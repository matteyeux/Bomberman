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

static int run_server(int sock, net_data_t *network_data)
{
	int client_sock = 1;
	int client_cnt = 1;
	unsigned int client_addr_len;
	pthread_t thread_id;

	struct sockaddr_in client;
	struct msg_struct *message;

	message = malloc(sizeof(struct msg_struct));

	if (message == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
	}

	while (client_sock && status != -1) {
		/* Set the size of the in-out parameter */
		client_addr_len = sizeof(struct sockaddr_in);

		if (client_cnt > 3) {
			printf("cannot accept more than 4 clients\n");
			client_sock = -1;
		} else {
			client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&client_addr_len);

			/*
			* when you press exit you'll get :
			* accept: Invalid argument
			*/
			if (client_sock == -1) {
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
	struct net_data_s *message;

	int client_sock, sender;
	unsigned int client_addr_len;
	struct sockaddr_in client;
	ssize_t receiver;

	message = malloc(sizeof(net_data_t));
	if (message == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
	}

	memcpy(message, (net_data_t *)input, sizeof(net_data_t));

	while (status != -1) {
		client_sock = message->client_sock;

		client_addr_len = message->client_addr_len;
		client = message->client;

		message->message->id = 0;
		bzero(message->message->message, 100);

		receiver = recvfrom(client_sock, message->message,
							sizeof(*(message->message)), 0,
							(struct sockaddr *) &client, &client_addr_len);

		if (receiver == -1) {
			perror("recvfrom");
			return NULL;
		}

		// client things issues
		// TODO : fix
		if (message->message->id == 0) {
			printf("recv : failed, it should have received a non-0 int\n");
			printf("pthread_exit\n");
			close(client_sock);
			pthread_exit(NULL);
		} else {
			printf("Received: %d\t%s\n", message->message->id, message->message->message);
		}

		message->message->id += 1;

		printf("server will send : %d\n", message->message->id);

		/* Send the int and string to the server */
		sender = sendto(client_sock, message->message,
						sizeof(*(message->message)), MSG_NOSIGNAL,
						(struct sockaddr *)&client, client_addr_len);

		if (sender == -1 ) {
			perror("sendto");
			printf("pthread_exit\n");
			close(client_sock);
			pthread_exit(NULL);
		}

		sleep(1);
	}

	free(message);
	return (void *)input;
}
