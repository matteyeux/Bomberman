#include "game.h"

int main(void)
{
    stGame *game = game_init();

    printf("ok SDL\n");

    game_destroy(game);
    
    return (0);
}