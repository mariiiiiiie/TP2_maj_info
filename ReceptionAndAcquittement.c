#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <sys/socket.h>

#define CMD_SIZE 1500

int main(int argc, char *argv[]){
	
	char *host, *file;
	
	if (argc<3){
		printf("not enough arguments \n");
		exit(EXIT_FAILURE);
	}
	else{
		host = argv[1];
		file = argv[2];
		printf("the host is : %s \nthe file is : %s \n",host,file);
	}
	
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    // IPv4
    hints.ai_socktype = SOCK_DGRAM; // socket for an UDP
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_UDP; // config prtocol for an UDP

    // status creation
    int s = getaddrinfo(argv[1], "69", &hints, &result);
    
    if (s != 0) { //verification if getaddrinfo worked
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s)); //return of the error code
        exit(EXIT_FAILURE);
    }

	// socket creation
	int sfd = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	
	if (sfd==-1) {
		fprintf(stderr, "Error : %s cannot connect to the secteur %s\n", argv[0], argv[1]);
		exit(EXIT_FAILURE);
	}
	
	//Read request to send to the server
	//Creation of the request
	char* cmd = malloc(CMD_SIZE);

	cmd[0] = 0;
	cmd[1] = 1;
	// opcode for the read request
	
	char *filename = argv[2];
	strcpy(&cmd[2], filename);
	strcpy(&cmd[2 + strlen(filename) + 1], "octet");
	//consideration of zeros

	int size = (int) (2 + strlen(filename) + 1 + strlen("octet") + 1);// we add /0

	//file demand to the server
	
	int sendmessage;
	sendmessage = sendto(sfd, cmd, size, result ->ai_flags, result->ai_addr, result->ai_addrlen);
	printf("SendTo = %d\n", sendmessage);
	
	//error test
	
	if(sendmessage == -1){
		printf("error while sendto : %d\n", sendmessage);
	}
	
	// file reception
	
	struct sockaddr sock_addr;
	int recvSize;
	char espace[CMD_SIZE];
	
	socklen_t addrsize = sizeof(sock_addr);
	recvSize= recvfrom(sfd, espace, CMD_SIZE, 0,&sock_addr, &addrsize);
	printf("recvffrom=%d\n",recvSize);
	
	//error test
	if (recvSize==-1){
		printf("error while recvfrom : %d\n",recvSize);
	}
	
	for (int i = 4; i < recvSize; ++i) {
        printf("%c", espace[i]);
    }
	
	// opcode for the ACK request
	
	char* ackCmd = malloc(CMD_SIZE);
	ackCmd[0] = 0;
	ackCmd[1] = 4;
	
	char* Block = malloc(2);
	Block[0] = espace[2];
	Block[1] = espace[3];
	
	strcpy(&ackCmd[2], Block);
	

	//file demand to the server
	
	int sendacquittement;
	sendacquittement = sendto(sfd, ackCmd, sizeof(ackCmd), result ->ai_flags, result->ai_addr, result->ai_addrlen);
	printf("SendToASK = %d\n", sendacquittement);
	return 0;
	
	
}
