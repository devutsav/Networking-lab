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
	char filename[100],fname[100];
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
	else{
		printf("Connection problem\n");
	}

	FILE *fp;
	printf("Enter the file name- ");
	gets(filename);

	printf("Enter the new filename: ");  
	scanf("%s",fname); 

	fp=fopen(fname,"w"); 
	
	write(sockfd,filename,sizeof(filename));

	while(1)
	{
		bzero(buffer,sizeof(buffer));
		int bytes = read(sockfd,buffer,sizeof(buffer));
		if(bytes==0)
		{
			break;
		}
		fputs(buffer,fp);
		fputs(buffer,stdout); 
		
	}

	close(sockfd);
	fclose(fp);
	return 0;

}
