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

player_t *init_player(interface_t *interface);
void movePlayer(player_t *player, interface_t *interface, SDL_Keycode direction, client_t *client_struct);
void destroy_player(player_t *player);
bomb_t *dropBomb(player_t *player, bomb_t *bomb);

#endif /* PLAYER_H_ */