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
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	// TODO : changer la generation ID, doit être faite par le serveur
	player->magic = 0;
	player->score = 0;
	player->speed = 10;
	player->dir = 3;
	player->command = 0;

	player->posX = 2;
    player->posY = 2;

    player->playerTexture = NULL;
    player->srcRectPlayer = malloc(sizeof(SDL_Rect));
    if (player->srcRectPlayer == NULL) {
        fprintf(stderr, "Probleme malloc SRC rect player\n");
        destroy_player(player);
        return NULL;
    }
    player->destRectPlayer = malloc(sizeof(SDL_Rect));
    if (player->destRectPlayer == NULL) {
        fprintf(stderr, "Probleme malloc DEST rect player\n");
        destroy_player(player);
        return NULL;
    }
	// player->playerPositionRect.x = interface->screenSize.x / 2;
	// player->playerPositionRect.y = interface->screenSize.y / 2;
	// player->playerPositionRect.w = 50;
	// player->playerPositionRect.h = 60;

	// // load player texture
	// SDL_Surface *playerSurface = IMG_Load("images/bomberman_front.png");

	// if (!playerSurface) {
	// 	fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
	// 	destroy_game(interface, player, NULL);
	// 	return NULL;
	// } else {
	// 	player->TexPlayer = SDL_CreateTextureFromSurface(interface->Renderer, playerSurface);

	// 	if (!player->TexPlayer) {
	// 		fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
	// 		destroy_game(interface, player, NULL);
	// 		return NULL;
	// 	}

	// 	SDL_FreeSurface(playerSurface);
	// }

	return player;
}

// void movePlayer(player_t *player, interface_t *interface, SDL_Keycode direction, client_t *client_struct)
// {
// 	t_server_game *game = NULL;

// 	if (direction == SDLK_UP) {
// 		player->dir = 0;

// 		if (client_struct != NULL) {
// 			// TODO Yop printf("sending data\n");
// 			send_client_data(client_struct, player);
// 			// TODO Yop printf("waiting for data\n");
// 			//game = receive_server_data(client_struct);
// 			// TODO Matt printf("%d\n", game->player_infos->x_pos); // prints 12
// 		}

// 		if (player->playerPositionRect.y > 0) {
// 			player->playerPositionRect.y -= player->speed;
// 		}
// 	} else if (direction == SDLK_DOWN) {
// 		player->dir = 2;
// 		send_client_data(client_struct, player);
// 		if (player->playerPositionRect.y < (interface->screenSize.y - player->playerPositionRect.h)) {
// 			player->playerPositionRect.y += player->speed;
// 		}
// 	} else if (direction == SDLK_LEFT) {
// 		player->dir = 3;
// 		send_client_data(client_struct, player);
// 		if (player->playerPositionRect.x > 0) {
// 			player->playerPositionRect.x -= player->speed;
// 		}
// 	} else if (direction == SDLK_RIGHT) {
// 		player->dir = 1;
// 		send_client_data(client_struct, player);
// 		if (player->playerPositionRect.x < (interface->screenSize.x - player->playerPositionRect.w)) {
// 			player->playerPositionRect.x += player->speed;
// 		}
// 	} else {
// 		fprintf(stderr, "unknown direction\n");
// 	}

// 	if (game)
// 		free(game);
// }

bomb_t *dropBomb(player_t *player, bomb_t *bomb)
{
	if (bomb->exist == 0) {
		placeBomb(bomb, player);
	}

	return bomb;
}

void destroy_player(player_t *player)
{
    if(player) {
        if (player->playerTexture)
            SDL_DestroyTexture(player->playerTexture);

        if (player->srcRectPlayer)
            free(player->srcRectPlayer);

        if (player->destRectPlayer)
            free(player->destRectPlayer);

        free(player);
    }
    printf("Destruction du player OK \n");
}

SDL_Texture *set_texture_player(SDL_Renderer *pRenderer)
{
    SDL_Surface *surfacePlayer = IMG_Load("images/player.png");
    SDL_Texture *texture = NULL;
    if (!surfacePlayer) {
        printf("Error creation surface \n");
        return (NULL);
    } else {

        texture = SDL_CreateTextureFromSurface(pRenderer, surfacePlayer);
        if (texture == NULL) {
            fprintf(stderr, "Probleme creation texture player\n");
            SDL_FreeSurface(surfacePlayer);
            return NULL;
        }
        
        SDL_FreeSurface(surfacePlayer);
    }

    return texture;

}