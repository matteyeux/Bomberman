#include <include/interface.h>

#ifndef BOMB_H_
#define BOMB_H_

typedef struct bomb_s bomb_t;
typedef struct player_s player_t;

struct bomb_s
{
	// Does the bomb exist
	int exist;
	int posX, posY;

	// bomb textures
	SDL_Texture *TexBomb;

	// position of bomb
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
};

bomb_t *init_bomb(SDL_Renderer *renderer);
void placeBomb(bomb_t *bomb, player_t *player);
void destroy_bomb(bomb_t *bomb);
SDL_Texture *set_texture_bomb(SDL_Renderer *renderer);

#endif // BOMB_H_
