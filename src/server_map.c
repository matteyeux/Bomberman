#include <include/server_map.h>

void implement_map(t_server_game *server_game)
{
    // Clean map from players
    for (int y = 0; y < 13; y++) {
        for (int x = 0; x < 15; x++) {
            switch (server_game->schema[y][x])
            {
                case '6' :
                case '7' :
                case '8' :
                case '9' :
                    server_game->schema[y][x] = '3';
                    break;
            }
        }
    }

    server_game->schema[server_game->player1.y_pos][server_game->player1.x_pos] = '6';
    server_game->schema[server_game->player2.y_pos][server_game->player2.x_pos] = '7';
    server_game->schema[server_game->player3.y_pos][server_game->player3.x_pos] = '8';
    server_game->schema[server_game->player4.y_pos][server_game->player4.x_pos] = '9';
}