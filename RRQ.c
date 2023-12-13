#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>
#include <arpa/inet.h> 

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
	
	
}
