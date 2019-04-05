#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <include/menu.h>
#include <include/player.h>
#include <stdbool.h>

#ifdef __APPLE__
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

#ifndef SERVER_H_
#define SERVER_H_

#define MAP_SIZE 12
#define MAX_PLAYERS 4
extern int sock;

struct msg_struct {
	int id;
	char key[10];
};

typedef struct server_data_s server_data_t;
typedef struct s_server_game t_server_game;
typedef struct s_player_infos t_player_infos;
typedef struct bomb_server_s bomb_server_t;
typedef struct explosion_server_s explosion_server_t;
typedef char t_map[MAP_SIZE];

struct server_data_s {
	int magic[5];
	int sock_fd[MAX_PLAYERS];
	int sock_id;
	struct sockaddr_in client;
	unsigned int client_addr_len;
	t_server_game *server_game;
	bomb_server_t *server_bomb;
	explosion_server_t *server_explosion;
};

struct s_player_infos {
	int live;
	int x_pos;
	int y_pos;
	int current_dir;
	int bombs_left;

	SDL_Rect	dest;
	SDL_Rect	src;
};

t_player_infos *player1;
t_player_infos *player2;
t_player_infos *player3;
t_player_infos *player4;

struct s_server_game {
	t_player_infos player1;
	t_player_infos player2;
	t_player_infos player3;
	t_player_infos player4;

	char schema[13][15];
};

void *init_server(void *input);
void init_player_informations(server_data_t *server_data);
int send_data_to_client(server_data_t *server_data, t_server_game *server_game);
t_client_request *receive_client_data(server_data_t *server_data);

#endif
