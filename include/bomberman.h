#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/game.h>

extern int status;

void draw_game(global_game_t *game, t_server_game *sg);
int game_event(global_game_t *game, client_t *client_struct);
void destroy_game(global_game_t *game);
