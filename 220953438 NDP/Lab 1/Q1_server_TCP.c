//not working
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

int main()
{
	int sockfd,newsockfd,retval,i;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	char buff[MAXSIZE];
	
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1)
	{
	printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval=listen(sockfd,1);
	if(retval==-1)
	{
	close(sockfd);
	}
	
	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);
	if(newsockfd==-1)
	{
		close(sockfd);
	}
	int j;
	recedbytes=recv(newsockfd,buff,sizeof(buff),0);
	if(recedbytes==-1)
	{
	close(sockfd);
	close(newsockfd);
	}
	int n,ar[100];
	
	n=buff[0]-'0';
	for(i=0;i<n;i++)
	{
	ar[i]=buff[i+1]-'0';
	}
	printf("Array size:%d",n);
	printf("Array elements:");
	for(i=0;i<n;i++)
	{
	printf("\n%d",ar[i]);
	}
	
	while(1)
	{
	
	
	memset(buff, '\0', sizeof(buff));
	recedbytes=recv(newsockfd,buff,sizeof(buff),0);
	if(recedbytes==-1)
	{
	close(sockfd);
	close(newsockfd);
	}
	int choice,num;
	//choice=buff[0]-'0';
	//num=buff[1]-'0';
	printf("Printing choice and num");
	//printf("%d %d",choice,num);
		printf("%d %d",buff[0],buff[1]);
	}
	close(sockfd);
	close(newsockfd);
}

