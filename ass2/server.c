#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	int i, count, len = 0;
	struct sockaddr_un server_address, client_address;

	remove("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);

	int ts;
	while (1)
	{
		char ch;
		char input[BUFSIZ], ans;
		printf("server waiting\n");

		int l = sizeof(client_address);
		ts = accept(server_sockfd, (struct sockaddr *)&client_address, &l);

		read(ts, input, BUFSIZ);
		printf("Server Received : %s\n", input);

		len = strlen(input);
		for (i = 0; i < len; i++)
		{
			if (input[i] == '1')
				count += 1;
		}
		if (count % 2 == 0)
			ans = '0';
		else
			ans = '1';

		write(ts, &ans, sizeof(char));
		printf("Sending back to the client\n");
	}
	close(ts);
}
