#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>

typedef struct game_s game_t;

struct game_s {
	interface_t *interface;
	player_t *player;
	bomb_t *bomb;
};

game_t *init_game(void);
void game_loop(interface_t *interface, player_t *player, bomb_t *bomb);
int start_networking(char *type);