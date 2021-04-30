#include <iostream>			// std::cout, std::cerr
#include <sys/types.h>		// include for portability
#include <sys/socket.h>		// socket, bind, listen, accept
#include <sys/time.h>		// timeval
#include <unistd.h>			// close
#include <arpa/inet.h>		// inet_ntoa, htonl, htons, ntohl, ntohs
#include <netdb.h>			// getaddrinfo, freeaddrinfo, INADDR_ANY (superset of netinet/in.h)
#include <cstdlib>			// atoi
#include <cstring>			// strlen, strcmp
#include <string>			// string

#define PORT 50000
#define LISTEN_BACKLOG 50
#define BUFFER_SIZE 1024

int main() {
	// declare structure variables that store local and peer socket addresses
	// sockaddr_in is the address sturcture used for IPv4 
	// sockaddr is the protocol independent address structure
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
	if (lstn_socket_desc == -1) {
		std::cerr << "Listening socket creation failed!\n";
		return 1;
	}

	// prepare sockaddr_in structure variable
	my_addr.sin_family = AF_INET;				// address family (2 bytes)
	my_addr.sin_port = htons(PORT);				// port in network byte order (2 bytes)
												// htons takes care of host-order to short network-order conversion.
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);// internet address (4 bytes) INADDR_ANY is all local interfaces
												// htons takes care of host-order to long network-order conversion.

	// note bind takes in a protocol independent address structure
	// hence we need to cast sockaddr_in* to sockaddr*
	if (bind(lstn_socket_desc, (struct sockaddr *) &my_addr, sizeof my_addr) == -1) {
	    std::cerr << "Binding failed!\n";
	    close(lstn_socket_desc);
	    return 1;
	}
	std::cout << "Binding was successful\n";


    if (listen(lstn_socket_desc, LISTEN_BACKLOG) == -1) {
    	std::cerr << "Cannot listen to the specified socket!\n";
        close(lstn_socket_desc);
        return 1;
    }

	socklen_t peer_addr_size = sizeof my_addr;

	// comment the outer while loop to make the server 
	// terminate after accepting one connection request
	while (true) {
		// extract the first connection request from the queue of pending connection requests
		// return a new connection socket descriptor which is not in the listening state
		conn_socket_desc = accept(lstn_socket_desc, (struct sockaddr *) &peer_addr, &peer_addr_size);
		if (conn_socket_desc == -1){
			std::cerr << "Connection socket creation failed!\n";
			// continue;
			return 1;
		}
		std::cout << "Connection request accepted from " << inet_ntoa(peer_addr.sin_addr) << ":" << ntohs(peer_addr.sin_port) << "\n";

		// declare structure variable that represents an elapsed time 
		// it stores the number of whole seconds and the number of microseconds
		struct timeval timer = {.tv_sec = 1, .tv_usec = 10000};

		
		/*   setsockopt sets a socket option
		it takes a socket descriptor, an integer that represents the level at which the option resides,
		an integer that can be mapped to the option name, a buffer pointed to by a const void * that 
		contains the option value, and an integer for the size of that buffer

		to manipulate socket API options, use SOL_SOCKET for the level
		SO_RCVTIMEO and SO_SNDTIMEO are option names for receiving and sending timeouts respectively
		send and recv functions return -1 if timeout occurs
		*/
		// if (setsockopt(conn_socket_desc, SOL_SOCKET, SO_RCVTIMEO, (void *) &timer, sizeof(timer)) == -1) {
		// 	std::cerr << "Cannot set socket options!\n";
		// 	close(conn_socket_desc);
		// 	return 1;
		// }

	    while (true) {
	    	// blocking call - blocks until a message arrives 
	    	// (unless O_NONBLOCK is set on the socket's file descriptor)
	    	int rec_size = recv(conn_socket_desc, echobuffer, BUFFER_SIZE, 0);
	    	if (rec_size == -1) {
	    		std::cout << "Timeout occurred... still waiting!\n";
	    		continue;
	    	}
	    	std::cout << "Message received\n";
	    	if (strcmp("Q", echobuffer) == 0) {
	    		std::cout << "Connection will be closed\n";
	    		break;
	    	}

	    	// convert a c-style string to an integer
	    	int num = atoi(echobuffer);

	    	// convert the integer to a string
	    	std::string str = std::to_string(-num);
	    	send(conn_socket_desc, str.c_str(), str.length() + 1, 0);
	    	std::cout << "Computation result sent back\n";
	    }
	}

	// close socket descriptors
    close(lstn_socket_desc);
    close(conn_socket_desc);

	return 0;
}