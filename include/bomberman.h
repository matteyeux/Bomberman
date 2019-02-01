#include <include/interface.h>
#include <include/player.h>

void draw_game(interface_t *interface, player_t *player);
int game_event(player_t *player, interface_t *interface);
void destroy_game(interface_t *interface, player_t *player);
void destroy_game_by_wallHard(interface_t *interface, wallHard_t *wallHard);