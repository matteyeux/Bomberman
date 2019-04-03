#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <include/interface.h>
#include <include/menu.h>
#include <include/game.h>

#define MAX_IP_LENGTH 16
#define MAX_PORT_LENGTH 8

menu_return_t *menu(void)
{
	Images images;
	Buttons buttons;
	gameState game_state = MENU;

	menu_return_t *menu_ret;

	int quit_bomberman = 0;
	int IPTextLength = 0;
	int PortTextLength = 0;
	char *IPTextInput = (char*) malloc(16);
	char *PortTextInput = (char*) malloc(8);
	int isIPTextInput = FALSE;
	int isPortTextInput = FALSE;

	SDL_Surface *IPSurfaceText = NULL, *PortSurfaceText = NULL;
	SDL_Texture *IPText = NULL, *PortText = NULL;

	// define rect text input
	SDL_Rect IPTextRect, PortTextRect;
	IPTextRect.x = 68;
	PortTextRect.x = 471;
	IPTextRect.y = PortTextRect.y = 150;
	IPTextRect.w = PortTextRect.w = 336;
	IPTextRect.h = PortTextRect.h = 90;

	// define color
	SDL_Color white = {255, 255, 255, 99};

	init_buttons(&buttons);

	// START TODO à raccrocher à interface.c
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	// Build window
	SDL_Window *window = SDL_CreateWindow("Bomberman",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 780, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("Error : %s\n", SDL_GetError());
		return NULL;
	}

	// Create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Error : %s\n", SDL_GetError());
		return NULL;
	}

	TTF_Font *arial = TTF_OpenFont("fonts/arial.ttf", 45);
	if (arial == NULL){
		printf("Error : %s\n", SDL_GetError());
		return NULL;
	}
	// END TODO à raccrocher à interface.c

	// active transparency
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	load_images(&images, renderer);

	menu_ret = malloc(sizeof(menu_return_t));

	if (menu_ret == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	menu_ret->ip = "127.0.0.1";
	menu_ret->port = 12345;
	menu_ret->ret = -1;

	while (game_state != EXIT) {
		switch (game_state) {
			case MENU:
				if (display_image(renderer, images.mainMenuTex) == EXIT_FAILURE)
					return NULL;
			break;
			case JOIN:
				if (display_image(renderer, images.joinPartyMenuTex) == EXIT_FAILURE)
					return NULL;
				SDL_RenderCopy(renderer, IPText, NULL, &IPTextRect);
				SDL_RenderCopy(renderer, PortText, NULL, &PortTextRect);
			break;
			default:
			break;
		}

		SDL_Event event;
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_BACKSPACE) {
					if (game_state == JOIN) {
						// IP
						if (isIPTextInput && IPTextLength > 0) {
							IPTextLength--;
							IPTextInput[strlen(IPTextInput)-1] = 0;
							IPSurfaceText = TTF_RenderText_Blended(arial, IPTextInput, white);
							IPText = SDL_CreateTextureFromSurface(renderer, IPSurfaceText);
						} // Port
						else if (isPortTextInput && PortTextLength > 0) {
							PortTextLength--;
							PortTextInput[strlen(PortTextInput)-1] = 0;
							PortSurfaceText = TTF_RenderText_Blended(arial, PortTextInput, white);
							PortText = SDL_CreateTextureFromSurface(renderer, PortSurfaceText);
						}
					}
				}
			break;
			case SDL_TEXTINPUT:
				if (game_state == JOIN) {
					// IP
					if (isIPTextInput && IPTextLength < MAX_IP_LENGTH) {
						IPTextLength++;
						strcat(IPTextInput, event.text.text);
						IPSurfaceText = TTF_RenderText_Blended(arial, IPTextInput, white);
						IPText = SDL_CreateTextureFromSurface(renderer, IPSurfaceText);
					} // Port
					else if (isPortTextInput && PortTextLength < MAX_PORT_LENGTH) {
						PortTextLength++;
						strcat(PortTextInput, event.text.text);
						PortSurfaceText = TTF_RenderText_Blended(arial, PortTextInput, white);
						PortText = SDL_CreateTextureFromSurface(renderer, PortSurfaceText);
					}
				}
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (game_state == JOIN) {
					int x = event.button.x, y=event.button.y;
					// Click on the "IP" or "Port" text input
					if (x >= IPTextRect.x && x <= IPTextRect.x+IPTextRect.w &&
						y >= IPTextRect.y && y <= IPTextRect.y+IPTextRect.h)
					{
						SDL_StartTextInput();
						isIPTextInput = TRUE;
						isPortTextInput = FALSE;
					} else if (x >= PortTextRect.x && x <= PortTextRect.x+PortTextRect.w &&
						y >= PortTextRect.y && y <= PortTextRect.y+PortTextRect.h)
					{
						SDL_StartTextInput();
						isIPTextInput = FALSE;
						isPortTextInput = TRUE;
					} else {
						isIPTextInput = FALSE;
						isPortTextInput = FALSE;
						SDL_StopTextInput();
					}
					// Click on the "Validate" button
					if (x >= buttons.validateBtn.min_x && x <= buttons.validateBtn.max_x &&
						y >= buttons.validateBtn.min_y && y <= buttons.validateBtn.max_y)
					{

						// inject data in the struct
						// we return at the end of the function
						menu_ret->ip = IPTextInput;
						menu_ret->port = atoi(PortTextInput);
						menu_ret->ret = 2;
						// sortir du menu
						game_state = EXIT;
					}

					// Click on the "Return" button
					if (x >= buttons.returnBtn.min_x && x <= buttons.returnBtn.max_x &&
						y >= buttons.returnBtn.min_y && y <= buttons.returnBtn.max_y)
					{
						game_state = MENU;
						printf("CLICK ON THE RETURN BUTTON\n");
					}
				} else if (game_state == MENU) {
					int button = mouse_bouton(event.button.x, event.button.y, buttons);
					if (button == 0) {
						game_state = JOIN;
					} else if (button == 1) {
						menu_ret->ret = 1;
						game_state = EXIT;
					} else if (button == 2) {
						game_state = EXIT;
						quit_bomberman = 1;
					}
				}
				break;
			case SDL_QUIT:
				game_state = EXIT;
				break;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		if (isIPTextInput)
			SDL_RenderFillRect(renderer, &IPTextRect);
		if (isPortTextInput)
			SDL_RenderFillRect(renderer, &PortTextRect);

		SDL_RenderPresent(renderer);
	}

	free_images(&images);
	SDL_FreeSurface(IPSurfaceText);
	SDL_FreeSurface(PortSurfaceText);
	SDL_DestroyTexture(IPText);
	SDL_DestroyTexture(PortText);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(arial);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	if (quit_bomberman == 1) {
		exit(0);
	}

	return menu_ret;
}

void init_buttons(Buttons *buttons)
{
	int width = 365;
	int height = 90;

	// coordinate min_x
	buttons->createPartyBtn.min_x
		= buttons->joinPartyBtn.min_x
		= buttons->exitBtn.min_x
		= buttons->validateBtn.min_x
		= buttons->returnBtn.min_x
		= 255;

	// coordinate max_x
	buttons->createPartyBtn.max_x
		= buttons->joinPartyBtn.max_x
		= buttons->exitBtn.max_x
		= buttons->validateBtn.max_x
		= buttons->returnBtn.max_x
		= 255 + width;

	// coordinate y
	buttons->createPartyBtn.min_y = 148;
	buttons->createPartyBtn.max_y = 148 + height;
	buttons->joinPartyBtn.min_y = buttons->validateBtn.min_y = 269;
	buttons->joinPartyBtn.max_y = buttons->validateBtn.max_y = 269 + height;
	buttons->exitBtn.min_y = buttons->returnBtn.min_y = 385;
	buttons->exitBtn.max_y = buttons->returnBtn.max_y = 385 + height;
}

void load_images(Images *images, SDL_Renderer *renderer)
{
	SDL_Surface *surface = IMG_Load("images/Bomberman_main_menu.jpg");
	images->mainMenuTex = SDL_CreateTextureFromSurface(renderer, surface);

	surface = IMG_Load("images/Bomberman_join_game.jpg");
	images->joinPartyMenuTex = SDL_CreateTextureFromSurface(renderer, surface);
}

int display_image(SDL_Renderer *renderer, SDL_Texture *texture)
{
	SDL_Rect dest = {0, 0, 900, 780};

	if (texture == NULL || SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
		printf("Error : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int mouse_bouton(int x, int y, Buttons buttons)
{
	int button = -1;
	if (x >= buttons.createPartyBtn.min_x && x <= buttons.createPartyBtn.max_x) {
		// Click on the "Join Party" button
		if (y >= buttons.joinPartyBtn.min_y && y <= buttons.joinPartyBtn.max_y)
			button = 0;
		// Click on the "Create Party" button
		else if (y >= buttons.createPartyBtn.min_y && y <= buttons.createPartyBtn.max_y)
			button = 1;
		// Click on the "Zxit" button
		else if (y >= buttons.exitBtn.min_y && y <= buttons.exitBtn.max_y)
			button = 2;
	}

	return button;
}

void free_images(Images *images)
{
	SDL_DestroyTexture(images->mainMenuTex);
	SDL_DestroyTexture(images->joinPartyMenuTex);
}