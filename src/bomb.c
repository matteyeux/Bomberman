#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/bomb.h>
#include <include/interface.h>
#include <include/bomberman.h>

bomb_t *init_bomb(SDL_Renderer *renderer)
{
	bomb_t *bomb = NULL;

	bomb = malloc(sizeof(bomb_t));

	if (bomb == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	bomb->exist = 0;
	setRectangle(&bomb->srcRect, 8*16, 6*16, 16, 16);

	// load bomb texture
	bomb->TexBomb = set_texture_bomb(renderer);
	if (bomb->TexBomb == NULL) {
		fprintf(stderr, "Error texture bomb\n");
		destroy_bomb(bomb);
		return NULL;
	}

	return bomb;
}

void placeBomb(bomb_t *bomb, player_t *player)
{
	bomb->exist= 1;
	setRectangle(&bomb->destRect, player->destRectPlayer->x + 5, player->destRectPlayer->y + 20, 40, 55);
	// bomb->destRect.x = player->destRectPlayer->x + 5;
	// bomb->destRect.y = player->destRectPlayer->y + 20;
	// bomb->destRect.h = 60;
	// bomb->destRect.w = 60;
}

void destroy_bomb(bomb_t *bomb)
{
	if (bomb) {
		if (bomb->TexBomb)
			SDL_DestroyTexture(bomb->TexBomb);

		free(bomb);
	}
}

SDL_Texture *set_texture_bomb(SDL_Renderer *renderer)
{
	SDL_Surface *bombSurface = IMG_Load("images/tiles_bomberman.png");
	SDL_Texture *texture;

	if (!bombSurface) {
		fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
		return NULL;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, bombSurface);

		if (!texture) {
			fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
			SDL_FreeSurface(bombSurface);
			return NULL;
		}

		SDL_FreeSurface(bombSurface);
	}
	return texture;
}