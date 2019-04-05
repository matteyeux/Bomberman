#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <include/server.h>
#include <include/server_player.h>
#include <include/server_map.h>
#include <include/server_bomb.h>
#include <include/server_explosion.h>
#include <include/client.h>
#include <include/bomberman.h>

/*
* this function is called in a pthread
* I pass a struct net_data_s that I cast in
* a (void *).
* it recv() from the client (recvfrom) a struct
* then send back the same struct type with an id incremented by 1.
*/

void *handler(void *input)
{
	int m;
	int num_player = 0;
	char **schema;
	server_data_t *server_data;
	t_client_request *request;

	server_data = malloc(sizeof(server_data_t));

	if (server_data == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return NULL;
	}

	memcpy(server_data, (server_data_t *)input, sizeof(server_data_t));


	server_data->server_bomb->player = 0;
	server_data->server_bomb->next = NULL;

	schema = malloc(13 * sizeof(char*));

	if (schema == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return NULL;
	}

	schema = handle_file("map.txt");

	for (int i = 0; i < 13; ++i) {
		memcpy(server_data->server_game->schema[i], schema[i], sizeof(char) * 15);
	}

	while (status != -1) {

		bombs_timer(server_data->server_game, server_data->server_bomb, server_data->server_explosion);
		explosions_timer(server_data->server_explosion);

		// Sending players and bombs into map
		implement_map(server_data->server_game, server_data->server_bomb, server_data->server_explosion);

		send_data_to_client(server_data, server_data->server_game);
		
		request = receive_client_data(server_data);

		if (request == NULL) {
			free(request);
			free(server_data);
			pthread_exit(NULL);
		}

		for (int i = 1; i < 5; i++) {
			m = request->magic;
			if (m == server_data->magic[i]) {
				num_player = i;
				break;
			}
		}

		player_action(server_data->server_game, server_data->server_bomb, num_player, request->command);

		free(request);
	}

	free(schema);
	free(server_data);
	return (void *)input;
}

