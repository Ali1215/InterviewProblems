/*Name: Ali Muneer
Student ID: 1615694
CMPUT 275; Winter 2021
Assignment 1 Part 2*/

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <sstream>
#include <sys/socket.h> // socket, connect
#include <arpa/inet.h>  // inet_aton, htonl, htons
#include <unistd.h>     // close
#include <cstring>      // strlen, strcmp
#include <string>
// Add more libraries, macros, functions, and global variables if needed

#define BUFFER_SIZE 1024


using namespace std;

int create_and_open_fifo(const char *pname, int mode)
{
    // creating a fifo special file in the current working directory
    // with read-write permissions for communication with the plotter
    // both proecsses must open the fifo before they can perform
    // read and write operations on it
    if (mkfifo(pname, 0666) == -1)
    {
        cout << "Unable to make a fifo. Ensure that this pipe does not exist already!" << endl;
        exit(-1);
    }

    // opening the fifo for read-only or write-only access
    // a file descriptor that refers to the open file description is
    // returned
    int fd = open(pname, mode);

    if (fd == -1)
    {
        cout << "Error: failed on opening named pipe." << endl;
        exit(-1);
    }

    return fd;
}

string convert_read(string input){
    size_t decimalIndex = input.find_first_of('.');
    input.insert(decimalIndex+6,".");
    input.erase(decimalIndex,1 );
    input.erase(input.size()-2, 2);
    return input;
}


int main(int argc, char const *argv[])
{
    if (argc != 3){
        cout << "This program takes tow command line arguments" << endl;
        return 0;
    }
    int port_num = atoi(argv[1]);
    const char * server_ip = argv[2];
    //cout << "test";
    const char *inpipe = "inpipe";
    const char *outpipe = "outpipe";

    int in = create_and_open_fifo(inpipe, O_RDONLY);
    cout << "inpipe opened..." << endl;
    int out = create_and_open_fifo(outpipe, O_WRONLY);
    cout << "outpipe opened..." << endl;

    struct sockaddr_in my_addr, peer_addr;

    // zero out the structor variable because it has an unused part
    memset(&my_addr, '\0', sizeof my_addr);

    // Declare socket descriptor
    int socket_desc;

    char outbound[BUFFER_SIZE] = {};
    char inbound[BUFFER_SIZE] = {};

    /*
		socket() input arguments are:
		socket domain (AF_INET):	IPv4 Internet protocols
		socket type (SOCK_STREAM):	sequenced, reliable, two-way, connection-based
									byte streams
		socket protocol (0): 		OS selects a protocol that supports the requested
							 		socket type (in this case: IPPROTO_TCP)
		socket() returns a socket descriptor
	*/
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        std::cerr << "Listening socket creation failed!\n";
        return 1;
    }

    // Prepare sockaddr_in structure variable
    peer_addr.sin_family = AF_INET;          // address family (2 bytes)
    peer_addr.sin_port = htons(port_num); // port in network byte order (2 bytes)
                                             // htons takes care of host-order to short network-order conversion.

    
    inet_aton(server_ip, &(peer_addr.sin_addr));

    // inet_aton converts the Internet host address from the IPv4 numbers-and-dots notation
    // to binary form (network byte order)
    // htonl takes care of host-order to long network-order conversion.

    // connecting to the server socket
    if (connect(socket_desc, (struct sockaddr *)&peer_addr, sizeof peer_addr) == -1)
    {
        std::cerr << "Cannot connect to the host!\n";
        close(socket_desc);
        return 1;
    }
    std::cout << "Connection established with " << inet_ntoa(peer_addr.sin_addr) << ":" << ntohs(peer_addr.sin_port) << "\n";

    while (true)
    {
        //initialize buffer and pipe/socket variables
        char line[BUFFER_SIZE] = {};
        int bytes_read;
        int bytes_written;
        
        bytes_read = read(in, line, 22); //read in starting set of coordinates
        
        //if it is the Quit message then send Q to the server to quit
        if (line[0] == 'Q'){
            bytes_written = write(socket_desc, "Q", 2);
            break;
        }
        stringstream stream(line);
        string lat1, lat2, lon1, lon2;
        stream >> lat1 >> lon1;
        
        bytes_read = read(in, line, 22); //read the endpoint set of coordinates
        
        //reset stream
        stream.str("");
        stream.clear();
        stream << line;
        
        stream >> lat2 >> lon2;
        
        //construct request, converting each lattitude and longitude to proper format for server
        string request = "R " + convert_read(lat1) + ' ' + convert_read(lon1)
            + ' ' + convert_read(lat2) + ' ' + convert_read(lon2);
        
        bytes_written = write(socket_desc, request.c_str(), strlen(request.c_str()) + 1);
        
        //read number of vertices
        bytes_read = read(socket_desc, line, BUFFER_SIZE);
        //reset stream
        stream.str("");
        stream.clear();
        stream << line;

        char c;
        int N;
        stream >> c >> N;
        

        if (c != 'N'){
            bytes_written = write(socket_desc, "W", 2); //abnormal input, give unexpected input to server to reset both
            cout << "Abnormal Input, Resetting ....." << endl;
            continue;
        }
        
        
        if (N == 0){
            //if N is 0 then there are no points to be written, signal plotter and reset
            bytes_written = write(out, "E\n", 2);
            cout << "No path found...." << endl;
            continue;
        }
        //send acknowledgement to server
        bytes_written = write(socket_desc, "A", 2);
        
        if (N == 1){
            bytes_written = write(out, "E\n", 2);
            cout << "No path found...." << endl;
            continue;
        } 

        bool error = false;
        for (int i = 0; i<N; i++){
            //read in one waypoint
            bytes_read = read(socket_desc, line, BUFFER_SIZE);
            string way_lat, way_lon;

            //reset stream
            stream.str("");
            stream.clear();
            stream << line;

            
            stream >> c >> way_lat >> way_lon;
            if (c != 'W'){
                error = true;
                bytes_written = write(socket_desc, "W", 2); //give unexpected input to server to reset both
                cout << "Abnormal Input, Resetting ....." << endl;
                break;
            }
            //send acknowledgement
            bytes_written = write(socket_desc, "A", 2);

            //add decimal point to match plotter format
            way_lat.insert(way_lat.length()-5,".");
            way_lon.insert(way_lon.length()-5,".");
            string response = way_lat + ' ' + way_lon + '\n';
            
            //write waypoint to plotter pipe
            bytes_written = write(out, response.c_str(), response.length());
        }
        if (error) continue;
        bytes_read = read(socket_desc, line, BUFFER_SIZE);
        //read ending input of the server
        if (strcmp("E", line) != 0)
            {
                cout << "Abnormal Input, Resetting .....\n";
                error = true;
                continue;
            }
        // send end message to the plotter
        bytes_written = write(out, "E\n", 2);
        cout << "Ready for new setpoints...." << endl;
    }

    // close socket
    close(socket_desc);
    

   
    //close pipes and delete them
    close(in);
    close(out);
    unlink(inpipe);
    unlink(outpipe);
    return 0;
}
