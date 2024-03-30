#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/crc_socket"

int main() {
int client_fd;
struct sockaddr_un server_addr;
char data[100], divisor[100];
unsigned int codeword;

// Create a socket
client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

// Connect to server
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sun_family = AF_UNIX;
strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

// Get data word and divisor from user
printf("Enter the data word: ");
scanf("%s", data);
printf("Enter the divisor: ");
scanf("%s", divisor);

// Send data and divisor to server
send(client_fd, data, strlen(data), 0);
send(client_fd, divisor, strlen(divisor), 0);

// Receive codeword from server
recv(client_fd, &codeword, sizeof(codeword), 0);

// Display codeword
printf("Calculated codeword: %u\n", codeword);

// Close socket
close(client_fd);

return 0;
}
