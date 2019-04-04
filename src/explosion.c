#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <include/explosion.h>
#include <include/interface.h>
#include <include/bomberman.h>


explosion_t *init_explosion(SDL_Renderer *renderer)
{
    explosion_t *explosion = malloc(sizeof(explosion_t));
    if (explosion == NULL) {
        fprintf(stderr, "Error malloc Explosion\n");
        return NULL;
    }

    explosion->explTexture = NULL;
    // explosion->srcRect = NULL;
    // explosion->destRect = NULL;

    setRectangle(&explosion->srcRect, 4*16, 3*16, 16, 16);

    return explosion; 
}

void destroy_explosion(explosion_t *explosion)
{
    if (explosion) {
        if (explosion->explTexture)
            SDL_DestroyTexture(explosion->explTexture);

        free(explosion);
    }
}

SDL_Texture *set_texture_explosion(SDL_Renderer *renderer)
{

}