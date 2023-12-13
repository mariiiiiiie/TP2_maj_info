#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

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
}
