#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
int main() 
{ 
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli; 

	// creation et verification du socket 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("création du socket échoué...\n"); 
		exit(0); 
	} 
	else
	printf("Socket créer avec success..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 
	// IP et PORT du serveur
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("192.168.43.217"); 
	servaddr.sin_port = htons(PORT); 

	// connection au serveur 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection au serveur échoué...\n"); 
		exit(0); 
	} 
	else
		printf("connecté au serveur ..\n"); 
	close(sockfd); 
} 

