#include <stdio.h>
#include "../include/interface.h"
#include "../include/player.h"
#include "../include/map.h"

int game_event(void);

int main (void)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return (EXIT_FAILURE);
    
    interface_t *interface = NULL;
    map_t *map = NULL;

    printf("Création de l'interface de test\n");
    map = init_map("map.txt");

    printf("Map INITED\n");

    interface = init_interface(map);

    printf("Interface INITED\n");

    map->mapTexture = set_texture_map(interface->pRenderer);

    if (!set_tile_array(map)) {
        printf("Probleme pour set le tileArray\n");

        destroy_map(map);
        destroy_interface(interface);
        return (EXIT_FAILURE);
    }
    
    int result = 0;
        
    printf("test debug\n");

    while (result != -1) {
        draw_interface(interface);
        result = game_event();
    }

    printf("Destruction de l'interface de test\n");
    
    destroy_map(interface->map);
    destroy_interface(interface);

    return (EXIT_SUCCESS);
}

int game_event(void)
{
    int result = 0;

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            result = -1;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    result = -1;
                    break;
                default:
                    result = 0;
                    break;
            }
            printf("KEY CODE : %d\n",e.key.keysym.sym);
        }

    }

    return (result);
}