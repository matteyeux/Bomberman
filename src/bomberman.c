#include <stdio.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomb.h>
#include <include/game.h>
#include <include/bomberman.h>

// set to global so run_server can use it
int status;

void draw_game(interface_t *interface, player_t *player, bomb_t *bomb)
{
	// back screen
	SDL_SetRenderDrawColor(interface->Renderer, 16, 120, 48, 255);
	SDL_RenderClear(interface->Renderer);

	// display player
	if (bomb->exist == 1) {
		SDL_RenderCopy(interface->Renderer, bomb->TexBomb, NULL, &bomb->bombPositionRect);
	}
	SDL_RenderCopy(interface->Renderer, player->TexPlayer, NULL, &player->playerPositionRect);

	// show renderer
	SDL_RenderPresent(interface->Renderer);
}

int game_event(player_t *player, interface_t *interface, bomb_t *bomb, client_t *client_struct)
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
				case SDLK_DOWN:
				case SDLK_LEFT:
				case SDLK_RIGHT:
					movePlayer(player, interface, e.key.keysym.sym, client_struct);
					break;
				case SDLK_d:
					send_client_data(client_struct);
					dropBomb(player, bomb);
					break;
				default :
				break;
			}
		}
	}

	return status;
}

void destroy_game(interface_t *interface, player_t *player, bomb_t *bomb)
{
	destroy_bomb(bomb);
	destroy_player(player);
	destroy_interface(interface);
}
