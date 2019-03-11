#include <include/game.h>
#include <include/interface.h>


#ifndef MENU_H_
#define MENU_H_

typedef struct menu_s menu_t;

struct menu_s {
	interface_t *interface;
	SDL_Texture *TexMenu;
};

menu_t *init_menu(void);
int menu_loop(menu_t *menu);
int choice_menu(menu_t *menu);
void destroy_menu(menu_t *menu);
void clean_menu_and_setup_game(int status);
#endif
