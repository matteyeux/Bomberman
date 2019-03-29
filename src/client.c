#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <include/client.h>
#include <include/server.h>
#include <include/player.h>

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
int send_client_data(client_t *client_data, player_t *player)
{
	ssize_t sender = -1;
	t_client_request *request;

	request = malloc(sizeof(t_client_request));

	if (client_data == NULL) {
		return -1;
	}

	if (request == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return -1;
	}

	/* hardcoded values waiting someone else (not giving any name this time) */
	request->magic = player->magic;
	request->x_pos = player->posX;
	request->y_pos = player->posY;
	request->dir = player->dir;
	request->command = player->command;
	request->speed = player->speed;
	request->checksum = request->magic /
			(request->x_pos +
			 request->y_pos +
			 request->dir +
			 request->command +
			 request->speed);

	// TODO Yop debug envoi direction, x, y, command, speed
	//printf("Emit :\n%d : %d - %d  c%d s%d cs%d\n", request->dir, request->x_pos, request->y_pos, request->command, request->speed, request->checksum);

	sender = sendto(client_data->sock, request,
					sizeof(t_client_request), MSG_NOSIGNAL,
					(struct sockaddr *)&client_data->server,
					sizeof(client_data->server));

	if (sender == -1 ) {
		printf("bla\n");
		perror("sendto");
		return -1;
	}

	free(request);
	return 0;
}

t_server_game *init_server_game(void)
{
	t_server_game *server_game;

	server_game = malloc(sizeof(t_server_game));

	if (server_game == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	return server_game;
}

t_server_game *receive_server_data(client_t *client_data)
{
	ssize_t receiver;
	unsigned int server_addr_len;

	server_addr_len = sizeof(client_data->server);

	receiver = recvfrom(client_data->sock, client_data->server_game, sizeof(*client_data->server_game),
						0, (struct sockaddr *) &client_data->server,
						&server_addr_len);

	if (receiver == -1 ) {
		perror("recvfrom");
		return NULL;
	}

	return client_data->server_game;
}

int get_magic(client_t *client_struct)
{
	int magic = -1;
	if (client_struct != NULL)
		recv(client_struct->sock, &magic, sizeof(int), 0);
	else
		magic = -1;
	return magic;
}

void *client_listening(void *client_data)
{
	while (1) {
		global_game = receive_server_data((client_t *)client_data);
	}

	return (void *)global_game;
}
