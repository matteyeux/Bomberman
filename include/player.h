#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <include/interface.h>

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct player_s player_t;

struct player_s
{	
	int id;
	int score;

	// player texture
	SDL_Texture *TexPlayer;
	
	// position of player
	SDL_Rect playerPositionRect;
};

player_t *init_player(interface_t *interface);
void destroy_player(player_t *player);

#endif /* PLAYER_H_ */