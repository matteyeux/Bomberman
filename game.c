#include "game.h"

stGame *game_init()
{
    stGame *game = NULL;
    game = malloc(sizeof(stGame));

    // Définition de la taille de l'écran dans la structure
    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;
    game->pTexPlayer = NULL;

    printf("Game Init \n");

    // Initialisation de la fenêtre
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Bug SDL: %s\n", SDL_GetError());
        game_destroy(game);
        return (NULL);
    }

    // Création de la window de jeu
    game->pWindow = SDL_CreateWindow(
        "Title", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        game->screenSize.x, game->screenSize.y,
        SDL_WINDOW_OPENGL);

    if (game->pWindow) {
        game->pRenderer = SDL_CreateRenderer(game->pWindow, -1, SDL_RENDERER_ACCELERATED);
        if (!game->pRenderer) {
            fprintf(stderr, "Bug Renderer: %s\n", SDL_GetError());
            game_destroy(game);
            return (NULL);
        }
    } else {
        fprintf(stderr, "Bug Window: %s\n", SDL_GetError());
        game_destroy(game);
        return (NULL);
    }

    // Création d'une texture
    // nécessite une surface
    SDL_Surface *sdlSurface = IMG_Load("./img.png");
    if (!sdlSurface) {
        //fprintf(stderr, "Bug Surface: %s\n", IMG_GetError());
        game_destroy(game);
        return (NULL);
    } else {

        // Création de la texture depuis la surface
        game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRenderer, sdlSurface);
        if (!game->pTexPlayer) {
            fprintf(stderr, "Bug Texture: %s\n", SDL_GetError());
            game_destroy(game);
            return (NULL);
        } else {
            SDL_FreeSurface(sdlSurface);
        }
    }

    return game;
}

void game_destroy(stGame *game)
{
    // Si la structure existe
    if (game) {

        // Si la texture existe
        if (game->pTexPlayer) {
            printf("Free du Texture \n");
            SDL_DestroyTexture(game->pTexPlayer);
        }

        // Si le renderer existe 
        if (game->pRenderer) {
            printf("Free du renderer \n");
            SDL_DestroyRenderer(game->pRenderer);
            //free(game->pRenderer);
        }

        // Si la fenêtre existe
        if (game->pWindow) {
            printf("Free de la Window \n");
            SDL_DestroyWindow(game->pWindow);
            //free(game->pWindow);
        }
        SDL_Quit();

        printf("Game Destroy\n");

        free(game);
    }
}