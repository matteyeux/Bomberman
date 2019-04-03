#ifndef BOMBERMAN_SERVER_EXPLOSION_H
#define BOMBERMAN_SERVER_EXPLOSION_H

#include <include/server.h>

explosion_server_t *init_explosion_server(int size, int x, int y);

struct explosion_server_s {
    bool first;
    int x;
    int y;
    int size;
    long time;
    bomb_server_t *next;
    bomb_server_t *prev;
};

void create_new_explosion(explosion_server_t *server_explosion, int size, int x, int y);
void explosions_timer(explosion_server_t *server_explosion);

#endif //BOMBERMAN_SERVER_EXPLOSION_H
