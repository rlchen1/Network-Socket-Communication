#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Chess.h"

int socket(int domain, int protocol);

//bzero((char *) &serv_addr, sizeof(serv_addr));

//atoi(argv[1]);

int listen(int sockfd, int backlog);

//accept(sockfd, (struct sockaddr *) &cli_addr, &clilen));

//bzero(buffer, int);

//read

//write

//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <netdb.h>
#define PORT 7500

//// USE: int sockfd = socket(),
int socket(int domain, int protocol);
////domain = communication domain (IP address)
////type = communication type ????
////protocol value for IP (0) ????
////**********************************************************
////Host crystalcove.eecs.uci.edu has IP address 128.200.85.14
////**********************************************************
//
