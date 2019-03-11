#include <stdio.h>
#include <pthread.h>

#include <SDL2/SDL_image.h>

#include <include/interface.h>
#include <include/menu.h>
#include <include/game.h>

menu_t *init_menu(void)
{
	menu_t *menu = NULL;

	menu = malloc(sizeof(menu_t));

	if (menu == NULL) {
		fprintf(stderr, "[MALLOC] unable to allocate memory\n");
		return NULL;
	}

	menu->interface = init_interface();
	if (menu->interface == NULL) {
		return NULL;
	}

	fprintf(stdout, "Successfully initialized menu interface !\n");

	// load menu texture
	SDL_Surface *menuSurface = IMG_Load("images/menu.jpg");

	if (!menuSurface) {
		fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
		destroy_menu(menu);
		return NULL;
	} else {
		menu->TexMenu = SDL_CreateTextureFromSurface(menu->interface->Renderer, menuSurface);

		if (!menu->TexMenu) {
			fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
			destroy_menu(menu);
			return NULL;
		}

		SDL_FreeSurface(menuSurface);
	}

	return menu;
}

int menu_loop(menu_t *menu)
{
	int choice = -1;

	while (choice == -1) {
		choice = choice_menu(menu);
	}

	if (menu) {
		destroy_menu(menu);
	}

	return choice;
}

/*
* This  function is used to call destroy_menu
* and start threads for SDL and server
*/
void clean_menu_and_setup_game(int status)
{
	pthread_t thread_sdl, thread_net;
	game_t *game = NULL;
	char *arg = NULL;

	switch (status) {
		case 1:
			break;
		case 2:
			arg = "server";
			break;
		case 3:
			arg = "client";
			break;
		default:
			break;
	}

	game = init_game();

	if (game == NULL) {
		fprintf(stderr, "failed to to init game\n");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&thread_sdl, NULL, game_loop, (void*) game) < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	/* if arg is not NULL, it means we have to start client or server */
	if (arg) {
		if (pthread_create(&thread_net, NULL, start_networking, (void*) arg) < 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}

	/* join SDL thead */
	if (pthread_join(thread_sdl, NULL) != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
}
/*
* function to set choice of user
*/
int choice_menu(menu_t *menu)
{
	SDL_Event event;
	int choice = -1;
	SDL_WaitEvent(&event);

	switch(event.type)
	{
		case SDL_QUIT:
			choice = 0;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					choice = 0;
					break;
				case SDLK_1:
				case SDLK_s:
					choice = 1;
					break;
				case SDLK_2:
				case SDLK_c:
					choice = 2;
					break;
				case SDLK_3:
				case SDLK_r:
					choice = 3;
					break;
			}
		break;
	}

	// display & show menu
	if (menu->interface->Renderer != NULL && menu->TexMenu != NULL) {
		SDL_RenderCopy(menu->interface->Renderer, menu->TexMenu, NULL, NULL);
		SDL_RenderPresent(menu->interface->Renderer);
	}

	return choice;
}

void destroy_menu(menu_t *menu)
{
	if (menu) {
		if (menu->interface) {
			destroy_interface(menu->interface);
		}

		if (menu->TexMenu) {
			SDL_DestroyTexture(menu->TexMenu);
		}

		free(menu);
	}
}