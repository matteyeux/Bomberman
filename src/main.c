#include <stdio.h>
#include <stdlib.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>

int main(void)
{
	interface_t *interface = NULL;
	player_t *player = NULL;

	interface = init_interface();

	if (interface == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized interface !\n");
	SDL_Delay(3000);

	player = init_player(interface);

	if (player == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized player !\n");
	SDL_Delay(3000);

	destroy_game(interface, player);
}
