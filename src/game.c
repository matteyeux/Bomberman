#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/bomberman.h>

void game_loop(interface_t *interface, player_t *player, bomb_t *bomb)
{
	int status = 0;

	while (status != -1) {
		draw_game(interface, player, bomb);

		status = game_event(player, interface, bomb);

		SDL_Delay(20);
	}

	return;
}