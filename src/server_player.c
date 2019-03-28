#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <include/server_player.h>
#include <include/server.h>

void player_action(t_server_game *server_game, int player, char command) {
    switch (command)
    {
        case 'U' :
        case 'D' :
        case 'L' :
        case 'R' :
            player_move(server_game, player, command);
            break;
        case 'B' :
            bomb_drop();
            break;
    }
}

void player_move(t_server_game *server_game, int player, char command) {

    printf("\n\n\n__ %d _ %c\n", player, command);

    switch (command)
    {
        case 'U' :
            if (place_is_free(server_game, server_game->player1.x_pos, server_game->player1.y_pos-1)) {
                server_game->player1.y_pos--;
            }
            break;
        case 'D' :
            if (place_is_free(server_game, server_game->player1.x_pos, server_game->player1.y_pos+1)) {
                server_game->player1.y_pos++;
            }
            break;
        case 'L' :
            if (place_is_free(server_game, server_game->player1.x_pos-1, server_game->player1.y_pos)) {
                server_game->player1.x_pos--;
            }
            break;
        case 'R' :
            if (place_is_free(server_game, server_game->player1.x_pos+1, server_game->player1.y_pos)) {
                server_game->player1.x_pos++;
            }

            break;
    }

    // TODO Yop : Debug a virer
    //if (1 == 1) {
    //    server_game->schema[2][2] = 'Z';
    //}
}

bool place_is_free(t_server_game *server_game, int x, int y)
{
    // TODO Yop printf("=== %c en x%d y%d\n", server_game->schema[y][x], x, y);
    if (server_game->schema[y][x] == '0' || server_game->schema[y][x] == '1'|| server_game->schema[y][x] == '2') {
        printf("NOOOOO\n");
        return false;
    }

    return true;
}

void bomb_drop()
{
    printf("DROP THE BOMB !!!\n");
}

/*
server_player_t *init_server_player(int num_player)
{
    server_player_t *server_player = NULL;

    server_player = malloc(sizeof(server_player_t));

    if (server_player == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    switch (num_player)
    {
        case 1 :
            server_player->x_pos = 0;
            server_player->y_pos = 0;
            break;
        case 2 :
            server_player->x_pos = 100;
            server_player->y_pos = 0;
            break;
        case 3 :
            server_player->x_pos = 50;
            server_player->y_pos = 0;
            break;
        case 4 :
            server_player->x_pos = 50;
            server_player->y_pos = 100;
            break;
    }

    server_player->connected = 'Y';
    server_player->alive = 'Y';
    server_player->current_dir = 3;
    server_player->current_speed = 10;
    server_player->max_speed = 10;
    server_player->bombs_left = 1;
    server_player->bombs_capacity = 1;
    server_player->frags = 0;

    return server_player;
}
*/