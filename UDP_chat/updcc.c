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
    int sockfd,newsockfd,len;
    struct sockaddr_in serv_addr, cli_addr;
 
    char buffer[256];
    
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd==-1)
    {
		printf("Error while creating socket\n");
		exit(0);
    }
    bzero(buffer,256);
  
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET; //ipv4 
    serv_addr.sin_addr.s_addr=inet_addr(SERVER);
    serv_addr.sin_port=htons(1556);

    //connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
      
    len = sizeof(serv_addr);
    int n;
    while(1)
    {
	printf("To server- ");
        n=0;
	while((buffer[n++]=getchar())!='\n');
	sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&serv_addr,sizeof(serv_addr));   //flag is set to 0
	bzero(buffer,0);
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&serv_addr,&len);

	printf("Reply from server- %s",buffer);
        
        if(strncmp("exit",buffer,4)==0)
	{
		printf("Exited\n");
		break;
	}
	else{
	 //printf("Message from server- %s\n",buffer);
	}


    }
    close(sockfd);
 
    return 0;
}
	
    	
    

     
