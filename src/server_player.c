#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server.h>
#include <include/server_player.h>
#include <include/server_bomb.h>

void player_action(t_server_game *server_game, bomb_server_t *server_bomb, int player, char command)
{
    // Get the player
    t_player_infos *the_player;
    the_player = get_the_player(server_game, player);

    // If player is dead, don't take any information
    if (the_player->live != 1)
    {
        printf("IS DEAD\n");
        return;
    }

    // Check the command of the player
    switch (command)
    {
        case 'U' :
        case 'D' :
        case 'L' :
        case 'R' :
            player_move(server_game, server_bomb, player, command);

            break;
        case 'B' :
            if (the_player->bombs_left > 0)
            {
                bomb_drop(server_game, server_bomb, player);
            }
            break;
    }
}

t_player_infos *get_the_player(t_server_game *server_game, int player)
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

    return the_player;
}

void player_move(t_server_game *server_game, bomb_server_t *server_bomb, int player, char command)
{
    // Get the player
    t_player_infos *the_player;
    the_player = get_the_player(server_game, player);

    // For each command check if : place is free, no player on place, no bomb on place
    //     -> then move
    switch (command)
    {
        case 'U' :
            if (place_is_free(server_game, the_player->x_pos, the_player->y_pos-1)
            && place_is_free_of_player(server_game, the_player->x_pos, the_player->y_pos-1)
            && place_is_free_of_bomb(server_bomb, the_player->x_pos, the_player->y_pos-1)) {
                the_player->y_pos--;
            }
            break;
        case 'D' :
            if (place_is_free(server_game, the_player->x_pos, the_player->y_pos+1)
            && place_is_free_of_player(server_game, the_player->x_pos, the_player->y_pos+1)
            && place_is_free_of_bomb(server_bomb, the_player->x_pos, the_player->y_pos+1)) {
                the_player->y_pos++;
            }
            break;
        case 'L' :
            if (place_is_free(server_game, the_player->x_pos-1, the_player->y_pos)
            && place_is_free_of_player(server_game, the_player->x_pos-1, the_player->y_pos)
            && place_is_free_of_bomb(server_bomb, the_player->x_pos-1, the_player->y_pos)) {
                the_player->x_pos--;
            }
            break;
        case 'R' :
            if (place_is_free(server_game, the_player->x_pos+1, the_player->y_pos)
            && place_is_free_of_player(server_game, the_player->x_pos+1, the_player->y_pos)
            && place_is_free_of_bomb(server_bomb, the_player->x_pos+1, the_player->y_pos)) {
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

bool place_is_free_of_player(t_server_game *server_game, int x, int y)
{
    if (server_game->player1.x_pos == x && server_game->player1.y_pos == y && server_game->player1.live == 1)
    {
        return false;
    }

    if (server_game->player2.x_pos == x && server_game->player2.y_pos == y && server_game->player2.live == 1)
    {
        return false;
    }

    if (server_game->player3.x_pos == x && server_game->player3.y_pos == y && server_game->player3.live == 1)
    {
        return false;
    }

    if (server_game->player4.x_pos == x && server_game->player4.y_pos == y && server_game->player4.live == 1)
    {
        return false;
    }

    return true;
}

bool place_is_free_of_bomb(bomb_server_t *server_bomb, int x, int y)
{
    // init the_bomb for temporary using it in loop
    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;

    // for each bomb, we check the place
    while (!last_bomb) {
        // Check if there is bomb in the place
        if (the_bomb->x == x && the_bomb->y == y)
        {
            return false;
        }

        // go to the next bomb of the chained list or break the while
        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        } else {
            last_bomb = true;
        }
    }

    // default return true
    return true;
}

void bomb_drop(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{
    create_new_bomb(server_game, server_bomb, player);
}