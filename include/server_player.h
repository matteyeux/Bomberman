#ifndef SERVER_PLAYER_H_
#define SERVER_PLAYER_H_

#include <stdbool.h>
#include <include/server.h>
#include <include/server_bomb.h>

void player_action(t_server_game *server_game,bomb_server_t *server_bomb , int player, char command);
t_player_infos *get_the_player(t_server_game *server_game, int player);
void player_move(t_server_game *server_game, bomb_server_t *server_bomb, int player, char command);

bool place_is_free(t_server_game *server_game, int x, int y);
bool place_is_free_of_player(t_server_game *server_game, int x, int y);
bool place_is_free_of_bomb(bomb_server_t *server_bomb, int x, int y);

void bomb_drop(t_server_game *server_game, bomb_server_t *server_bomb, int player);

#endif /* PLAYER_H_ */