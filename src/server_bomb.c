#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <include/server_bomb.h>
#include <include/server.h>


void create_new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{

    // TODO Yop : Swicth a fonctionner
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
    long time_drop;
    time_drop = time(NULL);
    printf("\n ---- %ld secondes ----\n", time_drop);

    bomb_server_t *bomb = NULL;

    bomb = malloc(sizeof(bomb_server_t));

    if (bomb == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    bomb->x= x;
    bomb->y = y;
    bomb->player = player;
    bomb->time = time_drop;
    bomb->next = NULL;

    return bomb;
}

void bombs_timer(t_server_game *server_game, bomb_server_t *server_bomb)
{
    t_player_infos *the_player;

    long time_actual;
    time_actual = time(NULL);

    printf("\nTIME NOW : %ld\n", time_actual);

    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;

    while (!last_bomb)
    {
        if (the_bomb->player != 0)
        {
            if ((time_actual - the_bomb->time) > 2 )
            {
                printf("DELETTTEEE BOOOOMMMMMB\n");
                server_bomb->next = the_bomb->next;

                // TODO Yop : Swicth a fonctionner
                switch (the_bomb->player)
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

                the_player->bombs_left++;

                free(the_bomb);
            }
        }

        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        }else{
            last_bomb = true;
        }
    }
}
