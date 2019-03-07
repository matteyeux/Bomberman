#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>


#ifndef GAME_H_
#define GAME_H_

typedef struct game_s game_t;

struct game_s {
	interface_t *interface;
	player_t *player;
	bomb_t *bomb;
};

game_t *init_game(void);
void *game_loop(void *game_struct);
void *start_networking(void *type);

#endif
