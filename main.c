#include "game.h"

int main(void)
{
    stGame *game = game_init();

    printf("ok SDL\n");

    SDL_Delay(5000);

    game_destroy(game);
    
    return (0);
}