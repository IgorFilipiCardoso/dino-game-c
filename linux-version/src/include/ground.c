#include "../lib/ground.h"

struct type_ground
{
    int x, y;
    int height, width;
    SDL_Texture *ground_texture;
};

bool init_ground(Ground *ground, int position_x, int position_y, int height, int width)
{
    (*ground) = malloc(sizeof(Ground));

    (*ground)->y = position_y;
    (*ground)->x = position_x;
    (*ground)->height = height;
    (*ground)->width = width;
}

void move_ground(Ground *ground);

void render_ground(SDL_Renderer *renderer, Ground *ground);

void set_ground_texture(Ground *ground, SDL_Renderer *renderer, char *src);
