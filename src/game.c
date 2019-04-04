#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/bomberman.h>
#include <include/client.h>
#include <include/server.h>
#include <include/game.h>

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

	game->player = init_player();
	if (game->player == NULL)
		return NULL;

	game->player->playerTexture = set_texture_player(game->interface->Renderer);
	if (game->player->playerTexture == NULL)
		return NULL;

	fprintf(stdout, "Successfully initialized player !\n");

	game->bomb = init_bomb(game->interface->Renderer);
	if (game->bomb == NULL) 
		return NULL;

	fprintf(stdout, "Successfully initialized bomb !\n");

	game->explosion = init_explosion(game->interface->Renderer);
	if (game->explosion == NULL)
		return NULL;

	fprintf(stdout, "Successfully initialized explosions !\n");

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
	int status = 0, magic;
	global_game_t *game = (global_game_t *)game_struct;
	client_t *client_struct;
	pthread_t thread_client;

	client_struct = init_client(game->ip, game->port);

	if (client_struct != NULL) {
		magic = get_magic(client_struct);
		client_struct->server_game = init_server_game();

		printf("magic : %d\n", magic);
		game->player->magic = magic;

		global_game = malloc(sizeof(t_server_game));

		if (global_game == NULL) {
			fprintf(stderr, "MALLOC ERROR\n");
			return NULL;
		}

		if (pthread_create(&thread_client, NULL, client_listening, (void*) client_struct) < 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	} else {
		// if client cannot connect to server
		// then destroy game and kill everything else
		destroy_game(game);
		exit(-1);
	}

	while (status != -1) {

		draw_game(game, global_game);

		status = game_event(game, client_struct);

		printf("Debug Map\n");
		if (global_game != NULL) {
			for (int y = 0; y < 13; y++) {
				for (int x = 0; x < 15; x++) {
					printf("%c", global_game->schema[y][x]);
				}
				printf("\n");
			}
			printf("\n");
		}

		SDL_Delay(20);
	}

	/*
	* SHUT_RDWR is used to disable further
	* receptions and transmissions
	*/
	free(global_game);
	free(client_struct);
	shutdown(sock, SHUT_RDWR);
	close(sock);
	return (void *)game_struct;
}

void setup_game(menu_return_t *menu)
{
	pthread_t thread_sdl, thread_net;
	global_game_t *game = NULL;

	game = init_game();

	if (game == NULL) {
		fprintf(stderr, "failed to to init game\n");
		exit(EXIT_FAILURE);
	}

	if (menu->ret == 1) {
		if (pthread_create(&thread_net, NULL, init_server, (void*) menu) < 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}

	game->ip = menu->ip;
	game->port = menu->port;

	if (pthread_create(&thread_sdl, NULL, game_loop, (void*) game) < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	/* join SDL thead */
	if (pthread_join(thread_sdl, NULL) != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
}