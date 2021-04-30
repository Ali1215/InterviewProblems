#include <iostream>			// std::cin, std::cout, std::cerr
#include <sys/types.h>		// include for portability
#include <sys/socket.h>		// socket, connect
#include <arpa/inet.h>		// inet_aton, htonl, htons
#include <unistd.h>			// close
#include <cstring>			// strlen, strcmp

#define BUFFER_SIZE 1024
#define SERVER_PORT 50000
#define SERVER_IP "127.0.0.1"

int main() {
	// Declare structure variables that store local and peer socket addresses
	// sockaddr_in is the address sturcture used for IPv4 
	// sockaddr is the protocol independent address structure
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
	if (socket_desc == -1) {
		std::cerr << "Listening socket creation failed!\n";
		return 1;
	}

	// Prepare sockaddr_in structure variable
	peer_addr.sin_family = AF_INET;							// address family (2 bytes)
	peer_addr.sin_port = htons(SERVER_PORT);				// port in network byte order (2 bytes)
															// htons takes care of host-order to short network-order conversion.

	peer_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);		// internet address (4 bytes). INADDR_LOOPBACK is localhost address
	// inet_aton(SERVER_IP, &(peer_addr.sin_addr));

															// inet_aton converts the Internet host address from the IPv4 numbers-and-dots notation 
															// to binary form (network byte order)
															// htonl takes care of host-order to long network-order conversion.

	// connecting to the server socket
	if (connect(socket_desc, (struct sockaddr *) &peer_addr, sizeof peer_addr) == -1) {
		std::cerr << "Cannot connect to the host!\n";
		close(socket_desc);
		return 1;
	}
	std::cout << "Connection established with " << inet_ntoa(peer_addr.sin_addr) << ":" << ntohs(peer_addr.sin_port) << "\n";

    while (true) {
    	std::cout << "Enter an integer or \"Q\" to quit:\n";
    	std::cin.getline(outbound, BUFFER_SIZE);

    	send(socket_desc, outbound, strlen(outbound) + 1, 0);
    	if (strcmp("Q", outbound) == 0) {
    		break;
    	}

    	// blocking call
    	int rec_size = recv(socket_desc, inbound, BUFFER_SIZE, 0);
    	std::cout << "Received: " << inbound << std::endl;
    }

    // close socket
    close(socket_desc);

	return 0;
}