#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<time.h>
#define SERVER 1556
//#define s_adrr "127.0.0.1'

int main()
{
	int len, clilen;
	char buffer[100];
	time_t t;
	struct sockaddr_in serv_addr,cli_addr;
	
	int sockfd=socket(AF_INET, SOCK_STREAM,0);
	
	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(SERVER);

	clilen=sizeof(cli_addr);
	len=sizeof(serv_addr);

	//bind(sockfd,(struct sockaddr *)&serv_addr,len);

	//listen(sockfd,5);

	//int newsockfd=accept(sockfd,(struct sockaddr *)&serv_addr,&len);
	connect(sockfd,(struct sockaddr *)&serv_addr,len);

	//while(1)
	//{
		bzero(buffer,sizeof(buffer));
               
		//write(sockfd,buffer,sizeof(buffer));
		/*int n=0;
		while((buffer[n++]=getchar())!='\n');*/
		
		//bzero(buffer,sizeof(buffer));
	
	       read(sockfd,buffer,sizeof(buffer));

		printf("The Day and time as responded by the server: %s\n",buffer);


	//}
	close(sockfd);
	
    
	return 0;
}
