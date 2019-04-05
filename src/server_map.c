#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server_bomb.h>
#include <include/server_explosion.h>
#include <include/server.h>
#include <include/server_map.h>

void implement_map(t_server_game *server_game, bomb_server_t *server_bomb, explosion_server_t *server_explosion)
{
    // Clean map and bombs from players
    for (int y = 0; y < 13; y++) {
        for (int x = 0; x < 15; x++) {
            switch (server_game->schema[y][x])
            {
                case '6' :
                case '7' :
                case '8' :
                case '9' :
                case 'A' :
                case 'G' :
                case 'H' :
                case 'I' :
                    server_game->schema[y][x] = '3';
                    break;
            }
        }
    }

    // Implement Elements on the map
    implement_bomb_on_map(server_game, server_bomb);
    implement_player_on_map(server_game);
    implement_explosion_on_map(server_game, server_explosion);
}

void implement_player_on_map(t_server_game *server_game)
{
    // Drop Players on the map
    //
    // if alive Drop Players alive on top
    //  else    Drop Players dead on top
    if (server_game->player1.live == 1) {
        server_game->schema[server_game->player1.y_pos][server_game->player1.x_pos] = '6';
        server_game->schema[0][4] = 'S';
    } else {
        server_game->schema[0][4] = 'W';
    }

    if (server_game->player2.live == 1) {
        server_game->schema[server_game->player2.y_pos][server_game->player2.x_pos] = '7';
        server_game->schema[0][6] = 'T';
    } else {
        server_game->schema[0][6] = 'X';
    }

    if (server_game->player3.live == 1) {
        server_game->schema[server_game->player3.y_pos][server_game->player3.x_pos] = '8';
        server_game->schema[0][8] = 'U';
    } else {
        server_game->schema[0][8] = 'Y';
    }

    if (server_game->player4.live == 1) {
        server_game->schema[server_game->player4.y_pos][server_game->player4.x_pos] = '9';
        server_game->schema[0][10] = 'V';
    } else {
        server_game->schema[0][10] = 'Z';
    }
}

void implement_bomb_on_map(t_server_game *server_game, bomb_server_t *server_bomb)
{
    // Drop the bombs ont the map
    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;
    while (!last_bomb) {
        // If it is not the initial bomb (used for passing in arguments)
        if (the_bomb->player != 0) {
            server_game->schema[the_bomb->y][the_bomb->x] = 'A';
        }

        // go to the next bomb
        if (the_bomb->next != NULL) {
            the_bomb = the_bomb->next;
        } else {
            last_bomb = true;
        }
    }
}

void implement_explosion_on_map(t_server_game *server_game, explosion_server_t *server_explosion)
{
    // Drop the explosions ont the map
    bool last_explosion = false;
    explosion_server_t *the_explosion = server_explosion;
    while (!last_explosion)
    {
        // If it is not the initial bomb (used for passing in arguments)
        if (the_explosion->first != 1)
        {
            // Drop the center of explosion on the map
            server_game->schema[the_explosion->y][the_explosion->x] = 'G';

            // for each way (Up RightDown Left)
            // If not any wall expand the explosion by 1 and allow to continue expansion
            // If a brick wall expand the explosion by 1 and stop expansion
            // If hard wall stop the expansion
            for (int i=1; i < (the_explosion->size + 1); i++ )
            {
                if ( i < (the_explosion->size_up + 1))
                {
                    server_game->schema[(the_explosion->y - i)][the_explosion->x] = 'H';
                }
                if ( i < (the_explosion->size_right + 1)) {
                    server_game->schema[the_explosion->y][(the_explosion->x + i)] = 'I';
                }
                if ( i < (the_explosion->size_down + 1)) {
                    server_game->schema[(the_explosion->y + i)][the_explosion->x] = 'H';
                }
                if ( i < (the_explosion->size_left+ 1)) {
                    server_game->schema[the_explosion->y][(the_explosion->x - i)] = 'I';
                }
            }
        }

        // go to the next explosion
        if (the_explosion->next != NULL)
        {
            the_explosion = the_explosion->next;
        }else{
            last_explosion = true;
        }
    }

}

