#include <pthread.h>
#include <unistd.h>

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

void *game_loop(void *game_struct)
{
	int status = 0;
	game_t *game = (game_t *)game_struct;
	printf("here\n");
	while (status != -1) {
		draw_game(game->interface, game->player, game->bomb);

		status = game_event(game->player, game->interface, game->bomb);
		SDL_Delay(20);
	}

	return (void *)game_struct;
}

/*
* temp workaround, waiting for the menu
* blame lepage_b
*/
void *start_networking(void *type)
{

	if (!strcmp((char *)type, "server")) {
		init_server(PORT);
	} else if (!strcmp((char *)type, "client")) {
		client(IP, PORT);
	} else {
		printf("no\n");
		return NULL;
	}

	return (void *)type;
}