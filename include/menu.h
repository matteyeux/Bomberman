#include <include/interface.h>

#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#define TRUE 1
#define true 1
#define false 0
#define FALSE 0

typedef enum gameState gameState;
typedef struct Images Images;
typedef struct Button Button;
typedef struct Buttons Buttons;
typedef struct menu_return_s menu_return_t;

enum gameState {
    MENU, JOIN, EXIT
};
struct Images {
    SDL_Texture* mainMenuTex;
    SDL_Texture* joinPartyMenuTex;
};

struct Button {
    int min_x, max_x, min_y, max_y;
};

struct Buttons {
    Button createPartyBtn;
    Button joinPartyBtn;
    Button validateBtn;
    Button returnBtn;
    Button exitBtn;
};

struct menu_return_s {
    char *ip;
    u_short port;
    int ret;
};

menu_return_t *menu(void);
void init_buttons(Buttons *btns);
void load_images(Images *images, SDL_Renderer *renderer);
int display_image(SDL_Renderer *renderer, SDL_Texture *texture);
int mouse_bouton(int x, int y, Buttons btns);
void free_images(Images *images);

#endif