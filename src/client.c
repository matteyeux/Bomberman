#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <include/client.h>
#include <include/server.h>


client_t *init_client(char *ip_addr, unsigned short port)
{
	client_t *client_struct;
	struct sockaddr_in server;

	client_struct = malloc(sizeof(client_t));

	if (client_struct == NULL) {
		printf("[ERROR] : malloc for client_struct\n");
		return NULL;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		NULL;
	}

	// build server address struct
	server.sin_family = AF_INET; // IPv4
	server.sin_addr.s_addr = inet_addr(ip_addr); // serv IP to connect to
	server.sin_port = htons(port); // serv port

	// connect to server
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("connect");
		return NULL;
	}
	client_struct->server = server;
	client_struct->sock = sock;

	return client_struct;
}

int client(client_t *client_data)
{
	int sender, receiver;
	unsigned int server_addr_len;

	struct msg_struct *my_message;
	struct msg_struct *received_message;

	//sock = client_data->sock;

	printf("here\n");
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

	server_addr_len = sizeof(client_data->server);

	while (1) {

		// should segfault in this loop
		printf("will send, id : %d\t message : %s\n", my_message->id, my_message->message);

		// Send the int and string to the server
		sender = sendto(client_data->sock, my_message, sizeof(struct msg_struct), MSG_NOSIGNAL, (struct sockaddr *)&client_data->server, sizeof(client_data->server));

		if (sender == -1 ) {
			perror("sendto");
			return -1;
		}

		receiver = recvfrom(client_data->sock, received_message, sizeof(*received_message), 0, (struct sockaddr *) &client_data->server, &server_addr_len);

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

	close(client_data->sock);
	free(my_message);
	return 0;
}

#if 0
int send_data(client_t *client_data)
{
	ssize_t sender = -1;

	sender = sendto(client_data->sock, my_message, sizeof(struct msg_struct), MSG_NOSIGNAL, (struct sockaddr *)&client_data->server, sizeof(client_data->server));

	if (sender == -1 ) {
		perror("sendto");
		return -1;
	}

	return 0;
}

void receive_data(void)
{
	// data to receive
}
#endif
