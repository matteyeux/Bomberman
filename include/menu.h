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
void menu_loop(game_t *game);
int choice_menu(int continuer, menu_t *menu, void *game_struct);
void destroy_menu(menu_t *menu);

#endif
