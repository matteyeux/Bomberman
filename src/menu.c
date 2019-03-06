#include <stdio.h>
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

	fprintf(stdout, "Successfully initialized interface !\n");

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

void menu_loop()
{
	menu_t *menu = init_menu();

	int continuer = 1; 

	while (continuer) {
		choice_menu(continuer, menu);
	}

	destroy_menu(menu);
}

int choice_menu(int continuer, menu_t *menu)
{
	SDL_Event event;
	SDL_WaitEvent(&event);

	switch(event.type)
	{
		case SDL_QUIT:
		    continuer = 0;
		    break;
		case SDL_KEYDOWN:
		    switch(event.key.keysym.sym)
		    {
		        case SDLK_ESCAPE:
		            continuer = 0;
		            break;
		        case SDLK_1:
		        case SDLK_s:
		            printf("Jeux Solo\n");
		            // game_loop(game->interface, game->player, game->bomb);
		            break;
		        case SDLK_2:
		        case SDLK_c:
		            printf("Créer une partie Multi\n");
		            // game_loop(game->interface, game->player, game->bomb);
		            break;
		        case SDLK_3:
		        case SDLK_r:
		            printf("Rejoindre une partie Multi\n");
		            // game_loop(game->interface, game->player, game->bomb);
		            break;   
		        case SDLK_4:
		        case SDLK_e:
		            printf("Editeur de map\n");
		            // game_loop(game->interface, game->player, game->bomb);
		            break;                               
		    }
		break;
	}

	// display & show menu
	SDL_RenderCopy(menu->interface->Renderer, menu->TexMenu, NULL, NULL);
	SDL_RenderPresent(menu->interface->Renderer);

	return continuer;
}

void destroy_menu(menu_t *menu)
{
	destroy_interface(menu->interface);
	if (menu) {
		if (menu->TexMenu) {
			SDL_DestroyTexture(menu->TexMenu);
		}

		free(menu);
	}    
}