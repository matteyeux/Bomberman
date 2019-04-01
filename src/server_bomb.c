#include <stdio.h>
#include <stdlib.h>
#include <include/server_bomb.h>
#include <include/server.h>

void new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{
    t_player_infos *the_player;

    switch (player)
    {
        case 1 :
            the_player = &server_game->player1;
            break;
        case 2 :
            the_player = &server_game->player2;
            break;
        case 3 :
            the_player = &server_game->player3;
            break;
        case 4 :
            the_player = &server_game->player4;
            break;
    }

    if (server_bomb->next == NULL)
    {
        printf("NULLLLLLL\n");
    }else{
        printf("EXIST !!!!!\n");
    }

    bomb_server_t *new_bomb;
    new_bomb = init_bomb_server(player, the_player->x_pos, the_player->y_pos);

    //printf("BOMB : %d %d\n", new_bomb->x, new_bomb->y);

    server_bomb = &new_bomb;

    printf("NewBomPoint : %p\n", &new_bomb);
    //server_bomb->next = &new_bomb;

    if (server_bomb->next == NULL)
    {
        printf("NULLLLLLL\n");
    }else{
        printf("EXIST !!!!!\n");
    }
}


bomb_server_t *init_bomb_server(int player, int x, int y)
{
    bomb_server_t *bomb = NULL;

    bomb = malloc(sizeof(bomb_server_t));

    if (bomb == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    bomb->x= x;
    bomb->y = y;
    bomb->player = player;
    bomb->time = 0;
    bomb->next = NULL;

    return bomb;
}
