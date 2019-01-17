#include <stdio.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>

void bomberman_print(void)
{
	printf("Bomberman\n");
}

void destroy_game(interface_t *interface, player_t *player)
{
	destroy_player(player);
	destroy_interface(interface);
}