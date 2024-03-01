#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char input[BUFSIZ];
	
	
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);
	
	if(result == -1)
	{
		perror("oops: client1");
		exit(1);
	}
	printf("Enter Data: ");
	fgets(input,BUFSIZ,stdin);
	
	printf("\n Sending Data: %s\n",input);
	write(sockfd, input, strlen(input)+1);
	
	printf("WAITING...\n");
	char res;
	read(sockfd, &res, sizeof(char));
	printf("Data from server = %s%c\n",input,res);

	close(sockfd);
	exit(0);
}
