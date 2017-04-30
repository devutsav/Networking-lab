#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

#define SERVER "127.0.0.1"

int main()
{
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
  
    char buffer[256];
    
    sockfd = socket(AF_INET,SOCK_DGRAM,0);   //SOSK_DGRAM fro UDp
    if(sockfd==-1)
    {
	printf("There was an error while creating the socket\n");
        exit(0);
    }

    bzero(buffer,256);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET; //ipv4 
    serv_addr.sin_addr.s_addr=inet_addr(SERVER);
    serv_addr.sin_port=htons(1556);

   // bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if((bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))!=0)
    {
	printf("Error binding\n");
	exit(0);
    }
    
    /*int ret=listen(sockfd,5);
    if(ret!=0)
    {
	printf("Error listening\n");
	exit(0);
    }*/
    int clilen=sizeof(cli_addr);
    //newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	
    int n;
    printf("Server started succesfully...\n");
    while(1)
    {
	bzero(buffer,256);
        //int m=sizeof(serv_addr);
        
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&cli_addr,&clilen);
	printf("From client- %s\nto client- ",buffer);

        bzero(buffer,256);

        int n=0;
	while((buffer[n++]=getchar())!='\n');

	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&cli_addr,clilen);   //flag is set to 0
        if(strncmp("exit",buffer,4)==0)
	{
		printf("Exited\n");
		break;
	}
	

    }
    close(sockfd);
    
    return 0;
}
	
    	
    
