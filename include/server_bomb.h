#ifndef BOMBERMAN_SERVER_BOMB_H
#define BOMBERMAN_SERVER_BOMB_H

#include <include/server.h>

typedef struct bomb_server_s bomb_server_t;

struct bomb_server_s
{
    int x;
    int y;
    int player;
    long time;
    bomb_server_t *next;
};

bomb_server_t *init_bomb_server();

void create_new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player);

#endif //BOMBERMAN_SERVER_BOMB_H
