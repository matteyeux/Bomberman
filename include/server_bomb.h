#ifndef BOMBERMAN_SERVER_BOMB_H
#define BOMBERMAN_SERVER_BOMB_H

#include <include/server.h>

bomb_server_t *init_bomb_server();

struct bomb_server_s {
    int x;
    int y;
    int player;
    long time;
    int size;
    bomb_server_t *next;
};

void create_new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player);
void bombs_timer(t_server_game *server_game, bomb_server_t *server_bomb, explosion_server_t *server_explosion);

#endif //BOMBERMAN_SERVER_BOMB_H
