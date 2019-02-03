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
	interface_t *interface = NULL;
	player_t *player = NULL;
	bomb_t *bomb = NULL;
	pid_t pid;

	if (argc != 2) {
		usage(argv[0]);
		return 3;
	}

	interface = init_interface();
	if (interface == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized interface !\n");

	player = init_player(interface);
	if (player == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized player !\n");

	bomb = init_bomb(interface);
	if (bomb == NULL) {
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "Successfully initialized bomb !\n");

	pid = fork();

	switch(pid) {
		case 0: // son, put server function here
			start_networking(argv[1]);
		case -1:
			printf("fork : %d\n", pid);
			perror("fork");
			return -1;
		default:
			game_loop(interface, player, bomb);
	}

	kill(pid ,SIGKILL);
	destroy_game(interface, player, bomb);
}