#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>

void draw_game(interface_t *interface, player_t *player, bomb_t *bomb);
int game_event(player_t *player, interface_t *interface, bomb_t *bomb);
void destroy_game(interface_t *interface, player_t *player, bomb_t *bomb);