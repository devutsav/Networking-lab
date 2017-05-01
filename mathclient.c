#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;

    char buffer[256],msg[256];

    if (argc < 3) 
    {
        

		     printf("Either %s, %s or %s not entered properly\n",argv[0],argv[1],argv[2]);
	
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("ERROR opening socket");
        exit(1);
    }
    

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(const struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
         perror("ERROR connecting to the server");
         exit(1);
    }	
	for(;;)
	{
	    printf("\nPlease enter the expression: ");
	    bzero(buffer,256);
	    fgets(buffer,255,stdin);
	    n = write(sockfd,buffer,strlen(buffer));
	    
	    bzero(msg,256);
	    n = read(sockfd,msg,255);
	    
	    printf("\nHere is the answer: %s\n",msg);
	}
	close(sockfd);
    return 0;
}
