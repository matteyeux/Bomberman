
#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
} stGame;

stGame *game_init(void);
void game_destroy(stGame *pGame);

#endif