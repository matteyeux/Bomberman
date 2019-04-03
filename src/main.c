#include <time.h>
#include <include/menu.h>
#include <include/game.h>


int main(void)
{
	srandom(time(0));

	menu_return_t *menu_ret;

	menu_ret = menu();

	setup_game(menu_ret);

	free(menu_ret);

	return 0;
}