#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server.h>
#include <include/server_player.h>
#include <include/server_bomb.h>

void player_action(t_server_game *server_game, bomb_server_t *server_bomb, int player, char command) {
    switch (command)
    {
        case 'U' :
        case 'D' :
        case 'L' :
        case 'R' :
            player_move(server_game, player, command);

            bool last_bomb = false;
            bomb_server_t *the_bomb = server_bomb;
            while (!last_bomb)
            {
                printf("BOMB : %d, %p\n", the_bomb->player, the_bomb->next);

                if (the_bomb->next != NULL)
                {
                    the_bomb = the_bomb->next;
                }else{
                    last_bomb = true;
                }
            }

            break;
        case 'B' :
            bomb_drop(server_game, server_bomb, player);
            break;
    }
}

void player_move(t_server_game *server_game, int player, char command)
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

    switch (command)
    {
        case 'U' :
            if (place_is_free(server_game, the_player->x_pos, the_player->y_pos-1)) {
                the_player->y_pos--;
            }
            break;
        case 'D' :
            if (place_is_free(server_game, the_player->x_pos, the_player->y_pos+1)) {
                the_player->y_pos++;
            }
            break;
        case 'L' :
            if (place_is_free(server_game, the_player->x_pos-1, the_player->y_pos)) {
                the_player->x_pos--;
            }
            break;
        case 'R' :
            if (place_is_free(server_game, the_player->x_pos+1, the_player->y_pos)) {
                the_player->x_pos++;
            }
            break;
    }
}

bool place_is_free(t_server_game *server_game, int x, int y)
{
    if (server_game->schema[y][x] == '0' || server_game->schema[y][x] == '1'|| server_game->schema[y][x] == '2')
    {
        return false;
    }

    return true;
}

void bomb_drop(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{
    new_bomb(server_game, server_bomb, player);
}