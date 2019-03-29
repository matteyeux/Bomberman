#ifndef BOMBERMAN_SERVER_BOMB_H
#define BOMBERMAN_SERVER_BOMB_H

#include <include/server.h>

typedef struct bomb_server_s bomb_server_t;
//typedef struct player_s player_t;

struct bomb_server_s
{
    int x;
    int y;
    int player;
    long time;
    //bomb_server_t *next;
};

bomb_server_t *init_bomb_server();
//void placeBomb(bomb_t *bomb, player_t *player);
//void destroy_bomb(bomb_t *bomb);

void new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player);

#endif //BOMBERMAN_SERVER_BOMB_H
