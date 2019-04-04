#ifndef BOMBERMAN_SERVER_EXPLOSION_H
#define BOMBERMAN_SERVER_EXPLOSION_H

#include <include/server.h>

explosion_server_t *init_explosion_server(t_server_game *server_game, int size, int x, int y);

struct explosion_server_s {
    bool first;
    int x;
    int y;
    int size;
    int size_up;
    int size_right;
    int size_down;
    int size_left;
    long time;
    explosion_server_t *next;
    explosion_server_t *prev;
};

void create_new_explosion(t_server_game *server_game, explosion_server_t *server_explosion, int size, int x, int y);
int wall_in_place(t_server_game *server_game, int x, int y);
void kill_player_on_place(t_server_game *server_game, int x, int y);
void explosions_timer(explosion_server_t *server_explosion);

#endif //BOMBERMAN_SERVER_EXPLOSION_H
