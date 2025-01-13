//not working
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 50

int main()
{
	char buff[MAXSIZE];
	int sockfd,retval,i;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
		return;
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection error");
		return;
	}
	printf("Enter size of array:");
         int n, a [100];
         scanf("%d",&n);
         buff[0]=n+'0';
         printf("Enter the array:");
         for (i=0;i<n;i++)
         {
         scanf("%d",&a[i]);
         buff[i+1]=a[i]+'0';
         }
         sentbytes=send(sockfd,buff,sizeof(buff),0);
         if (sentbytes==-1)
         {
         printf("Error");
         close(sockfd);
         } 

	while(1)
	{
                 
         printf("Operations\n1.Search for a number\n2.Sort the array\n3.Split given set to odd and even\n Enter choice:");
         int num,choice;
         scanf("%d",&choice);
         memset(buff, '\0', sizeof(buff));
         buff[0]=choice+'0';
         
         switch(choice)
         {
         
         case 1:
         printf("Enter number to search for:");
         scanf("%d",&num);
         buff[1]=num+'0';
         
         sentbytes=send(sockfd,buff,sizeof(buff),0);
         if (sentbytes==-1)
         {
         printf("Error");
         close(sockfd);
         } 
         printf("Sent");
         break;
         
         case 2:
         printf("Sort array in ascending(1) or descending(2) order?");
         break;
         case 3:
         printf("Split set to odd and even");
         break;
         case 4:
         printf("Exiting");
         close(sockfd);
         exit(0);
         break;
         default:
         printf("Invalid.Enter again");
         }
      
	}
	close(sockfd);
}
