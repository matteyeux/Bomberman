
#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

typedef struct {
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    SDL_Texture *pTexPlayer;
} stGame;

stGame *game_init(void);
void game_destroy(stGame *pGame);


#endif