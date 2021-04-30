/*Name: Ali Muneer
Student ID: 1615694
CMPUT 275; Winter 2021
Assignment 1 Part 2*/

#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <list>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "wdigraph.h"
#include "dijkstra.h"

#define LISTEN_BACKLOG 50
#define BUFFER_SIZE 1024

using namespace std;

struct Point
{
    long long lat, lon;
};

// returns the manhattan distance between two points
long long manhattan(const Point &pt1, const Point &pt2)
{
    long long dLat = pt1.lat - pt2.lat, dLon = pt1.lon - pt2.lon;
    return abs(dLat) + abs(dLon);
}

// finds the point that is closest to a given point, pt
int findClosest(const Point &pt, const unordered_map<int, Point> &points)
{
    pair<int, Point> best = *points.begin();

    for (const auto &check : points)
    {
        if (manhattan(pt, check.second) < manhattan(pt, best.second))
        {
            best = check;
        }
    }
    return best.first;
}

// reads graph description from the input file and builts a graph instance
void readGraph(const string &filename, WDigraph &g, unordered_map<int, Point> &points)
{
    ifstream fin(filename);
    string line;

    while (getline(fin, line))
    {
        // split the string around the commas, there will be 4 substrings either way
        string p[4];
        int at = 0;
        for (auto c : line)
        {
            if (c == ',')
            {
                // starting a new string
                ++at;
            }
            else
            {
                // appending a character to the string we are building
                p[at] += c;
            }
        }

        if (at != 3)
        {
            // empty line
            break;
        }

        if (p[0] == "V")
        {
            // adding a new vertex
            int id = stoi(p[1]);
            assert(id == stoll(p[1])); // sanity check: asserts if some id is not 32-bit
            points[id].lat = static_cast<long long>(stod(p[2]) * 100000);
            points[id].lon = static_cast<long long>(stod(p[3]) * 100000);
            g.addVertex(id);
        }
        else
        {
            // adding a new directed edge
            int u = stoi(p[1]), v = stoi(p[2]);
            g.addEdge(u, v, manhattan(points[u], points[v]));
        }
    }
}


// Keep in mind that in Part I, your program must handle 1 request
// but in Part 2 you must serve the next request as soon as you are
// done handling the previous one
int main(int argc, char *argv[])
{
    int port_num = atoi(argv[1]);
    WDigraph graph;
    unordered_map<int, Point> points;

    // build the graph
    readGraph("edmonton-roads-2.0.1.txt", graph, points);

    // In Part 2, client and server communicate using a pair of sockets
    // modify the part below so that the route request is read from a socket
    // (instead of stdin) and the route information is written to a socket

    // read a request
    struct sockaddr_in my_addr, peer_addr;

    // zero out the structor variable because it has an unused part 
    memset(&my_addr, '\0', sizeof my_addr);

    // declare variables for socket descriptors
    int lstn_socket_desc, conn_socket_desc;

    char echobuffer[BUFFER_SIZE] = {}; 

    /*
		socket() input arguments are:
		socket domain (AF_INET):	IPv4 Internet protocols 
		socket type (SOCK_STREAM):	sequenced, reliable, two-way, connection-based
									byte streams
		socket protocol (0): 		OS selects a protocol that supports the requested
							 		socket type (in this case: IPPROTO_TCP)
		socket() returns a socket descriptor
	*/
    lstn_socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (lstn_socket_desc == -1)
    {
        std::cerr << "Listening socket creation failed!\n";
        return 1;
    }

    // prepare sockaddr_in structure variable
    my_addr.sin_family = AF_INET;                // address family (2 bytes)
    my_addr.sin_port = htons(port_num);              // port in network byte order (2 bytes)
                                                 // htons takes care of host-order to short network-order conversion.
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // internet address (4 bytes) INADDR_ANY is all local interfaces
                                                 // htons takes care of host-order to long network-order conversion.

    // note bind takes in a protocol independent address structure
    // hence we need to cast sockaddr_in* to sockaddr*
    if (bind(lstn_socket_desc, (struct sockaddr *)&my_addr, sizeof my_addr) == -1)
    {
        std::cerr << "Binding failed!\n";
        close(lstn_socket_desc);
        return 1;
    }
    std::cout << "Binding was successful\n";

    if (listen(lstn_socket_desc, LISTEN_BACKLOG) == -1)
    {
        std::cerr << "Cannot listen to the specified socket!\n";
        close(lstn_socket_desc);
        return 1;
    }


    socklen_t peer_addr_size = sizeof my_addr;
    conn_socket_desc = accept(lstn_socket_desc, (struct sockaddr *)&peer_addr, &peer_addr_size);
    if (conn_socket_desc == -1)
    {
        std::cerr << "Connection socket creation failed!\n";
        // continue;
        return 1;
    }
    std::cout << "Connection request accepted from " << inet_ntoa(peer_addr.sin_addr) << ":" << ntohs(peer_addr.sin_port) << "\n";

    
    
    while (true)
    {
        // Read first message from client
        int rec_size = read(conn_socket_desc, echobuffer, BUFFER_SIZE);
        
        cout << "Message received\n";
        //Exit program if Quit signal Received
        if ('Q' == echobuffer[0])
        {
            cout << "Quit\n";
            break;
        }
        
        //check if it is a request
        if ('R' != echobuffer[0])
        {
            cout << "Not a request\n";
            continue;
        }
        
        
        // create stringstream and extract information
        stringstream stream(echobuffer);
        char c;
        Point sPoint, ePoint;
        stream >> c >> sPoint.lat >> sPoint.lon >> ePoint.lat >> ePoint.lon;
        
        //find closest starting vertex to requested start/end points
        int start = findClosest(sPoint, points), end = findClosest(ePoint, points);
        
        // run dijkstra's, this is the unoptimized version that does not stop
        // when the end is reached but it is still fast enough
        unordered_map<int, PIL> tree;
        dijkstra(graph, start, tree);
        
        // no path
        if (tree.find(end) == tree.end())
        {
            int wrt_size = write(conn_socket_desc, "N 0", 4);
            continue;
        }
        else
        {
            // read off the path by stepping back through the search tree
            list<int> path;
            while (end != start)
            {
                path.push_front(end);
                end = tree[end].first;
            }
            path.push_front(start);
            
            // output the path

            //output number of vertices
            string out;
            out = "N " + to_string(path.size());
            int wrt_size = write(conn_socket_desc, out.c_str(), out.length() + 1);
            
            //await acknowledgement
            rec_size = read(conn_socket_desc, echobuffer, BUFFER_SIZE);
            if (strcmp("A", echobuffer) != 0)
            {
                cout << "Not acknowledged properly\n";
                continue;
            }
            if (path.size() == 1) continue;
            bool error = false;
            
            for (int v : path)
            {
                //output waypoint to client
                out = "W " + to_string(points[v].lat) + ' ' + to_string(points[v].lon);
                
                wrt_size = write(conn_socket_desc, out.c_str(), out.length() + 1);
                
                //await acknowledgement
                rec_size = read(conn_socket_desc, echobuffer, BUFFER_SIZE);
                if (strcmp("A", echobuffer) != 0)
                {
                    cout << "Not acknowledged properly\n";
                    error = true;
                    break;
                }
            }
            if (error)
                continue; //reset state if unexpected output
            wrt_size = write(conn_socket_desc, "E", 2); //signal to client that waypoints are all sent

            cout << "Finished Sending Waypoints...\n";
        }
        
        
        
    }
    
    close(conn_socket_desc);
    close(lstn_socket_desc);
    

    return 0;
}
