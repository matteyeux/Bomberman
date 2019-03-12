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

	if (client_struct == NULL) {
		printf("struct is null\n");
	}

	return client_struct;
}

/*
* function used to send the t_client_request struct
*/
int send_client_data(client_t *client_data)
{
	ssize_t sender = -1;
	t_client_request *request;

	request = malloc(sizeof(t_client_request));

	if (request == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return -1;
	}

	/* hardcoded values waiting someone else (not giving any name this time) */
	request->magic = 0;
	request->x_pos = 1;
	request->y_pos = 2;
	request->dir = 3;
	request->command = 4;
	request->speed = 5;
	request->ckecksum = 6;

	sender = sendto(client_data->sock, request,
					sizeof(t_client_request), MSG_NOSIGNAL,
					(struct sockaddr *)&client_data->server,
					sizeof(client_data->server));

	if (sender == -1 ) {
		perror("sendto");
		return -1;
	}

	return 0;
}

t_game *receive_server_data(client_t *client_data)
{
	ssize_t receiver;
	unsigned int server_addr_len;
	t_game *game;

	game = malloc(sizeof(t_game));

	if (game == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	server_addr_len = sizeof(client_data->server);

	receiver = recvfrom(client_data->sock, game, sizeof(*game),
						0, (struct sockaddr *) &client_data->server,
						&server_addr_len);

	if (receiver == -1 ) {
		perror("sendto");
		return NULL;
	}

	return game;
}
