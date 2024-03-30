#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MAX_BUFFER_SIZE 1024

char *bit_stuffing(char* input){
  char* stuffed_output = (char *)malloc(strlen(input)*2+1);
  int stuffed_index = 0;
  int consecutive_ones = 0;
  int i;
  for(i=0;input[i] != '\0';i++){
    stuffed_output[stuffed_index++] = input[i];
    if(input[i] == '1'){
    	consecutive_ones++;
    	if(consecutive_ones == 5){    	
	      stuffed_output[stuffed_index++] = '0';
	      consecutive_ones = 0;
	    }
    }
    else{
    	consecutive_ones = 0;
    }
  }
  stuffed_output[stuffed_index] = '\0';
  return stuffed_output;
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n",argv[0]);
		exit(0);
	}
  int server_fd,new_socket;
  char *ip = "127.0.0.1";
  int port = atoi(argv[1]);
  struct sockaddr_in address;
  int opt = 1,n;
  int addrlen = sizeof(address);
  char buffer[MAX_BUFFER_SIZE] = {0};

  if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0){
    perror("socket failed");
    exit(1);
  }

  printf("socket created\n");
  memset(&address,'\0',sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = inet_addr(ip);

  n = bind(server_fd,(struct sockaddr*)&address,sizeof(address));
  if(n == -1){
    perror("bind error");
    exit(1);
  }
  printf("binded to the port number: %d\n",port);
  listen(server_fd,5);
  printf("Listening...\n");

  if((new_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t *)&addrlen)) < 0){
    perror("accept");
    exit(1);
  }

	bzero(buffer,MAX_BUFFER_SIZE);
  recv(new_socket,buffer,MAX_BUFFER_SIZE,0);
  printf("Received From client: %s\n", buffer);
  
  char *stuffed_data = bit_stuffing(buffer);
  send(new_socket,stuffed_data,strlen(stuffed_data),0);
  printf("Sent stuffed data back to client: %s\n",stuffed_data);
  
	free(stuffed_data);
	close(new_socket);
	close(server_fd);
	
  return 0;
}
