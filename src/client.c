#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <include/server.h>

int client(char *ip_addr, unsigned short port)
{
	int sock, sender, receiver;
	struct sockaddr_in server;
	unsigned int server_addr_len;

	struct msg_struct *my_message;
	struct msg_struct *received_message;

	my_message = malloc(sizeof(struct msg_struct));
	if (my_message == NULL) {
		printf("error malloc\n");
		return -1;
	}

	received_message = malloc(sizeof(struct msg_struct));
	if (received_message == NULL) {
		printf("error malloc\n");
		return -1;
	}

	my_message->id = 1234;
	strcpy(my_message->message, "message");


	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		return -1;
	}

	// build server address struct
	server.sin_family = AF_INET; // IPv4
	server.sin_addr.s_addr = inet_addr(ip_addr); // serv IP to connect to
	server.sin_port   = htons(port); // serv port

	// connect to server
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("connect");
		return -2;
	}

	server_addr_len = sizeof(server);

	while (1) {
		printf("will send, id : %d\t message : %s\n", my_message->id, my_message->message);

		// Send the int and string to the server
		sender = sendto(sock, my_message, sizeof(struct msg_struct), MSG_NOSIGNAL, (struct sockaddr *)&server, sizeof(server));

		if (sender == -1 ) {
			perror("sendto");
			return -1;
		}

		receiver = recvfrom(sock, received_message, sizeof(*received_message), 0, (struct sockaddr *) &server, &server_addr_len);

		if (receiver == -1 ) {
			perror("recvfrom");
			return -1;
		}

		// server should send id++ -> 667
		// message should be the same for some lazy reasons
		printf("received id : %d\n", received_message->id);
		printf("received message : %s\n", received_message->message);

		sleep(1);
	}

	close(sock);
	free(my_message);
	return 0;
}