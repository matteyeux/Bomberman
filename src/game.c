#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/bomberman.h>
#include <include/client.h>
#include <include/server.h>
#include <include/game.h>

#define IP "127.0.0.1"
#define PORT 12345

game_t *init_game(void)
{
	game_t *game = NULL;

	game = malloc(sizeof(game_t));

	if (game == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	game->interface = init_interface();
	if (game->interface == NULL) {
		return NULL;
	}

	fprintf(stdout, "Successfully initialized interface !\n");

	game->player = init_player(game->interface);
	if (game->player == NULL) {
		return NULL;
	}

	fprintf(stdout, "Successfully initialized player !\n");

	game->bomb = init_bomb(game->interface);
	if (game->bomb == NULL) {
		return NULL;
	}

	fprintf(stdout, "Successfully initialized bomb !\n");

	return game;
}

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

/*
* temp workaround, waiting for the menu
* blame lepage_b
*/
int start_networking(char *type)
{
	if (!strcmp(type, "server")) {
		init_server(PORT);
	} else if (!strcmp(type, "client")) {
		client(IP, PORT);
	} else {
		printf("no\n");
		return -1;
	}

	return 0;
}