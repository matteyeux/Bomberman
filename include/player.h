#include <include/bomb.h>
#include <include/interface.h>
#include <include/client.h>

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct player_s player_t;

struct player_s
{
	int magic;
	int score;
	int speed;
	int dir;
	char command;

	SDL_Texture *playerTexture;
    SDL_Rect    *srcRectPlayer;
    SDL_Rect    *destRectPlayer;
    int         posX, posY;
};

void movePlayer(player_t *player, interface_t *interface, SDL_Keycode direction, client_t *client_struct);
bomb_t *dropBomb(player_t *player, bomb_t *bomb);

player_t *init_player(void);
void destroy_player(player_t *player);
SDL_Texture *set_texture_player(SDL_Renderer *pRenderer);

#endif /* PLAYER_H_ */