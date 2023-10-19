#include "./main.h"

typedef struct ground_type *Ground;

bool init_ground(Ground *ground, int position_x, int position_y, int height, int width);

void move_ground(Ground* ground);

void render_ground(SDL_Renderer* renderer, Ground* ground);

void set_ground_texture(Ground* ground, SDL_Renderer* renderer, char* src);


