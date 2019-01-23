#include <include/interface.h>
#include <include/player.h>

void draw_game(interface_t *interface, player_t *player);
int game_event(player_t *player, interface_t *interface);
void destroy_game(interface_t *interface, player_t *player);