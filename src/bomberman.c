#include <stdio.h>

#include <include/interface.h>
#include <include/player.h>
#include <include/bomberman.h>

void draw_game(interface_t *interface, player_t *player)
{
	// back screen
	SDL_SetRenderDrawColor(interface->Renderer, 16, 120, 48, 255);
	SDL_RenderClear(interface->Renderer);


	// display player
	SDL_RenderCopy(interface->Renderer, player->TexPlayer, NULL, &player->playerPositionRect);

	// show renderer
	SDL_RenderPresent(interface->Renderer);
}

int game_event(player_t *player, interface_t *interface)
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
				case SDLK_DOWN:
				case SDLK_LEFT:
				case SDLK_RIGHT:
					movePlayer(player, interface, e.key.keysym.sym);
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

void destroy_game_by_wallHard(interface_t *interface, wallHard_t *wallHard)
{

}