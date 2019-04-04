#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/player.h>
#include <include/interface.h>
#include <include/bomberman.h>
#include <include/bomb.h>
#include <include/client.h>
#include <include/server.h>

#define IP "127.0.0.1"
#define PORT 12345

player_t *init_player(void)
{
	player_t *player = NULL;

	player = malloc(sizeof(player_t));

	if (player == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		return NULL;
	}

	player->magic = 0;
	player->score = 0;
	player->speed = 10;
	player->dir = 3;
	player->command = 0;

	player->posX = 0;
	player->posY = 0;

	player->playerTexture = NULL;
	player->srcRectPlayer = malloc(sizeof(SDL_Rect));
	if (player->srcRectPlayer == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		destroy_player(player);
		return NULL;
	}
	player->destRectPlayer = malloc(sizeof(SDL_Rect));
	if (player->destRectPlayer == NULL) {
		fprintf(stderr, "[%s:%d] unable to allocate memory\n", __FILE__, __LINE__);
		destroy_player(player);
		return NULL;
	}

	return player;
}

void destroy_player(player_t *player)
{
	if (player) {
		if (player->playerTexture)
			SDL_DestroyTexture(player->playerTexture);

		if (player->srcRectPlayer)
			free(player->srcRectPlayer);

		if (player->destRectPlayer)
			free(player->destRectPlayer);

		free(player);
	}
}

SDL_Texture *set_texture_player(SDL_Renderer *pRenderer)
{
	SDL_Surface *surfacePlayer = IMG_Load("images/player.png");
	SDL_Texture *texture = NULL;
	if (!surfacePlayer) {
		printf("[ERROR] unable to create surface \n");
		return (NULL);
	} else {

		texture = SDL_CreateTextureFromSurface(pRenderer, surfacePlayer);
		if (texture == NULL) {
			fprintf(stderr, "[ERROR] unable to create texture for player\n");
			SDL_FreeSurface(surfacePlayer);
			return NULL;
		}

		SDL_FreeSurface(surfacePlayer);
	}

	return texture;

}