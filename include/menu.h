#include <include/interface.h>

typedef struct menu_s menu_t;

struct menu_s {
	interface_t *interface;
	SDL_Texture *TexMenu;
};

menu_t *init_menu(void);
void menu_loop();
int choice_menu(int continuer, menu_t *menu);
void destroy_menu(menu_t *menu);