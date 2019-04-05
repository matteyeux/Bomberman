#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#include <include/server.h>
#include <include/server_player.h>
#include <include/server_map.h>
#include <include/server_bomb.h>
#include <include/server_explosion.h>
#include <include/client.h>
#include <include/bomberman.h>
#include <include/map.h>
#include <include/menu.h>
#include <include/handler.h>

int sock;
int sock_fd_array[4];

/*
* function defined else it would cause
* each source file that included the header
*  file to have its own private copy of the function
*/
static int run_server(int sock, server_data_t *server_data);

void *init_server(void *input)
{
	menu_return_t *menu = input;
	struct sockaddr_in server; /* Local address */

	int port = menu->port;
	int enable = 1;

	memset(&sock_fd_array, -1, sizeof(sock_fd_array));
	server_data_t *server_data;

	server_data = malloc(sizeof(server_data_t));

	if (server_data == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return NULL;
	}

	/* Create socket for sending/receiving datagrams */
	sock = socket(AF_INET , SOCK_STREAM , 0);

	if (sock < 0) {
		perror("socket");
		return NULL;
	}

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		printf("[ERROR] setsockopt(SO_REUSEADDR) failed");
		return NULL;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);

	/* Bind to the local address */
	if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("bind");
		return NULL;
	}

	printf("[INFO] Successfully initialized server !\n");

	if (listen(sock, 4) == 0) {
		printf("[INFO] waiting for incomming connections...\n");
	} else {
		perror("listen");
		return NULL;
	}


	run_server(sock, server_data);
	free(server_data);

	return 0;
}


static int run_server(int sock, server_data_t *server_data)
{
	int sock_fd = 1;
	int client_cnt = 0;
	unsigned int client_addr_len;
	pthread_t thread_id;
	int magic_array[5];
	struct sockaddr_in client;

	client_cnt = 0;
	client_addr_len = sizeof(struct sockaddr_in);

	server_data->server_game = malloc(sizeof(t_server_game));

	if (server_data->server_game == NULL){
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return -1;
	}

	// Init base player datum
	init_player_informations(server_data);

	// Init server_bomb
	server_data->server_bomb = malloc(sizeof(bomb_server_t));

	// Init	server_explosion
	server_data->server_explosion = malloc(sizeof(explosion_server_t));
	server_data->server_explosion->first = true;

	if (server_data->server_bomb == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return -1;
	}

	if (server_data->server_explosion == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return -1;
	}

	while (sock_fd && status != -1) {
		memset(&magic_array, 0, sizeof(magic_array));

		/*
		* if client count is >= 4
		* set sock_fd to -1
		* loop until client_cnt is decremented
		*/
		if (client_cnt >= 4) {
			sock_fd = -1;
		} else {
			sock_fd = accept(sock, (struct sockaddr *)&client, (socklen_t *)&client_addr_len);

			/*
			* if we hit this condition, close server
			*/
			if (sock_fd == -1) {
				printf("[INFO] connections closed\n");
				return -1;
			}

			sock_fd_array[client_cnt] = sock_fd;

			client_cnt++;
			server_data->sock_id = client_cnt - 1;

			// set magic and send it here
			magic_array[server_data->sock_id] = rand();
			server_data->magic[(server_data->sock_id + 1)] = magic_array[server_data->sock_id];

			server_data->sock_fd[client_cnt - 1] = sock_fd;

			memcpy(&(server_data->client), &client, sizeof(struct sockaddr_in));
			server_data->client_addr_len = client_addr_len;

			printf("[INFO] connection accepted\n");

			send(server_data->sock_fd[client_cnt - 1], &magic_array[server_data->sock_id], sizeof(int), 0);

			if (pthread_create(&thread_id, NULL, handler, (void*) server_data) < 0) {
				perror("pthread_create");
				return -1;
			}
		}
	}

	if (sock_fd < 0) {
		printf("%d\n", server_data->sock_id);
		perror("accept");
		return 1;
	}

	close(sock_fd);
	close(sock);
	pthread_exit(NULL);
	return 0;
}

t_client_request *receive_client_data(server_data_t *server_data)
{
	ssize_t receiver;

	t_client_request *request;

	request = malloc(sizeof(t_client_request));

	if (request == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return NULL;
	}

	receiver = recvfrom(server_data->sock_fd[server_data->sock_id],
						request, sizeof(*(request)), 0,
						(struct sockaddr *) &server_data->client,
						&server_data->client_addr_len);

	if (receiver == -1) {
		free(request);
		return NULL;
	}

	return request;
}

int send_data_to_client(server_data_t *server_data, t_server_game *server_game)
{
	ssize_t sender;
	int i;

	for (i = 0; i < MAX_PLAYERS; ++i) {
		// Debug check sending to ckect number
		if (sock_fd_array[i] != -1){
			sender = sendto(sock_fd_array[i], server_game,
					sizeof(*(server_game)), MSG_NOSIGNAL,
					(struct sockaddr *)&server_data->client,
					server_data->client_addr_len);
		}

		if (sender == -1) {
			perror("sendto");
			close(server_data->sock_fd[i]);
		}
	}

	return 0;
}

void init_player_informations(server_data_t *server_data)
{
	// init datum of player
	server_data->server_game->player1.x_pos = 2;
	server_data->server_game->player1.y_pos = 2;
	server_data->server_game->player1.live = 1;
	server_data->server_game->player1.bombs_left = 3;
	server_data->server_game->player2.x_pos = 12;
	server_data->server_game->player2.y_pos = 2;
	server_data->server_game->player2.live = 1;
	server_data->server_game->player2.bombs_left = 3;
	server_data->server_game->player3.x_pos = 2;
	server_data->server_game->player3.y_pos = 10;
	server_data->server_game->player3.live = 1;
	server_data->server_game->player3.bombs_left = 3;
	server_data->server_game->player4.x_pos = 12;
	server_data->server_game->player4.y_pos = 10;
	server_data->server_game->player4.live = 1;
	server_data->server_game->player4.bombs_left = 3;
}