#include "../include/interface.h"
#include "../include/map.h"

interface_t *init_interface(map_t *map)
{
    // Déclaration de la structure Interface
    interface_t *interface = NULL;

    // Allocation de l'interface
    interface = malloc(sizeof(interface_t));
    if (interface == NULL) {
        printf("Error construction window\n");
        return (NULL);
    }

    // Paramétrage de la fenêtre
    interface->screenSize.x = map->largeur_tile * map->nbTileY;
    interface->screenSize.y = map->hauteur_tile * map->nbTileX;
    interface->pWindow = NULL;
    interface->pRenderer = NULL;
    interface->destRect = NULL;
    interface->map = map;

    interface->destRect = malloc(sizeof(SDL_Rect));
    if (interface->destRect == NULL) {
        printf("Error malloc rect pour la map\n");
        destroy_interface(interface);
        return (NULL);
    }

    /**
     *  SDL ONLY
     */

    // Génération de la window
    interface->pWindow = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        interface->screenSize.x, interface->screenSize.y, SDL_WINDOW_SHOWN);

    // Si la window est OK, on génère le Renderer (Activation du rendu de la CG)
    if (interface->pWindow) {
        interface->pRenderer = SDL_CreateRenderer(interface->pWindow, -1, SDL_RENDERER_ACCELERATED);
        if (!interface->pRenderer) {
            printf("Renderer KO\n");
            destroy_interface(interface);
            return (NULL);
        }
        printf("Création Renderer OK\n");
    } else {
        printf("Window KO \n");
        destroy_interface(interface);
        return (NULL);
    }

    return (interface);
}

void destroy_interface(interface_t *interface)
{
    if (interface) {

        if (interface->destRect)
            free(interface->destRect);

        if (interface->pRenderer)
            SDL_DestroyRenderer(interface->pRenderer);

        if (interface->pWindow)
            SDL_DestroyWindow(interface->pWindow);
        
        SDL_Quit();

        free(interface);
    }
    printf("Destruction de l'interface OK\n");
}

void draw_interface(interface_t *interface)
{
    SDL_SetRenderDrawColor(interface->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(interface->pRenderer);
    
    // TESTS
    //setRectangle(interface->destRect, 0, 0, 45, 45);
    //SDL_RenderCopy(interface->pRenderer, interface->map->mapTexture, NULL, interface->destRect);
    
    // REAL EXECUTION

    map_t *map = interface->map;
         
    for (int i = 0; i < map->nbTileY; i++) {
        for (int j = 0; j < map->nbTileX; j++) {
            //setRectangle(interface->destRect, 45*i, 45*j, 45, 45);
            setRectangle(interface->destRect, map->largeur_tile*i, map->hauteur_tile*j, map->largeur_tile, map->hauteur_tile);

            // index contient le code ascii du caractère
            int index = map->schema[j][i]-48;
            SDL_RenderCopy(interface->pRenderer, map->mapTexture, map->tabTiles[index]->tile, interface->destRect);

        }
    }
    
    SDL_RenderPresent(interface->pRenderer);
}
