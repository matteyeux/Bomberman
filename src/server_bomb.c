#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <include/server.h>
#include <include/server_player.h>
#include <include/server_bomb.h>
#include <include/server_explosion.h>

void create_new_bomb(t_server_game *server_game, bomb_server_t *server_bomb, int player)
{
    // Get the player
    t_player_infos *the_player;
    the_player = get_the_player(server_game, player);

    // create a new bomb
    bomb_server_t *new_bomb;
    new_bomb = init_bomb_server(player, the_player->x_pos, the_player->y_pos);

    // put new bomb at the end of the list
    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;
    while (!last_bomb)
    {
        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        }else{
            the_bomb->next = new_bomb;
            last_bomb = true;
        }
    }

    // set on less number of bomb the player can drop
    the_player->bombs_left = the_player->bombs_left - 1;
}

bomb_server_t *init_bomb_server(int player, int x, int y)
{
    // Take unix time of now
    long time_drop;
    time_drop = time(NULL);

    // Create the new bomb
    bomb_server_t *bomb = NULL;
    bomb = malloc(sizeof(bomb_server_t));

    if (bomb == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    // Insert values in the bomb
    bomb->x= x;
    bomb->y = y;
    bomb->player = player;
    bomb->time = time_drop;
    bomb->size = 4;
    bomb->next = NULL;

    return bomb;
}

void bombs_timer(t_server_game *server_game, bomb_server_t *server_bomb, explosion_server_t *server_explosion)
{
    // init valu used for player's info
    t_player_infos *the_player;

    // Take unix time of now
    long time_actual;
    time_actual = time(NULL);

    // init the_bomb for temporary using it in loop
    bool last_bomb = false;
    bomb_server_t *the_bomb = server_bomb;

    while (!last_bomb)
    {
        // If it is not the initial bomb (used for passing in arguments)
        if (the_bomb->player != 0)
        {
            // If time the bomb was drop and now have 2 seconds or more difference
            if ((time_actual - the_bomb->time) > 1 )
            {
                // put address of the next bomb in the initial bomb
                server_bomb->next = the_bomb->next;

                // Get the player
                the_player = get_the_player(server_game, the_bomb->player);

                // Add one bomb to the player possibilities
                the_player->bombs_left++;

                // Create explosion and delete bomb
                create_new_explosion(server_game, server_explosion, the_bomb->size, the_bomb->x, the_bomb->y);
                free(the_bomb);

                // Stop the loop of creating explosion (fix the problem of too big explosion)
                return;
            }
        }

        // go to the next bomb
        if (the_bomb->next != NULL)
        {
            the_bomb = the_bomb->next;
        }else{
            last_bomb = true;
        }
    }
}
