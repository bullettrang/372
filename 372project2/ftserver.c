#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>			//allows 'hostent'
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char*argv[]){
	
	//declarations
	int mysocket, newsockfd, portnum;
	socklen_t servelen = sizeof(struct sockaddr_in);
	socklen_t clilen;
	
	//struct declarations
	struct sockaddr_in serv_address;
	struct sockaddr_in client_address;
	
	char buffer[256];
	
		//check for arg input
	 if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	
	//initialize socket
	mysocket = socket(AF_INET,SOCK_STREAM,0);
	//check socket initialized correctly
	if(mysocket <0){
		error("There was an error opening server socket");
	}
	
	//zero out the struct sockaddr_in
	memset(&serv_address,0,sizeof(serv_address));
	//initialize port num from arg
	portnum = atoi(argv[1]);
	
	//initialize the server_address member vals
	serv_address.sin_family = AF_INET;				//we are using TCP/IP
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(portnum);
	
	//bind the server info to the socket
	if(bind(mysocket,(struct sockaddr *) &serv_address, &servelen)<0){
		error("Error assigning name to socket");
	}
	
	if(listen(mysocket,5)<0){
		error("error listening");
	}
	
	int n;

	if(newsockfd == -1){
		error("error accepting");
	}
	
	/*Sever opens on 30021*/
	printf("Server open on %d\n",portnum);
	
		clilen = sizeof(cli_addr);
	newsockfd =accept(mysocket,(struct sockaddr *) &client_address,&clilen);
	
	n = read(newsockfd,buffer,255);

}