#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>
#include <include/bomb.h>
#include <include/game.h>
#include <include/server.h>
#include <include/client.h>
#include <include/menu.h>

/*
* CLI usage only.
* waiting for someone to implement GUI menu
*/
void usage(char *arg)
{
	printf("usage : %s <type>\n", arg);
	printf("type : client or server\n");
}

int main(void)
{
	menu_t *menu = NULL;
	int choice = 0;

	menu = init_menu();
	choice = menu_loop(menu);

	if (choice != 0) {
		clean_menu_and_setup_game(choice);
	}
	return 0;
}
