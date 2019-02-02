#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/bomb.h>
#include <include/interface.h>
#include <include/bomberman.h>

bomb_t *init_bomb(interface_t *interface)
{
    bomb_t *bomb = NULL;

    bomb = malloc(sizeof(bomb_t));

    if (bomb == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    bomb->exist = 0;
    bomb->bombPositionRect.x = 156;
    bomb->bombPositionRect.y = 78;
    bomb->bombPositionRect.w = 40;
    bomb->bombPositionRect.h = 40;

    // load bomb texture
    SDL_Surface *bombSurface = IMG_Load("images/bomb.png");

    if (!bombSurface) {
        fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
        return NULL;
    } else {
        bomb->TexBomb = SDL_CreateTextureFromSurface(interface->Renderer, bombSurface);

        if (!bomb->TexBomb) {
            fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
            destroy_bomb(bomb);
            return NULL;
        }

        SDL_FreeSurface(bombSurface);
    }

    return bomb;
}

void placeBomb(bomb_t *bomb, player_t *player)
{
    bomb->exist= 1;
    bomb->bombPositionRect.x = player->playerPositionRect.x + 5;
    bomb->bombPositionRect.y = player->playerPositionRect.y + 20;
}

void destroy_bomb(bomb_t *bomb)
{
    if (bomb) {
        if (bomb->TexBomb) {
            SDL_DestroyTexture(bomb->TexBomb);
        }

        free(bomb);
    }
}
