#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/crc_socket"

unsigned int crc(char* data, char* divisor) {
int data_len = strlen(data);
int divisor_len = strlen(divisor);
unsigned int remainder = 0;
int i, j;
// Perform CRC calculation
for (i = 0; i < data_len; i++) {
remainder ^= (data[i] - '0') << (divisor_len - 1);
for ( j = 0; j < divisor_len; j++) {
if (remainder & (1 << (divisor_len - 1))) {
remainder ^= (divisor[j] - '0') << (divisor_len - j - 1);
}
remainder <<= 1;
}
}

return remainder >> 1;
}

int main() {
int server_fd, client_fd;
struct sockaddr_un server_addr, client_addr;
char data[100], divisor[100];
unsigned int codeword;

socket(AF_UNIX, SOCK_STREAM, 0);
// Bind the socket
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sun_family = AF_UNIX;
strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

listen(server_fd, 1);

printf("Server is running...\n");

// Accept connections
socklen_t client_len = sizeof(client_addr);
client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

// Receive data and divisor from client
recv(client_fd, data, sizeof(data), 0);
recv(client_fd, divisor, sizeof(divisor), 0);

// Calculate codeword using CRC
codeword = crc(data, divisor);

// Send codeword back to client
send(client_fd, &codeword, sizeof(codeword), 0);

// Close sockets
close(client_fd);
close(server_fd);
unlink(SOCKET_PATH);
return 0;
}
