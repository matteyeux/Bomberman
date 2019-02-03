#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/bomberman.h>
#include <include/client.h>
#include <include/server.h>

#define IP "127.0.0.1"
#define PORT 12345

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


int start_networking(char *type)
{
	if (!strcmp(type, "server")) {
		server(PORT);
	} else if (!strcmp(type, "client")) {
		client(IP, PORT);
	} else {
		printf("no\n");
		return -1;
	}

	return 0;
}