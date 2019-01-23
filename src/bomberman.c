#include <stdio.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>

void draw_game(interface_t *interface, player_t *player)
{
	// back screen
	SDL_SetRenderDrawColor(interface->Renderer, 0, 0, 0, 255);
	SDL_RenderClear(interface->Renderer);

	//player->playerImg.x = 16;
	//player->playerImg.y = 0;
	//player->playerImg.w = 16;
	//player->playerImg.h = 16;
	

	// display player
	SDL_RenderCopy(interface->Renderer, player->TexPlayer, &player->playerImg,&player->playerPositionRect);

	// show renderer
	SDL_RenderPresent(interface->Renderer);
}

int game_event(player_t *player)
{
	int status = 0;

	SDL_Event e;

	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			status = -1;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					status = -1;
					break;
				case SDLK_UP:
					player->playerImg.x = 4*16;
					player->playerImg.y = 1*16;
					player->playerPositionRect.y -= 60;
					break;
				case SDLK_DOWN:
					player->playerImg.x = 4*16;
					player->playerImg.y = 0*16;
					player->playerPositionRect.y += 60;
					break;
				case SDLK_LEFT:
					player->playerImg.x = 1*16;
					player->playerImg.y = 0*16;
					player->playerPositionRect.x -= 60;
					break;
				case SDLK_RIGHT:
					player->playerImg.x = 1*16;
					player->playerImg.y = 1*16;
					player->playerPositionRect.x += 60;
					break;
				default :
					fprintf(stderr, "unknown key : %d\n", e.key.keysym.sym);
					break;
			}
		}
	}

	return status;
}

void destroy_game(interface_t *interface, player_t *player)
{
	destroy_player(player);
	destroy_interface(interface);
}
