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

global_game_t *init_game(void)
{
	global_game_t *game = NULL;

	game = malloc(sizeof(global_game_t));

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

int get_client_id(client_t *client_struct)
{
	int client_id;

	recv(client_struct->sock, &client_id, sizeof(int), 0);

	return client_id;
}

void *game_loop(void *game_struct)
{
	int status = 0;
	global_game_t *game = (global_game_t *)game_struct;
	client_t *client_struct;
	pthread_t thread_client;

	client_struct = init_client(IP, PORT);
	if (client_struct != NULL) {
		global_game = malloc(sizeof(t_game));

		if (global_game == NULL) {
			fprintf(stderr, "MALLOC ERROR\n");
			return NULL;
		}

		if (pthread_create(&thread_client, NULL, client_listening, (void*) client_struct) < 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}

	while (status != -1) {
		// should be 0 the first time, then 12
		if (global_game != NULL) {
			// comment cuz not finished yet
			printf("global_game->player_infos->x_pos : %d\n", 12); // global_game->player_infos->x_pos);
		}
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