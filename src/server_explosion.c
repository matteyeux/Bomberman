#include <stdbool.h>
#include <include/server_explosion.h>
#include <time.h>

void create_new_explosion(t_server_game *server_game, explosion_server_t *server_explosion, int size, int x, int y)
{
    printf("CREATE EXPLOSION  !!!!!!!!\n");

    explosion_server_t *new_explosion;
    new_explosion = init_explosion_server(server_game, size, x, y);

    bool last_explosion = false;
    explosion_server_t *the_explosion = server_explosion;
    while (!last_explosion)
    {
        // TODO Yop : printf("BOMB : %d, %p\n", the_bomb->player, the_bomb->next);
        if (the_explosion->next != NULL)
        {
            the_explosion = the_explosion->next;
        }else{
            the_explosion->next = new_explosion;
            last_explosion = true;
        }
    }
}


explosion_server_t *init_explosion_server(t_server_game *server_game, int size, int x, int y)
{
    // Init time drop of explosion
    long time_drop;
    time_drop = time(NULL);

    // init explosion
    explosion_server_t *explosion = NULL;
    explosion = malloc(sizeof(explosion_server_t));

    if (explosion == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    // Init explosion datum
    explosion->first = false;
    explosion->x= x;
    explosion->y = y;
    explosion->size = size;
    explosion->time = time_drop;
    explosion->prev = NULL;
    explosion->next = NULL;

    // Init booleens for checks
    bool up     = true;
    bool right  = true;
    bool down   = true;
    bool left   = true;

    // Check for each blocs of explosion (walls and bricks stop it)
    for (int i=1; i < (explosion->size + 1); i++)
    {
        if (up)
        {
            switch (wall_in_place(server_game, x, y - i))
            {
                case 0:
                    explosion->size_up = i;
                    kill_player_on_place(server_game, x, y - i);
                    break;
                case 2:
                    explosion->size_up = i;
                    up = false;
                    break;
                case 1:
                    up = false;
                    break;
            }
        }

        if (right)
        {
            switch (wall_in_place(server_game, x + i, y))
            {
                case 0:
                    explosion->size_right = i;
                    kill_player_on_place(server_game, x + i, y);
                    break;
                case 2:
                    explosion->size_right = i;
                    right = false;
                    break;
                case 1:
                    right = false;
                    break;
            }
        }

        if (down)
        {
            switch (wall_in_place(server_game, x, y + i))
            {
                case 0:
                    explosion->size_down = i;
                    kill_player_on_place(server_game, x, y + i);
                    break;
                case 2:
                    explosion->size_down = i;
                    down = false;
                    break;
                case 1:
                    down = false;
                    break;
            }
        }

        if (left)
        {
            switch (wall_in_place(server_game, x - i, y))
            {
                case 0:
                    explosion->size_left = i;
                    kill_player_on_place(server_game, x - i, y);
                    break;
                case 2:
                    explosion->size_left = i;
                    left = false;
                    break;
                case 1:
                    left = false;
                    break;
            }
        }
    }

    return explosion;
}

int wall_in_place(t_server_game *server_game, int x, int y)
{
    // Return 0 for nothing, 1 for hardwall, 2 for bricks
    switch (server_game->schema[y][x])
    {
        case '2' :
            printf("\n--> FOUND THE BRICKS ^^^^^ \n");
            return 2;
        case '1' :
            printf("\n--> FOUND THE HARD WALL ^^^^^ \n");
            return 1;
    }

    return 0;
}

void kill_player_on_place(t_server_game *server_game, int x, int y)
{
    if (server_game->player1.x_pos == x && server_game->player1.y_pos == y)
    {
        server_game->player1.live = 0;
    }

    if (server_game->player2.x_pos == x && server_game->player2.y_pos == y)
    {
        server_game->player2.live = 0;
    }

    if (server_game->player3.x_pos == x && server_game->player3.y_pos == y)
    {
        server_game->player3.live = 0;
    }

    if (server_game->player4.x_pos == x && server_game->player4.y_pos == y)
    {
        server_game->player4.live = 0;
    }
}

void explosions_timer(explosion_server_t *server_explosion)
{
    // TODO : Debug Explosion
    //bool last_explosion = false;
    //explosion_server_t *the_explosion = server_explosion;
    //while (!last_explosion)
    //{
    //    printf("EXPLODE : %p, %ld\n", the_explosion->next, the_explosion->time);
    //
    //    if (the_explosion->next != NULL)
    //    {
    //        the_explosion = the_explosion->next;
    //    }else{
    //        last_explosion = true;
    //    }
    //}


    long time_actual;
    time_actual = time(NULL);

    bool last_explosion = false;
    explosion_server_t *the_explosion = server_explosion;

    while (!last_explosion)
    {
        if (the_explosion->first != 1)
        {
            if ((time_actual - the_explosion->time) > 1 ) // TODO : time for explosion explode
            {
                server_explosion->next = the_explosion->next;
                free(the_explosion);
            }
        }

        if (the_explosion->next != NULL)
        {
            the_explosion = the_explosion->next;
        }else{
            last_explosion = true;
        }
    }
}