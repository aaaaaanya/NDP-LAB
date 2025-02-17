#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

// Function to check the parity of a string
int check_parity(const char* data, int parity_type) {
    int bit_count = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '1') {
            bit_count++;
        }
    }

    if (parity_type == 0) {  // Even Parity
        return bit_count % 2 == 0 ? 1 : 0;  // Valid if even number of 1s
    } else {  // Odd Parity
        return bit_count % 2 != 0 ? 1 : 0;  // Valid if odd number of 1s
    }
}

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
	
	// Receive the binary data
    read(newsockfd, buff, 1024);
    printf("Received data: %s\n", buff);

    // Ask the client which parity it used (0 for Even, 1 for Odd)
    int parity_type;
    read(newsockfd, &parity_type, sizeof(int));

    // Check the parity and display if the data is corrupt or not
    if (check_parity(buff, parity_type)) {
        printf("The data is received correctly (Parity OK).\n");
    } else {
        printf("The data is corrupted (Parity Error).\n");
    }
	close(sockfd);
	close(newsockfd);
}

