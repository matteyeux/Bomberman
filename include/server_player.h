#ifndef SERVER_PLAYER_H_
#define SERVER_PLAYER_H_

#include <stdbool.h>
#include <include/server.h>

void player_action(t_server_game *server_game, int player, char command);
void player_move(t_server_game *server_game, int player, char command, int x, int y);
bool place_is_free(t_server_game *server_game, int x, int y);

void bomb_drop();
/*
typedef struct server_player_s server_player_t;

struct server_player_s
{
    int id; // TODO Yop a supprimer si inutile a l'avenir
    char connected;
    char alive;
    int x_pos;
     int y_pos;
    int current_dir;
    int current_speed;
    int max_speed;
    int bombs_left;
    int bombs_capacity;
    int frags;
};

server_player_t *init_server_player();
// TODO Yop void movePlayer(player_t *player, interface_t *interface, SDL_Keycode direction, client_t *client_struct);
// TODO Yop void destroy_player(player_t *player);
// TODO Yop bomb_t *dropBomb(player_t *player, bomb_t *bomb);

*/

#endif /* PLAYER_H_ */