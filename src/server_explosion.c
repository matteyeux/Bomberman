#include <stdbool.h>
#include <include/server_explosion.h>
#include <time.h>

void create_new_explosion(explosion_server_t *server_explosion, int size, int x, int y)
{
    printf("CREATE EXPLOSION  !!!!!!!!\n");


    explosion_server_t *new_explosion;
    new_explosion = init_explosion_server(size, x, y);

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


explosion_server_t *init_explosion_server(int size, int x, int y)
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
    explosion->time = time_drop;
    explosion->prev = NULL;
    explosion->next = NULL;

    return explosion;
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