#include "../include/map.h"

#define CACHE_SIZE 64

map_t *init_map(const char *file)
{
	// Malloc de la Map
	map_t *map = malloc(sizeof(map_t));
	if (map == NULL) {
		printf("Error Malloc MAP\n");
		return (NULL);
	}

	// Settings de la map
	map->hauteur_tile = 60;
	map->largeur_tile = 60;

	//map->tabTiles = malloc(map->nbTileY * sizeof(tileProp_t*));
	//malloc de nbLignes * sizeof(char*)
	map->schema = malloc(13 * sizeof(char*));
	if (map->schema == NULL) {
		printf("Erreur sur le malloc du schema");
		destroy_map(map);
		return (NULL);
	}

	map->tabTiles = malloc(5*sizeof(tileProp_t));
	if( map->tabTiles == NULL) {
		printf("Error Malloc TabTile\n");
		destroy_map(map);
		return (NULL);
	}
	// Association de la map en fichier vers le schema de la map
	traitement_file(file, map);

	return (map);
}


void destroy_map(map_t *map)
{
	if (map) {
		if (map->tabTiles) {
			for (int i = 0; i < 5; i++) {
				if (map->tabTiles[i]) {
				
					// Free chaque rectangle du tableau de tile
					if (map->tabTiles[i]->tile)
						free(map->tabTiles[i]->tile);

					// Free la tile courante du tableau de tile
					free(map->tabTiles[i]);
				}
			}
			free(map->tabTiles);
		}

		if (map->mapTexture)
			SDL_DestroyTexture(map->mapTexture);

		if (map->schema) {
			for (int i = 0; i < map->nbTileY; i++) {
				if (map->schema[i])
					free(map->schema[i]);
				else
					break;
			}
			free(map->schema);
		}
		free(map);
	}
}


void setRectangle(SDL_Rect *rectangle, int x, int y, int w, int h)
{
    rectangle->x = x;
    rectangle->y = y;
    rectangle->w = w;
    rectangle->h = h;
}

void traitement_file(const char *file, map_t *map)
{
	FILE *f;
	int i = 0;
	char buf[CACHE_SIZE];

	f = fopen(file, "r");
	if (!f) 
		printf("Error read File\n");

	// Tant qu'on est pas à la fin du fichier, la ligne courante est insérée dans "buf"
    while (fgets(buf, CACHE_SIZE, f) != NULL) {
		map->schema[i] = strdup(buf);
		i++;
	}

	// i = nombre de lignes, strlen(buf) = nombre de colonnes
	map->nbTileX = i;
	map->nbTileY = strlen(buf);

	fclose(f);
}

SDL_Texture *set_texture_map(SDL_Renderer *pRenderer)
{
	SDL_Texture *texture = NULL;

	// Génération de la texture de la map
	SDL_Surface *surf = IMG_Load("images/tiles_bomberman.png");

    if (surf == NULL) {
        fprintf(stderr, "surface KO \n %s \n", IMG_GetError());
        return (NULL);
    } else {
        
		texture = SDL_CreateTextureFromSurface(pRenderer, surf);
        if (texture == NULL) {
            printf("texture KO \n");
            SDL_FreeSurface(surf);
            return (NULL);
        }

        SDL_FreeSurface(surf);
    }

	return (texture);
}

int set_tile_array(map_t *map)
{
	// Association d'un tableau de tile pour la map 
	tileProp_t *tiles = NULL;
    for (int i = 0; i < 5; i++) {
        tiles = malloc(sizeof(tileProp_t));
        if (tiles == NULL) {
            printf("Error malloc UNE TILE pour la map\n");
			destroy_map(map);
            //destroy_interface(interface);
            return (0);
        }

        tiles->plein = 1;
        tiles->tile = malloc(sizeof(SDL_Rect));
        if (!tiles->tile) {
            printf("Error malloc rect pour la map\n");
			destroy_map(map);
            //destroy_interface(interface);
            return (0);
        }

        setRectangle(tiles->tile, 16*i, 0, 16, 16);
        tiles->charTest = i+48;
        map->tabTiles[i] = tiles;
    }
	return (1);
}