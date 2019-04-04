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

    explosion->explTexture = set_texture_explosion(renderer);
    if (explosion->explTexture == NULL) {
        fprintf(stderr, "NO TEXTURE EXPLOSION");
        destroy_explosion(explosion);
        return NULL;
    }

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
    SDL_Surface *surf = IMG_Load("images/tiles_bomberman.png");
    SDL_Texture *texture;

    if (!surf) {
		fprintf(stderr, "unable to load image : %s\n", IMG_GetError());
		return NULL;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, surf);

		if (!texture) {
			fprintf(stderr, "unable to handle texture : %s\n", SDL_GetError());
			SDL_FreeSurface(surf);
			return NULL;
		}

		SDL_FreeSurface(surf);
	}
	return texture;
}