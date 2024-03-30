#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n",argv[0]);
		exit(0);
	}
  int sock;
  char *ip = "127.0.0.1";
  int port = atoi(argv[1]);
  struct sockaddr_in address;
  char buffer[MAX_BUFFER_SIZE] = {0};
  char bit_stream[MAX_BUFFER_SIZE] = {0};

	printf("Enter bit stream: ");
	fgets(bit_stream,MAX_BUFFER_SIZE,stdin);
	
  if((sock = socket(AF_INET,SOCK_STREAM,0)) == 0){
    perror("socket failed");
    exit(1);
  }

  printf("socket created\n");
  memset(&address,'\0',sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip);
  
  if(connect(sock,(struct sockaddr*)&address,sizeof(address)) < 0){
  	perror("Connection failed");
  	exit(1);
  }
  
  bzero(buffer,MAX_BUFFER_SIZE);
  send(sock, bit_stream, strlen(bit_stream), 0);
  printf("Bit stream sent to server\n");
  
  recv(sock,buffer,MAX_BUFFER_SIZE,0);
  printf("Received stuffed data from server: %s\n",buffer);
  
  close(sock);

  return 0;
}
