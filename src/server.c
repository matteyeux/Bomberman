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
#include <include/client.h>
#include <include/bomberman.h>

int sock;

/*
* function defined else it would cause
* each source file that included the header
*  file to have its own private copy of the function
*/
static int run_server(int sock, server_data_t *server_data);
static t_client_request *receive_client_data(server_data_t *server_data);
static int send_data_to_client(server_data_t *server_data, t_game *game);

int init_server(unsigned short port)
{
	struct sockaddr_in server; /* Local address */

	int enable = 1;

	server_data_t *server_data;

	server_data = malloc(sizeof(server_data_t));

	if (server_data == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return -1;
	}

	/* Create socket for sending/receiving datagrams */
	sock = socket(AF_INET , SOCK_STREAM , 0);

	if (sock < 0) {
		perror("socket");
		return -1;
	}

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		printf("setsockopt(SO_REUSEADDR) failed");
		return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);

	/* Bind to the local address */
	if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("bind");
		return -1;
	}

	if (listen(sock, 4) == 0) {
		printf("waiting for incomming connections...\n");
	} else {
		perror("listen");
		return -1;
	}

	run_server(sock, server_data);
	free(server_data);

	return 0;
}


static int run_server(int sock, server_data_t *server_data)
{
	int sock_fd = 1;
	unsigned int client_addr_len;
	pthread_t thread_id;
	int magic_array[5];
	struct sockaddr_in client;

	server_data->client_cnt = 0;
	client_addr_len = sizeof(struct sockaddr_in);

	while (sock_fd && status != -1) {
		memset(&magic_array, 0, sizeof(magic_array));

		/*
		* if client count is >= 4
		* set sock_fd to -1
		* loop until client_cnt is decremented
		*/
		if (server_data->client_cnt >= 4) {
			sock_fd = -1;
		} else {
			sock_fd = accept(sock, (struct sockaddr *)&client, (socklen_t *)&client_addr_len);

			/*
			* when you press exit you'll get :
			* accept: Invalid argument
			*/
			if (sock_fd == -1) {
				//server_data->client_cnt--;
				perror("accept");
				return -1;
			}

			server_data->client_cnt++;

			// set magic and send it here
			magic_array[server_data->client_cnt] = rand();
			printf("magic_array : %d\n", magic_array[server_data->client_cnt]);

			// TODO : send magic
			// just send a simple int : magic_array[server_data->client_cnt]
			// which is set with a random value.
			// send(server_data->sock_fd, magic_array[server_data->client_cnt], sizeof(int), 0);

			server_data->sock_fd = sock_fd;
			memcpy(&(server_data->client), &client, sizeof(struct sockaddr_in));
			server_data->client_addr_len = client_addr_len;

			printf("connection accepted\n");

			if (pthread_create(&thread_id, NULL, handler, (void*) server_data) < 0) {
				perror("pthread_create");
				return -1;
			}
		}
	}

	if (sock_fd < 0) {
		printf("%d\n", server_data->client_cnt );
		perror("accept");
		return 1;
	}

	close(sock_fd);
	close(sock);
	pthread_exit(NULL);
	return 0;
}

/*
* this function is called in a pthread
* I pass a struct net_data_s that I cast in
* a (void *).
* it recv() from the client (recvfrom) a struct
* then send back the same struct type with an id incremented by 1.
*/
void *handler(void *input)
{
	server_data_t *server_data;
	t_client_request *request;
	t_game *game;

	server_data = malloc(sizeof(server_data_t));
	if (server_data == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
	}

	memcpy(server_data, (server_data_t *)input, sizeof(server_data_t));

	while (status != -1) {
		request = receive_client_data(server_data);

		if (request == NULL) {
			free(request);
			free(server_data);
			pthread_exit(NULL);
			printf("failed request\n");
		}

		printf("Recept :\ndir  X   Y   comm speed checksum    ID\n%d   %d  %d %d   %d    %d   %d\n",
				request->dir,
				request->x_pos,
				request->y_pos,
				request->command,
				request->speed,
				request->checksum,
				request->magic);

		game = malloc(sizeof(t_game));

		if (game == NULL) {
			fprintf(stderr, "[MALLOC] unable to allocate memory\n");
			return NULL;
		}

		send_data_to_client(server_data, game);
	}

	free(request);
	free(server_data);
	return (void *)input;
}

static t_client_request *receive_client_data(server_data_t *server_data)
{
	ssize_t receiver;

	t_client_request *request;

	request = malloc(sizeof(t_client_request));

	if (request == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	receiver = recvfrom(server_data->sock_fd, request, sizeof(*(request)), 0,
				(struct sockaddr *) &server_data->client, &server_data->client_addr_len);

	if (receiver == -1) {
		perror("recvfrom");
		return NULL;
	}

	return request;
}

/*
* temporary function to put data in struct
*/
static t_game *put_data_in_game(t_game *game)
{
	game->player1->connected = 'e';
	game->player1->alive = 'e';
	game->player1->x_pos = 12;
	game->player1->y_pos = 12;
	game->player1->current_dir = 12;
	game->player1->current_speed = 12;
	game->player1->max_speed = 12;
	game->player1->bombs_left = 12;
	game->player1->bombs_capacity = 12;
	game->player1->frags = 12;

	return game;
}

int send_data_to_client(server_data_t *server_data, t_game *game)
{
	ssize_t sender;

	game = put_data_in_game(game);

	sender = sendto(server_data->sock_fd, game,
					sizeof(*(game)), MSG_NOSIGNAL,
					(struct sockaddr *)&server_data->client,
					server_data->client_addr_len);

	if (sender == -1) {
		perror("sendto");
		close(server_data->sock_fd);
		pthread_exit(NULL);
	}

	return 0;
}
