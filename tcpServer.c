#include <stdlib.h> // for basic memmory allocation and deallocation
#include <stdio.h> // for file read and write
#include <netdb.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 100
#define PORT 8080 
#define SA struct sockaddr
#define FIFO_FILE_1  "/tmp/client_to_server_fifo"
#define FIFO_FILE_2  "/tmp/server_to_client_fifo"

void sentFile(int sockfd, char *mystring)
{ 
	char buff[MAX]; // for read operation from file and used to sent operation 
 
	// create file 
	FILE *fp;
 	fp=fopen(mystring,"r");  // open file uses both stdio and stdin header files
	// file should be present at the program directory
	if( fp == NULL )
	{
 		printf("Error IN Opening File .. \n");
  		return ;
 	}
 
 	while ( fgets(buff,MAX,fp) != NULL ) // fgets reads upto MAX character or EOF 
  	write(sockfd,buff,sizeof(buff));  // sent the file data to stream
 
 	fclose (fp);       // close the file 
 
 	printf("File Sent successfully !!! \n"); 
}

int main() 
{
 
	int client_to_server;
    	int server_to_client;   	
	char buf[BUFSIZ];
	char buf1[1000];
    	/* create the FIFO (named pipe) */
    	mkfifo(FIFO_FILE_1, 0666);
    	mkfifo(FIFO_FILE_2, 0666);

	int sockfd, connfd, len;     // create socket file descriptor 
 	struct sockaddr_in servaddr, cli;   // create structure object of sockaddr_in for client and server// socket create and verification 
 	sockfd = socket(AF_INET, SOCK_STREAM, 0);    // creating a TCP socket ( SOCK_STREAM )
 
 	if (sockfd == -1) 
	{ 
  	printf("socket creation failed...\n"); 
  	exit(0); 
 	} 
 	else
  	printf("Socket successfully created..\n"); 
 
 
 	bzero(&servaddr, sizeof(servaddr));// assign IP, PORT 
 	servaddr.sin_family = AF_INET;     // specifies address family with IPv4 Protocol 
 	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // binds to any address
 	servaddr.sin_port = htons(PORT);     // binds to PORT specified// Binding newly created socket to given IP and verification 
 	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
	{ 
		printf("socket bind failed...\n"); 
  		exit(0); 
 	} 
 	else
  		printf("Socket successfully binded..\n");// Now server is ready to listen and verification 
 	
	if ((listen(sockfd, 5)) != 0) 
	{ 
  		printf("Listen failed...\n"); 
  		exit(0); 
 	} 
 	else
  		printf("Server listening..\n"); 
 
 	len = sizeof(cli); // Accept the data packet from client and verification 
 	connfd = accept(sockfd, (SA*)&cli, &len);  // accepts connection from socket
 
 	if (connfd < 0) 
	{ 
  		printf("server acccept failed...\n"); 
  		exit(0); 
 	} 
 	else
  		printf("server acccept the client...\n"); // Function for chatting between client and server 
	
	
	client_to_server = open(FIFO_FILE_1, O_RDONLY);
       	server_to_client = open(FIFO_FILE_2, O_WRONLY);

        read(client_to_server, buf, BUFSIZ);
	printf("Received: %s \n", buf);
	
	if (*buf = 1)
	{
		read(client_to_server, buf1, 1000);
		printf("Received: %s \n", buf1);
		
		sentFile(connfd,buf1); // After transfer close the socket 
	
	}
	
	memset(buf, 0, sizeof(buf));

	close(client_to_server);
    	close(server_to_client);

	unlink(FIFO_FILE_1);
   	unlink(FIFO_FILE_2);


	//sentFile(connfd);  // After transfer close the socket 
	
 
}



