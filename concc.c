#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>

int main()
{
	int serv_len,clilen,sockfd,newsockfd;
	char buffer[100];
	struct sockaddr_in serv_addr,cli_addr;

	bzero((char *)&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(1556);

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0)
	{
		printf("Socket was not created successfully\n");
		exit(0);
	}
	else{
		printf("Socket created successfully\n");
	}
	serv_len = sizeof(serv_addr);

	if(connect(sockfd,(struct sockaddr *)&serv_addr,serv_len)!=-1)
	{
		printf("Connection successful\n");
	}
	while(1)
	{

			bzero(buffer,sizeof(buffer));
			int n=0;
			while((buffer[n++]=getchar())!='\n');
			write(sockfd,buffer,sizeof(buffer));
			
			printf("To server- %s\n",buffer);

			bzero(buffer,sizeof(buffer));
			
			read(sockfd,buffer,sizeof(buffer));
			printf("From server- %s\n",buffer);
		
	}
	close(sockfd);
	return 0;
	
}
	 
