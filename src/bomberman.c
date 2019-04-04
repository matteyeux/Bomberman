#include <stdio.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/game.h>
#include <include/bomberman.h>

// set to global so run_server can use it
int status;

void draw_game(global_game_t *game, t_server_game *sg)
{
	interface_t *interface 	= game->interface;
	map_t 		*map 		= game->map;
	bomb_t 		*bomb 		= game->bomb;
	player_t 	*player 	= game->player;
	explosion_t *explosion 	= game->explosion;
	int index;

	// back screen
	SDL_SetRenderDrawColor(interface->Renderer, 128, 20, 0, 255);
	SDL_RenderClear(interface->Renderer);

	setRectangle(&sg->player1.src, 4*16, 0*16, 16, 16);
	setRectangle(&sg->player2.src, 4*16, 1*16, 16, 16);
	setRectangle(&sg->player3.src, 1*16, 0*16, 16, 16);
	setRectangle(&sg->player4.src, 1*16, 1*16, 16, 16);

	if (sg != NULL) {
		for (int i = 0; i < map->nbTileY; i++) {
			for (int j = 0; j < map->nbTileX; j++) {

				setRectangle(interface->destRect, map->largeur_tile*i, map->hauteur_tile*j, map->largeur_tile, map->hauteur_tile);
		
				setRectangle(&sg->player1.dest,  map->largeur_tile * sg->player1.x_pos, map->hauteur_tile * sg->player1.y_pos, map->largeur_tile, map->hauteur_tile);
				setRectangle(&sg->player2.dest,  map->largeur_tile * sg->player2.x_pos, map->hauteur_tile * sg->player2.y_pos, map->largeur_tile, map->hauteur_tile);
				setRectangle(&sg->player3.dest,  map->largeur_tile * sg->player3.x_pos, map->hauteur_tile * sg->player3.y_pos, map->largeur_tile, map->hauteur_tile);
				setRectangle(&sg->player4.dest,  map->largeur_tile * sg->player4.x_pos, map->hauteur_tile * sg->player4.y_pos, map->largeur_tile, map->hauteur_tile);

				// index is the ASCII code of the character
				index = sg->schema[j][i]-48;

				switch (index) {
					case 0:
					case 1:
					case 2:
					case 3:
						SDL_RenderCopy(interface->Renderer, map->mapTexture, map->tabTiles[index]->tile, interface->destRect);
						break;
					case 6:
						SDL_RenderCopy(interface->Renderer, player->playerTexture, &sg->player1.src, &sg->player1.dest);
						break;
					case 7:
						SDL_RenderCopy(interface->Renderer, player->playerTexture, &sg->player2.src, &sg->player2.dest);
						break;
					case 8:
						SDL_RenderCopy(interface->Renderer, player->playerTexture, &sg->player3.src, &sg->player3.dest);
						break;
					case 9:
						SDL_RenderCopy(interface->Renderer, player->playerTexture, &sg->player4.src, &sg->player4.dest);
						break;
					case 17:
						setRectangle(&bomb->srcRect, 8*16, 6*16, 16, 16);
						setRectangle(&bomb->destRect, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, bomb->TexBomb, &bomb->srcRect, &bomb->destRect);
						break;
					case 18:
						setRectangle(&bomb->srcRect, 7*16, 6*16, 16, 16);
						setRectangle(&bomb->destRect, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, bomb->TexBomb, &bomb->srcRect, &bomb->destRect);
						break;
					case 19:
						setRectangle(&bomb->srcRect, 6*16, 6*16, 16, 16);
						setRectangle(&bomb->destRect, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, bomb->TexBomb, &bomb->srcRect, &bomb->destRect);
						break;
					case 23:
						setRectangle(&explosion->srcRect, 5*16, 3*16, 16, 16);
						setRectangle(&explosion->destRect, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, explosion->explTexture, &explosion->srcRect, &explosion->destRect);
						break;
					case 24:
						setRectangle(&explosion->srcRect, 5*16, 4*16, 16, 16);
						setRectangle(&explosion->destRect, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, explosion->explTexture, &explosion->srcRect, &explosion->destRect);
						break;
					case 25:
						setRectangle(&explosion->srcRect, 0*16, 5*16, 16, 16);
						setRectangle(&explosion->destRect, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, explosion->explTexture, &explosion->srcRect, &explosion->destRect);
						break;
					case 83-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 84-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 85-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 86-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 87-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 88-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 89-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
					case 90-48:
						setRectangle(player->srcRectPlayer, 0*16, 5*16, 16, 16);
						setRectangle(player->destRectPlayer, i * map->largeur_tile, j * map->hauteur_tile, map->largeur_tile, map->hauteur_tile);
						SDL_RenderCopy(interface->Renderer, player->playerTexture, player->srcRectPlayer, player->destRectPlayer);
						break;
				}
			}
		}
	}

	// show renderer
	SDL_RenderPresent(interface->Renderer);
}

int game_event(global_game_t *game, client_t *client_struct)
{
	SDL_Event e;
	status = 0;

	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			status = -1;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					status = -1;
					break;
				case SDLK_UP:
					game->player->command = 'U';
					send_client_data(client_struct, game->player);
					break;
				case SDLK_DOWN:
					game->player->command = 'D';
					send_client_data(client_struct, game->player);
					break;
				case SDLK_LEFT:
					game->player->command = 'L';
					send_client_data(client_struct, game->player);
					break;
				case SDLK_RIGHT:
					game->player->command = 'R';
					send_client_data(client_struct, game->player);
					break;
				case SDLK_SPACE:
					game->player->command = 'B';
					send_client_data(client_struct, game->player);
					break;
				default :
				break;
			}

			for (int y = 0; y < 13; y++) {
				for (int x = 0; x < 15; x++) {
					printf("%c", game->map->schema[y][x]);
				}

				printf("\t");

				for (int z = 0; z < 15; z ++) {
					printf("%c", global_game->schema[y][z]);
				}
				printf("\n");
			}
			printf("\n");

		}
	}

	return status;
}

void destroy_game(global_game_t *game)
{
	destroy_bomb(game->bomb);
	destroy_player(game->player);
	destroy_map(game->map);
	destroy_interface(game->interface);
	free(game);
}
