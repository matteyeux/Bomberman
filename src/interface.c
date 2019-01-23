#include <stdio.h>
#include <stdlib.h>

#include <include/interface.h>

interface_t *init_interface(void)
{
	interface_t *interface = NULL;

	interface = malloc(sizeof(interface_t));

	if (interface == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	interface->screenSize.x = 14*60;
	interface->screenSize.y = 12*60;

	interface->Window = NULL;
	interface->Renderer = NULL;

	interface->Font = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "unable to init SDL : %s\n", SDL_GetError());
		destroy_interface(interface);
		return NULL;
	}

	// init TTF font
	if (TTF_Init() != 0) {
		fprintf(stderr, "unable to init TTF : %s\n", TTF_GetError());
		destroy_interface(interface);
		return NULL;		
	}

	// Load font
	interface->Font = TTF_OpenFont("fonts/arial.ttf", 25);

	if (!interface->Font) {
		fprintf(stderr, "unable to open TTF : %s\n", TTF_GetError());
		destroy_interface(interface);
		return NULL;	
	}

	// build window
	interface->Window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, interface->screenSize.x, interface->screenSize.y, SDL_WINDOW_SHOWN);

	if (interface->Window) {
		// create renderer
		interface->Renderer = SDL_CreateRenderer(interface->Window, -1, SDL_RENDERER_ACCELERATED);
		
		if (!interface->Renderer) {
			fprintf(stderr, "unable to create renderer : %s\n", SDL_GetError());
			destroy_interface(interface);
			return NULL;
		}
	} else {
		fprintf(stderr, "unable to create window : %s\n", SDL_GetError());
		destroy_interface(interface);
		return NULL;
	}

	return interface;
}

void destroy_interface(interface_t *interface)
{
	if (interface) {
		if (interface->Renderer) {
			SDL_DestroyRenderer(interface->Renderer);
		}

		if (interface->Window) {
			SDL_DestroyWindow(interface->Window);
		}

		if (interface->Font) {
			TTF_CloseFont(interface->Font);
		}

		TTF_Quit();

		SDL_Quit();
		free(interface);
	}
}
