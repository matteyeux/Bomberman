#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/player.h>
#include <include/interface.h>
#include <include/bomberman.h>

wallHard_t *init_wallHard(interface_t *interface)
{

    wallHard_t *wallHard = NULL;

    wallHard = malloc(sizeof(wallHard_t));

    if (wallHard == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    wallHard->wallHardPositionRect.x = 50;
    wallHard->wallHardPositionRect.y = 50;
    wallHard->wallHardPositionRect.w = 50;
    wallHard->wallHardPositionRect.h = 60;

    SDL_Surface *wallHardSurface = IMG_Load("images/wallhard.png");

    if (!wallHardSurface) {
        fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
        destroy_game_by_wallHard(interface, wallHard);
        return NULL;
    } else {
        wallHard->TexWallHard = SDL_CreateTextureFromSurface(interface->Renderer, wallHardSurface);

        if (!wallHard->TexWallHard) {
            fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
            destroy_game(interface, wallHard);
            return NULL;
        }

        SDL_FreeSurface(wallHardSurface);
    }
}