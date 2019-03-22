#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifndef CLIENT_H_
#define CLIENT_H_

typedef struct client_s client_t;
typedef struct s_client_request t_client_request;

#include <include/server.h>
#include <include/player.h>

struct client_s {
	int sock;
	struct sockaddr_in server;
};

struct s_client_request {
	unsigned int magic; /* client ID asigned by the server */
	int x_pos;			/* x position desired by client */
	int y_pos;			/* y position desired by client */
	int dir;			/* direction desired by client */
	int command;		/* client command. 0 : do nothing, 1 : drop bomb */
	int speed;			/* speed player */
	int checksum;		/* simple checksum */
};

t_server_game *global_game;

client_t *init_client(char *ip_addr, unsigned short port);

int send_client_data(client_t *client_data, player_t *player);

t_server_game *receive_server_data(client_t *client_data);

int get_magic(client_t *client_struct);

void *client_listening(void *client_data);
#endif
