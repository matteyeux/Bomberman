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
#include <include/bomberman.h>

int sock;

/*
* function defined else it would cause
* each source file that included the header
*  file to have its own private copy of the function
*/
static int run_server(int sock, net_data_t *network_data);

int init_server(unsigned short port)
{
	struct sockaddr_in server; /* Local address */

	int enable = 1;

	net_data_t *network_data;

	network_data = malloc(sizeof(net_data_t));

	if (network_data == NULL) {
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

	run_server(sock, network_data);
	free(network_data);

	return 0;
}

int client_cnt = 0;
static int run_server(int sock, net_data_t *network_data)
{
	int client_sock = 1;
	unsigned int client_addr_len;
	pthread_t thread_id;

	struct sockaddr_in client;
	struct msg_struct *message;

	message = malloc(sizeof(struct msg_struct));

	if (message == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
	}

	client_addr_len = sizeof(struct sockaddr_in);

	while (client_sock && status != -1) {
		/* Set the size of the in-out parameter */

		/*
		* if client count is >= 4
		* set client_sock to -1
		* loop until client_cnt is decremented
		*/
		if (client_cnt >= 4) {
			client_sock = -1;
		} else {
			client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&client_addr_len);

			/*
			* when you press exit you'll get :
			* accept: Invalid argument
			*/
			if (client_sock == -1) {
				client_cnt--;
				perror("accept");
				return -1;
			}

			client_cnt++;

			network_data->client_sock = client_sock;
			memcpy(&(network_data->client), &client, sizeof(struct sockaddr_in));
			network_data->client_addr_len = client_addr_len;

			network_data->message = message;

			printf("connection accepted\n");

			if (pthread_create(&thread_id, NULL, handler, (void*) network_data) < 0) {
				perror("pthread_create");
				return -1;
			}
		}
	}

	if (client_sock < 0) {
		printf("here\n");
		printf("%d\n", client_cnt );
		perror("accept");
		return 1;
	}

	free(message);
	close(client_sock);
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
	net_data_t *server_data;

	int client_sock, sender;
	unsigned int client_addr_len;
	struct sockaddr_in client;
	ssize_t receiver;

	server_data = malloc(sizeof(net_data_t));
	if (server_data == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
	}

	memcpy(server_data, (net_data_t *)input, sizeof(net_data_t));

	while (status != -1) {
		client_sock = server_data->client_sock;

		client_addr_len = server_data->client_addr_len;
		client = server_data->client;

		server_data->message->id = 0;
		bzero(server_data->message->key, 10);

		receiver = recvfrom(client_sock, server_data->message,
							sizeof(*(server_data->message)), 0,
							(struct sockaddr *) &client, &client_addr_len);

		if (receiver == -1) {
			perror("recvfrom");
			return NULL;
		}

		// client things issues
		// TODO : fix
		if (server_data->message->id == 0) {
			printf("recv : failed, it should have received a non-0 int\n");
			printf("pthread_exit\n");
			client_cnt--;
			close(client_sock);
			pthread_exit(NULL);
		} else {
			printf("Received: %d\t%s\n", server_data->message->id, server_data->message->key);
		}

		server_data->message->id += 1;

		printf("server will send : %d\n", server_data->message->id);

		/* Send the int and string to the server */
		sender = sendto(client_sock, server_data->message,
						sizeof(*(server_data->message)), MSG_NOSIGNAL,
						(struct sockaddr *)&client, client_addr_len);

		if (sender == -1 ) {
			perror("sendto");
			printf("pthread_exit\n");
			client_cnt--;
			close(client_sock);
			pthread_exit(NULL);
		}
	}

	free(server_data);
	return (void *)input;
}
