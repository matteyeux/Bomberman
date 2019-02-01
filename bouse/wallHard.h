#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <include/interface.h>


#ifndef BOMBERMAN_wallHard_H
#define BOMBERMAN_wallHard_H

typedef struct wallHard_s wallHard_t;

struct wallHard_s
{
    // wallHard texture
    SDL_Texture *TexwallHard;

    // position of wallHard
    SDL_Rect wallHardPositionRect;
};

wallHard_t *init_wallHard(interface_t *interface);
void moveWallHard(wallHard_t *wallHard, interface_t *interface, SDL_Keycode direction);
void destroy_wallHard(wallHard_t *wallHard);


#endif //BOMBERMAN_wallHard_H
