#include <stdio.h>
#include <stdlib.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>

int main(void)
{
	interface_t *interface = NULL;
	player_t *player = NULL;
	int status = 0;

	interface = init_interface();

	if (interface == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized interface !\n");

	player = init_player(interface);

	if (player == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized player !\n");

	while (status != -1) {
		draw_game(interface, player);

		status = game_event(player, interface);

		SDL_Delay(20);
	}

	destroy_game(interface, player);
}
