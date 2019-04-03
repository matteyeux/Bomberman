#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server_bomb.h>
#include <include/server.h>

void create_new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player)
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

    bomb_server_t *new_bomb;
    new_bomb = init_bomb_server(player, the_player->x_pos, the_player->y_pos);

    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;
    while (!last_bomb)
    {
        // TODO Yop : printf("BOMB : %d, %p\n", the_bomb->player, the_bomb->next);
        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        }else{
            the_bomb->next = new_bomb;
            last_bomb = true;

        }
    }

    the_player->bombs_left = the_player->bombs_left - 1;
    printf("Bombs left *** %d\n", the_player->bombs_left);
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
