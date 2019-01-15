#include "game.h"

stGame *game_init()
{
    stGame *game = NULL;
    game = malloc(sizeof(stGame));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Bug: %s\n", SDL_GetError());
        game_destroy(game);
    }

    return game;
}

void game_destroy(stGame *pGame)
{
    SDL_Quit();

    free(pGame);
}