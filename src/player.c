#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/player.h>
#include <include/interface.h>
#include <include/bomberman.h>

player_t *init_player(interface_t *interface)
{
	player_t *player = NULL;

	player = malloc(sizeof(player_t));

	if (player == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	player->id = 0;
	player->score = 0;
	player->playerPositionRect.x = interface->screenSize.x / 2;
	player->playerPositionRect.y = interface->screenSize.y / 2;
	player->playerPositionRect.w = 60;
	player->playerPositionRect.h = 60;
	player->playerImg.x = 16;
	player->playerImg.y = 16;
	player->playerImg.w = 16;
	player->playerImg.h = 16;

	// load player texture
	//SDL_Surface *playerSurface = IMG_Load("images/bomberman_front.png");
	SDL_Surface *playerSurface = IMG_Load("images/bomberman.bmp");

	if (!playerSurface) {
		fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
		destroy_game(interface, player);
		return NULL;	
	} else {
		player->TexPlayer = SDL_CreateTextureFromSurface(interface->Renderer, playerSurface);

		if (!player->TexPlayer) {
			fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
			destroy_game(interface, player);
			return NULL;
		}

		SDL_FreeSurface(playerSurface);
	}

	return player;
}

void destroy_player(player_t *player)
{
	if (player) {
		if (player->TexPlayer) {
			SDL_DestroyTexture(player->TexPlayer);
		}

		free(player);
	}
}
