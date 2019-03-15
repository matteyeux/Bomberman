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
	if (game->interface == NULL) 
		return NULL;

	fprintf(stdout, "Successfully initialized interface !\n");

	game->map = init_map("map.txt");
	if (game->map == NULL)
		return NULL;

	game->map->mapTexture = set_texture_map(game->interface->Renderer);
	if (game->map->mapTexture == NULL)
		return NULL;

	fprintf(stdout, "Successfully initialize map!\n");

	game->player = init_player(game->interface);
	if (game->player == NULL)
		return NULL;

	fprintf(stdout, "Successfully initialized player !\n");

	game->bomb = init_bomb(game->interface);
	if (game->bomb == NULL) 
		return NULL;

	fprintf(stdout, "Successfully initialized bomb !\n");

	return game;
}

void *game_loop(void *game_struct)
{
	int status = 0;
	game_t *game = (game_t *)game_struct;
	client_t *client_struct;

	client_struct = init_client(IP, PORT);

	while (status != -1) {
		draw_game(game);

		status = game_event(game->player, game->interface, game->bomb, client_struct);
		SDL_Delay(20);
	}

	/*
	* SHUT_RDWR is used to disable further
	* receptions and transmissions
	*/
	shutdown(sock, SHUT_RDWR);
	close(sock);
	return (void *)game_struct;
}


/*
* temp workaround, waiting for the menu
* blame lepage_b
*/
void *start_networking(void *input)
{
	char *type =  (char *)input;

	if (!strcmp(type, "server")) {
		init_server(PORT);
	} else if (!strcmp(type, "client")) {
		printf("client\n");

	} else {
		printf("no\n");
		return NULL;
	}

	return (void *)type;
}