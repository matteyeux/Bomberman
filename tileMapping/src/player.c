#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/player.h"
#include "../include/interface.h"

player_t *init_player(void)
{
    printf("Get the player\n");

    SDL_Surface *surfacePlayer = IMG_Load("../images/player.png");
    if (!surfacePlayer) {
        printf("Error creation surface \n");
        SDL_FreeSurface(surfacePlayer);
        return (NULL);
    }

    return (NULL);
}

void destroy_player(player_t *player)
{
    if(player) 
        free(player);
    printf("Destruction du player OK \n");
}