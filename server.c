#include <netdb.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 


// Fonction scanner les ports
	void scanPort(char hostname[30] , int start, int end ){
		int   sokpo,soport;
	    	struct sockaddr_in serv_addr;
		struct hostent *server;

		sokpo = socket(AF_INET, SOCK_STREAM, 0);
		server = gethostbyname(hostname);

		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

		if (server == NULL) {
			fprintf(stderr,"Erreur, pas d'hôte\n");
			exit(0);}  
	  
		for(int j = start ; j<end;j++){
			serv_addr.sin_port = htons(j);
			soport = connect(sokpo,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
		    	if (soport >= 0) {
				printf("--> Port %d ouvert  ",j); }	    		
		}
		printf("\n");
		close(sokpo);
	}



// Fonction Afficher Les adresses IPv4 des Clients
	void showIp(char tab[2][20]){
		printf("Les adresses IPv4 Disponibles : \n");
		int i;
	   	for(i=1;i<3;i++){
			printf("%d/ IP : %s \n",i,tab[i]);
		}
	}

void affiche(){
	printf("Accepte le client...\n"); ;
}

// Fonction Main 
int main() 
{ 
    	int sockfd, connfd, len,start , end;
    	struct sockaddr_in servaddr;
	char ips[2][20];
    	char hostname[20] ;


    // Création et vérification de socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("La création de socket a échoué...\n"); 
        exit(0); 
    } 
    else
        printf("Socket créé avec succès..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // attribuer IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Liaison de socket 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("La liaison de socket a échoué...\n"); 
        exit(0); 
    } 
    else
        printf("Socket lié avec succès..\n"); 
  
    // Ecoute et vérification 

    if ((listen(sockfd, 5)) != 0) { 
        printf("Écoute a échoué...\n"); 
        exit(0); 
    } 
    else
        printf("Écoute du serveur..\n"); 


    // Accepter le paquet de données du client et vérification
	len = sizeof(servaddr);
	pthread_t id;
	 for(int i=1;i<3;i++){
	    connfd = accept(sockfd, (SA*)&servaddr,&len ); 
	    if (connfd < 0) { 
		printf("Acceptation du serveur a échoué...\n"); 
		exit(0); 
	    } 
	    else{
		if (pthread_create(&id, NULL, (void *)affiche, NULL) != 0) {
		    	perror("Créer une erreur pthread!\n");
		    	exit(EXIT_FAILURE);}
		 	strcpy(ips[i], inet_ntoa(servaddr.sin_addr));}	
		sleep(1);
	 	}

   // Afficher Les adresses IPv4

	showIp(ips);

   //Scanner Les Ports
	printf("Entrez Hostname or IP: \n");
	scanf("%s",&hostname);

    	printf("Entrez le numéro du port Début: \n");
    	scanf("%d",&start);

   	printf("Entrez le numéro du port Final:\n");
	scanf("%d", &end);
	scanPort(hostname,start,end);
	
    // Fermer Socket
    close(sockfd); 

} 
