#include <include/interface.h>

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

typedef struct explosion_s {

    SDL_Texture     *explTexture;
    SDL_Rect        destRect;
    SDL_Rect        srcRect;
    char            type;

    

} explosion_t;

explosion_t *init_explosion(SDL_Renderer *renderer);
void destroy_explosion(explosion_t *explosion);
SDL_Texture *set_texture_explosion(SDL_Renderer *renderer);


#endif