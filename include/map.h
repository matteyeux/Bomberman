#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef MAP_H_
#define MAP_H_

typedef char tileIndex;
typedef struct map_s map_t;
typedef struct tileProp_s tileProp_t;

struct tileProp_s {
	SDL_Rect	*tile;
	SDL_Texture *textureTile;
	int plein;
	char charTest;
};

struct map_s {
	int largeur_tile;
	int hauteur_tile;
	int nbTileX;
	int nbTileY;
	tileProp_t **tabTiles;
	tileIndex **schema;
	SDL_Texture *mapTexture;
};


void setRectangle(SDL_Rect *rectangle, int x, int y, int w, int h);

map_t *init_map(const char *file);
char **handle_file(const char *file);
SDL_Texture *set_texture_map(SDL_Renderer *pRenderer);
int set_tile_array(map_t *map);

void destroy_map(map_t *map);

#endif