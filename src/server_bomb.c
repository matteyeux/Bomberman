#include <stdio.h>
#include <stdlib.h>
#include <include/server_bomb.h>
#include <include/server.h>

void new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{
    printf("GOTTTAAA\n");

    if (server_bomb == NULL)
    {
        printf("NULLLLLLL\n");
    }else{
        printf("EXIST !!!!!\n");
    }

    //bomb_server_t *new_bomb;
    //new_bomb = init_bomb_server(player);
}


bomb_server_t *init_bomb_server(int player)
{
    bomb_server_t *bomb = NULL;

    bomb = malloc(sizeof(bomb_server_t));

    if (bomb == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    bomb->x= 0;
    bomb->y = 0;
    bomb->player = player;
    bomb->time = 0;
    //bomb->next = ;

    return bomb;
}
