#include <time.h>

#include <include/menu.h>

int main(void)
{
	menu_t *menu = NULL;
	int choice = 0;

	srandom(time(0));

	menu = init_menu();
	choice = menu_loop(menu);

	if (choice != 0) {
		clean_menu_and_setup_game(choice);
	}

	return 0;
}
