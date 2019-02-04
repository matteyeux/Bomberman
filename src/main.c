#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>
#include <include/bomb.h>
#include <include/game.h>
#include <include/server.h>
#include <include/client.h>


/*
* CLI usage only.
* waiting for someone to implement GUI menu
*/
void usage(char *arg)
{
	printf("usage : %s <type>\n", arg);
	printf("type : client or server\n");
}

int main(int argc, char *argv[])
{
	game_t *game = NULL;
	pid_t pid;

	if (argc != 2) {
		usage(argv[0]);
		return -1;
	}

	game = init_game();
	pid = fork();

	switch(pid) {
		case 0:
			start_networking(argv[1]);
		case -1:
			printf("fork : %d\n", pid);
			perror("fork");
			return -1;
		default:
			game_loop(game->interface, game->player, game->bomb);
	}

	kill(pid ,SIGKILL);
	destroy_game(game->interface, game->player, game->bomb);
}