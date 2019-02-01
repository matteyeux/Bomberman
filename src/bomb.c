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

    bomb->bombPositionRect.x = interface->screenSize.x / 2;
    bomb->bombPositionRect.y = interface->screenSize.y / 2;
    bomb->bombPositionRect.w = 40;
    bomb->bombPositionRect.h = 40;

    // load bomb texture
    SDL_Surface *bombSurface = IMG_Load("images/bomb.png");

    if (!bombSurface) {
        fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
        destroy_game_by_bomb(interface, bomb);
        return NULL;
    } else {
        bomb->TexBomb = SDL_CreateTextureFromSurface(interface->Renderer, bombSurface);

        if (!bomb->TexBomb) {
            fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
            destroy_game(interface, bomb);
            return NULL;
        }

        SDL_FreeSurface(bombSurface);
    }

    return bomb;
}

void moveBomb(bomb_t *bomb, interface_t *interface, SDL_Keycode direction)
{
    if (direction == SDLK_UP){
        if (bomb->bombPositionRect.y > 0) {
            bomb->bombPositionRect.y -= 10;
        }
    } else if (direction == SDLK_DOWN) {
        if (bomb->bombPositionRect.y < (interface->screenSize.y - bomb->bombPositionRect.h)) {
            bomb->bombPositionRect.y += 10;
        }
    } else if (direction == SDLK_LEFT) {
        if (bomb->bombPositionRect.x > 0) {
            bomb->bombPositionRect.x -= 10;
        }
    } else if (direction == SDLK_RIGHT) {
        if (bomb->bombPositionRect.x < (interface->screenSize.x - bomb->bombPositionRect.w)) {
            bomb->bombPositionRect.x += 10;
        }
    } else {
        fprintf(stderr, "unknown direction\n");
    }
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
