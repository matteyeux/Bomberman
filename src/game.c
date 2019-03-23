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
	int status = 0, magic;
	global_game_t *game = (global_game_t *)game_struct;
	client_t *client_struct;
	pthread_t thread_client;

	int a = 0, b = 0, c = 0, d = 0;

	client_struct = init_client(IP, PORT);
	if (client_struct != NULL) {
		magic = get_magic(client_struct);

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
	}

	while (status != -1) {

		draw_game(game);

		status = game_event(game->player, game->interface, game->bomb, client_struct);

		/*
		* YOP : this is for you
		* to not get flooded by all this crap I made a simple condition when it's printed once
		* it will not be printed anymore
		*/
		if (global_game != NULL) {

			// Debug Yop (Non modéré, en mode flood, j'affiche non stop positions)
			printf("P1 X:%d Y:%d\n", global_game->player1.x_pos, global_game->player1.y_pos, global_game->player1.current_dir);
			printf("P2 X:%d Y:%d\n", global_game->player2.x_pos, global_game->player2.y_pos, global_game->player2.current_dir);
			printf("P3 X:%d Y:%d\n", global_game->player3.x_pos, global_game->player3.y_pos, global_game->player3.current_dir);
			printf("P4 X:%d Y:%d\n", global_game->player4.x_pos, global_game->player4.y_pos, global_game->player4.current_dir);

			// Debug Matthieu (Modéré)
			//if (global_game->player1.x_pos == 12 && a == 0) {
			//	a = 1;
			//	printf("global_game->player1.x_pos : %d\n", global_game->player1.x_pos);
			//}

			//if (global_game->player2.x_pos == 13 && b == 0) {
			//	b = 1;
			//	printf("global_game->player2.x_pos : %d\n", global_game->player2.x_pos);
			//}

			//if (global_game->player3.x_pos == 14 && c == 0) {
			//	c = 1;
			//	printf("global_game->player3.x_pos : %d\n", global_game->player3.x_pos);
			//}

			//if (global_game->player4.x_pos == 15 && d == 0) {
			//	d = 1;
			//	printf("global_game->player4.x_pos : %d\n", global_game->player4.x_pos);
			//}

		}

		SDL_Delay(20);
	}

	/*
	* SHUT_RDWR is used to disable further
	* receptions and transmissions
	*/
	free(global_game);
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