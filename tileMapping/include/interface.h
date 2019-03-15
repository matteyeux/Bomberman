#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"

#ifndef INTERFACE_H_
#define INTERFACE_H_

typedef struct interface_s {

    SDL_Point       screenSize;
    SDL_Window      *pWindow;
    SDL_Renderer    *pRenderer;
    SDL_Rect        *destRect;

    map_t           *map;

} interface_t;

interface_t *init_interface(map_t *map);
void destroy_interface(interface_t *pInterface);
void draw_interface(interface_t *interface);


#endif