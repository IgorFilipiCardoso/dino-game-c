#include "./main.h"

typedef struct count_type *Count;

void count_init(Count* count);

void set_count_texture(Count count, SDL_Renderer* renderer, char* src);

int get_count(Count count);

void render_count(Count count, SDL_Renderer* renderer);

void destroy_texture_count(Count count);