#ifndef SERVER_PLAYER_H_
#define SERVER_PLAYER_H_

typedef struct server_player_s server_player_t;

struct server_player_s
{
    int id; // TODO Yop a supprimer si inutile a l'avenir
    char connected;
    char alive;
    int x_pos;
    int y_pos;
    int current_dir;
    int current_speed;
    int max_speed;
    int bombs_left;
    int bombs_capacity;
    int frags;
};

server_player_t *init_server_player();
//void movePlayer(player_t *player, interface_t *interface, SDL_Keycode direction, client_t *client_struct);
//void destroy_player(player_t *player);
//bomb_t *dropBomb(player_t *player, bomb_t *bomb);

#endif /* PLAYER_H_ */