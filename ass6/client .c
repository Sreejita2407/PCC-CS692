#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 5555
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char ip_address[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) == -1) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", SERVER_IP, PORT);

    // Get IPv4 address from user
    printf("Enter IPv4 address: ");
    fgets(ip_address, BUFFER_SIZE, stdin);
    ip_address[strcspn(ip_address, "\n")] = '\0';  // Remove newline character

    // Send IPv4 address to server
    send(client_socket, ip_address, strlen(ip_address), 0);

    // Receive response from server
    char response[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, response, BUFFER_SIZE, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    response[bytes_received] = '\0';
    printf("Server response: %s\n", response);

    close(client_socket);

    return 0;
}
