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
    long time_drop;
    time_drop = time(NULL);
    explosion_server_t *explosion = NULL;
    explosion = malloc(sizeof(explosion_server_t));

    if (explosion == NULL) {
        fprintf(stderr, "[MALLOC] unable to allocate memory\n");
        return NULL;
    }

    explosion->first = false;
    explosion->x= x;
    explosion->y = y;
    explosion->size = size;
    explosion->size_right = 1;
    explosion->size_left = size;
    explosion->size_down = size;
    explosion->time = time_drop;
    explosion->prev = NULL;
    explosion->next = NULL;

    bool up     = true;
    bool right  = true;
    bool down   = true;
    bool left   = true;


    for (int i=1; i < (explosion->size + 1); i++ )
    {
        if (up && !wall_in_place(server_game, x, y - 1))
        {
            explosion->size_up = i;
        }else{
            up = false;
        }
    }


    return explosion;
}

bool wall_in_place(t_server_game *server_game, int x, int y)
{
    switch (server_game->schema[y][x])
    {
        case '2' :
            //printf("\nBREAK THE WALL ^^^^^ \n");
        case '1' :
            return true;
    }

    return false;
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