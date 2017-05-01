#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER "127.0.0.1"




int s[50];
int top=-1;

int isnum(char ch)
{
    if(ch>=48 && ch<=57)
    {
        return 1; 
    }
    return 0;
}


int main()
{
    int sockfd, newsockfd,  clilen,i,n;
    char buffer[256],msg[256],opr;
    struct sockaddr_in serv_addr, cli_addr;
    int ncount=0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER);
    serv_addr.sin_port = htons(1550);
 
    bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    float res=0;
    int tmp;
    int nol=0;
	top=-1;
               // Evaluates mathematical expression given in postfix form
	for(;;)
	{	
			bzero(buffer,256);
			
			n = read(newsockfd,buffer,255);
			
			printf("The expression: %s\n",buffer);
			
			printf("The expression is: %s\n",buffer);
			for(i=0;i<strlen(buffer);i++)
			{
				tmp = (int)buffer[i];
				if(isnum(tmp))
				{
					s[++top]=(tmp-48);
				}
				else if(buffer[i]=='+')
               			{
                   			int a=s[top]; 
                   			top--; 
                   			int b=s[top];
                   			top--;
                   			res=a+b;
                   			s[++top]=res;
               			}
               			else if(buffer[i]=='*')
               			{
                   			int a=s[top];
                   			top--;
                   			int b=s[top];
                   			top--;
                  			 res=a*b;
                   			s[++top]=res;
               			}
               			else if(buffer[i]=='-')
               			{
                   			int a=s[top];
                   			top--;
                   			int b=s[top];
                   			top--;
                   			res=a-b;
                  		 	s[++top]=res;
               			}
               			else if(buffer[i]=='/')
               			{
                   			int a=s[top];
                   			top--;
                   			int b=s[top];
                   			top--;
                   			res=a/b;
                   			s[++top]=res;
               			}
			}
			
			printf("%f\n",res);
			
				
			bzero(msg,256);
			snprintf (msg, sizeof(msg), "%f", res);
			res=0;
			//nol=0;
			//a=0;
			printf("%s",msg);
			n = write(newsockfd,msg, 255);
	}	
	
		
	
	close(newsockfd);
	close(sockfd);
    return 0; 
}






















