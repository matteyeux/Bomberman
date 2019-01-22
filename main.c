#include "game.h"

int main(void)
{
    SDL_Event event;

    stGame *game = game_init();

    printf("lancement");
    do {
        game_draw(game);
        SDL_WaitEvent(&event);
    }while(event.type != SDL_QUIT);

    game_destroy(game);
    
    return (0);
}