#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server_bomb.h>
#include <include/server.h>
#include <include/server_map.h>

void implement_map(t_server_game *server_game, bomb_server_t *server_bomb)
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
                    server_game->schema[y][x] = '3';
                    break;
            }
        }
    }

    // Drop Players on the map
    server_game->schema[server_game->player1.y_pos][server_game->player1.x_pos] = '6';
    server_game->schema[server_game->player2.y_pos][server_game->player2.x_pos] = '7';
    server_game->schema[server_game->player3.y_pos][server_game->player3.x_pos] = '8';
    server_game->schema[server_game->player4.y_pos][server_game->player4.x_pos] = '9';

    // Drop the bombs ont the map
    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;
    while (!last_bomb)
    {
        // TODO printf("Bomb Player %d\n", the_bomb->player);
        if (the_bomb->player != 0)
        {
            server_game->schema[the_bomb->y][the_bomb->x] = 'A';
        }

        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        }else{
            last_bomb = true;
        }
    }
}