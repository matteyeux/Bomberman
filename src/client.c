#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int client(char *ip_addr, int port)
{
	int sock;
	struct sockaddr_in server;
	char buff[80] = {0};

	printf("IP : %s\tPORT : %d\n", ip_addr, port);
	// init socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1) {
		perror("socket");
		return -1;
	}

	// init server structure
	server.sin_addr.s_addr = inet_addr(ip_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	// connect to server
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("connect");
		return -2;
	}


	while (1) {
		// copy simple string into buff
		strcpy(buff,"client_message\n");

		// send string to server
		send(sock, buff, sizeof(buff), 0);

		// set buff to 0 so we can reuse it
		bzero(buff, sizeof(buff));

		// receive data
		recv(sock, buff, sizeof(buff), 0);
		
		// very complexe function to print something
		printf("From Server : %s", buff);

		sleep(1);
	}

	close(sock);
	return 0;
}