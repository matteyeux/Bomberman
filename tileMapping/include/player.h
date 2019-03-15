#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct player_s {

    SDL_Texture *playerTexture;
    SDL_Rect    *rectPlayer;

} player_t;

player_t *init_player(void);
void destroy_player(player_t *player);

#endif