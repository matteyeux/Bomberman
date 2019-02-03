#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include <include/server.h>

int server(int port)
{
	int sock, client_sock = 1, c;
	struct sockaddr_in server, client;
	int enable = 1;

	// Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1) {
		printf("Could not create socket");
	}

	//  socket option to bypass the "Address already in use" error from bind
	//  SO_REUSEADDR just says that you can reuse local addresses
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		printf("setsockopt(SO_REUSEADDR) failed");
		return -2;
	}

	// setup the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	// Bind
	if (bind(sock,(struct sockaddr *)&server , sizeof(server)) < 0) {
		perror("bind");
		return 1;
	}

	// Listen
	listen(sock , 4);
	printf("listing on port %d\n", port);

	c = sizeof(struct sockaddr_in);

	pthread_t thread_id;

	while (client_sock) {
		client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
		printf("Connection accepted\n");

		if (pthread_create(&thread_id, NULL, handler, (void*) &client_sock) < 0) {
			perror("pthread_create");
			return -1;
		}

		printf("thread created\n");
	}

	if (client_sock < 0) {
		perror("accept");
		return 1;
	}

	close(client_sock);
	return 0;
}

void *handler(void *sockfd)
{
	char buff[80] = {0};
	int sock = *(int*)sockfd;
	ssize_t sender = 0;

	while (1) {
		// read the message from client and copy it in buffer
		recv(sock, buff, sizeof(buff), 0);

		// print buffer which contains the client contents
		printf("from client: %s", buff);
	
		bzero(buff, 80);

		// copy
		strcpy(buff,"server_message\n");

		sender = send(sock, buff, sizeof(buff), MSG_NOSIGNAL);
		if (sender < 0) {
			printf("pthread end\n");
			pthread_exit(NULL);
			//return NULL;
		}
	}

	return (void *)sockfd;
}
