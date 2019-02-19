#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef INTERFACE_H_
#define INTERFACE_H_

typedef struct interface_s interface_t;

struct interface_s
{
	// SDL variables
	SDL_Point screenSize;
	SDL_Window *Window;
	SDL_Renderer *Renderer;

	// TTF font
	TTF_Font *Font;
};

interface_t *init_interface(void);
void destroy_interface(interface_t *interface);

#endif