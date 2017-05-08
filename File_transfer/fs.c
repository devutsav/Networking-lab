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
	int clilen,sockfd,newsockfd,serv_len;
	char buffer[100],bass[100];
	struct sockaddr_in serv_addr,cli_addr;

	bzero((char *)&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(1556);

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Socket was not created successfully\n");
		exit(1);
	}
	printf("Socket succsefully created\n");

	clilen = sizeof(cli_addr);
	serv_len = sizeof(serv_addr);

	if(bind(sockfd,(struct sockaddr *)&serv_addr,serv_len)==0)
	{
		printf("Binding successful\n");
	}	
	else{
		printf("Binding not successful\n");
	}

	listen(sockfd,5);

	newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
	if(newsockfd<0)
	{
		printf("Error in accepting the connection\n");
	}
	else{
		printf("Connection accepted\n");
	}


	FILE *fp;


	bzero(buffer,sizeof(buffer));
	read(newsockfd,buffer,100);
	//printf("From client- %s\n",filename);
	//bzero(buffer,sizeof(buffer));
	/*int n=0;
	  while((buffer[n++]=getchar())!='\n');*/
	fp=fopen(buffer,"r");
	while(fgets(bass,sizeof(bass),fp))
	{
		write(newsockfd,bass,sizeof(buffer));
	}
	//printf("To client- %s\n",buffer);


	close(sockfd);
	close(newsockfd);
	fclose(fp);
	return 0;
}

