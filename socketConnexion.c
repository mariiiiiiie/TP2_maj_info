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
    struct addrinfo *result,*rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    // IPv4
    hints.ai_socktype = SOCK_DGRAM; // socket for an UDP
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_UDP; // config prtocol for an UDP

    
    int s = getaddrinfo(argv[1], argv[2], &hints, &result);
    
    if (s != 0) { //verification if getaddrinfo worked
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s)); //return of the error code
        exit(EXIT_FAILURE);
    }
}
