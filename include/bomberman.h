#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/game.h>

extern int status;

void draw_game(global_game_t *game);
int game_event(global_game_t *game, client_t *client_struct);
void destroy_game(interface_t *interface, player_t *player, bomb_t *bomb);
