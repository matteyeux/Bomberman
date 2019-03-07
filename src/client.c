#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <include/client.h>
#include <include/server.h>
client_t *init_client(char *ip_addr, unsigned short port)
{
	int sock;
	client_t *client_struct;
	struct sockaddr_in server;
	//struct msg_struct *message;

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
		printf("gang\n");
		return NULL;
	}

	client_struct->server = server;
	client_struct->sock = sock;

	if (client_struct == NULL) {
		printf("struct is null\n");
	}
	return client_struct;
}

int send_data(client_t *client_data, char *key)
{
	ssize_t sender = -1;
	struct msg_struct *message;

	if (client_data != NULL) {
		message = malloc(sizeof(struct msg_struct));

		if (message == NULL) {
			fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		}

		// set values
		message->id = 12;
		sprintf(message->key, key);

		// copy mem of message struct into actul client_data->msg struct
		memcpy(&(client_data->msg), &message, sizeof(struct msg_struct));

		sender = sendto(client_data->sock, client_data->msg,
						sizeof(struct msg_struct), MSG_NOSIGNAL,
						(struct sockaddr *)&client_data->server,
						sizeof(client_data->server));

		if (sender == -1 ) {
			perror("sendto");
			return -1;
		}
	}

	return 0;
}

void receive_data(void)
{
	// data to receive
}

/*
* keep this code here
* until I set the receive_data function
*/
#if 0
int client(client_t *client_data)
{
	int receiver;
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

		printf("will send, id : %d\t message : %s\n", my_message->id, my_message->message);

		// Send the int and string to the server
		// sender = sendto(client_data->sock, my_message, sizeof(struct msg_struct), MSG_NOSIGNAL, (struct sockaddr *)&client_data->server, sizeof(client_data->server));

		// if (sender == -1 ) {
		// 	perror("sendto");
		// 	return -1;
		// }

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

#endif