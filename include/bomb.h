#include <include/interface.h>

#ifndef BOMB_H_
#define BOMB_H_

typedef struct bomb_s bomb_t;
typedef struct player_s player_t;

struct bomb_s
{
    // Does the bomb exist
    int exist;

    // bomb texture
    SDL_Texture *TexBomb;

    // position of bomb
    SDL_Rect bombPositionRect;
};

bomb_t *init_bomb(interface_t *interface);
void placeBomb(bomb_t *bomb, player_t *player);
void destroy_bomb(bomb_t *bomb);

#endif // BOMB_H_
