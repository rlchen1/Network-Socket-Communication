#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#//include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <netdb.h>
#define PORT 7500


struct sockaddr_in{
	short sin_family; //e.g. AF_INET
	unsigned short sin_port; //e.g. hton(3490)
	struct in_addr sin_addr; //defined below
	char sin_zero[8]; //zero this if you want to
};

struct in_addr{
	unsigned long s_addr; //load with inet_pton()
};

struct sockaddr{
	unsigned short sa_family; //address family, AF_xxx
	char sa_data[14]; //14 bytes of protocol address
};

// USE: int sockfd = socket(), 
int socket(int domain, int protocol);
//domain = communication domain (IP address)
//type = communication type ???? 
//protocol value for IP (0) ????
//**********************************************************
//Host crystalcove.eecs.uci.edu has IP address 128.200.85.14
//**********************************************************

//optional function: prevents errors like addresss already in use
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

//after socket created, this binds socket to address and port # from struct addr
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

//waits for the client to make a connection to the server
//backlog defines max length of queue for pending connections of sockfd to grow???
int listen(int sockfd, int backlog);

//extracts 1st connection request on queue of pending connections for listening socket (sockfd) and creates a new connected socket. Returns a new file descriptor referring to that socket. Connection is established between client and server.
int new_socket(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

//Calls the socket referred to by sockfd to address specified by struct addr. Server address and port specified in addr.
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
