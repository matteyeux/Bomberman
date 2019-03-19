#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/game.h>

extern int status;

void draw_game(global_game_t *game);
int game_event(player_t *player, interface_t *interface, bomb_t *bomb, client_t *client_struct);
void destroy_game(interface_t *interface, player_t *player, bomb_t *bomb);