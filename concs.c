#include<stdio.h>   //Concurrent 
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>

int main()
{
	int clilen,sockfd,newsockfd,serv_len;
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
	clilen = sizeof(cli_addr);
	serv_len = sizeof(serv_addr);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,serv_len)==0)
	{
		printf("Binding successful\n");
	}	

	listen(sockfd,5);
	
	while(1)
	{
		newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
		int pid=fork();

		if(pid==0)
		{
			
			do
			{
				bzero(buffer,sizeof(buffer));
				read(newsockfd,buffer,sizeof(buffer));
				printf("From client- %s\n",buffer);
				bzero(buffer,sizeof(buffer));
				int n=0;
				while((buffer[n++]=getchar())!='\n');
				write(newsockfd,buffer,sizeof(buffer));
				printf("To client- %s\n",buffer);
			
			}while(strcmp(buffer,"exit")==0);
		}
		else
		{
			printf("Still in parent process\n");
		}	
		close(newsockfd);
		//close(sockfd);
	}
	close(sockfd);
	
	return 0;
}
	 
