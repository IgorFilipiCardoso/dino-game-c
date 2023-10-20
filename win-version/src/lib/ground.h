#include "./main.h"

typedef struct ground_type *Ground;

// Inicia o TAD do chao, tendo como argumentos o propio chao e algumas informacoes.
bool ground_init(Ground* ground, int position_x, int position_y, int height, int width);

// Coloca a textura do chao no chao.
void set_ground_texture(Ground ground, SDL_Renderer* renderer, char* src);

// Move o chao, da direita para a esquerda.
void move_ground(Ground ground);

// Coloca o chao na fila de espera para renderisar
void render_ground(Ground ground, SDL_Renderer* renderer);

// Destroi a textura para liberar memoria
void destroy_ground_texture(Ground ground);
