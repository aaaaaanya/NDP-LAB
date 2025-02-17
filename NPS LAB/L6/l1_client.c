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

int calculate_parity(const char* data, int parity_type) {
    int bit_count = 0;
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == '1') {
            bit_count++;
        }
    }

    if (parity_type == 0) {  // Even Parity
        return bit_count % 2 == 0 ? 1 : 0;  // Even parity is valid if there are an even number of 1's
    } else {  // Odd Parity
        return bit_count % 2 != 0 ? 1 : 0;  // Odd parity is valid if there are an odd number of 1's
    }
}

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


char *data = "1011001101";  // Example binary data to send
    int parity_type = 0;  // 0 for Even parity, 1 for Odd parity

	 // Send binary data
    send(sockfd, data, strlen(data), 0);
    printf("Sent data: %s\n", data);

    // Send the parity type (0 for Even, 1 for Odd)
    send(sockfd, &parity_type, sizeof(int), 0);

    // Calculate parity for verification (this is optional on client-side)
    if (calculate_parity(data, parity_type)) {
        printf("Parity for sent data is valid (Parity OK).\n");
    } else {
        printf("Parity for sent data is invalid (Parity Error).\n");
    }

	close(sockfd);
    return 0;
}
