#ifndef BOMBERMAN_SERVER_MAP_H
#define BOMBERMAN_SERVER_MAP_H

#include <include/server.h>

void implement_map(t_server_game *server_game, bomb_server_t *server_bomb, explosion_server_t *server_explosion);

void put_player_on_map(t_server_game *server_game);

#endif //BOMBERMAN_SERVER_MAP_H
