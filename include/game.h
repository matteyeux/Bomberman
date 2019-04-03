#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/map.h>
#include <include/menu.h>

#ifndef GAME_H_
#define GAME_H_

typedef struct global_game_s global_game_t;

struct global_game_s {
	interface_t *interface;
	player_t *player;
	bomb_t *bomb;
	map_t *map;
	char *ip;
	u_short port;
};

global_game_t *init_game(void);
void *game_loop(void *game_struct);
void setup_game(menu_return_t *menu);

#endif
