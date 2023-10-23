#include "./main.h"

typedef struct obstacle_type *Obstacle;

// Inicia o obstaculo e coloca seus valores, como posicao e tamanho.
bool obstacle_init(Obstacle *obstacle, int position_x, int position_y, int width, int height);

// Coloca o obstaculo no renderer.
void render_obstacle(Obstacle obstacle, SDL_Renderer *renderer,  SDL_Window* window);

// Move o objeto da direita para esquerda.
void move_obstacle(Obstacle obstacle, SDL_Window* window);

bool has_passed(Obstacle obstacle);

void set_passed(Obstacle obstacle);

// Coloca as texturas do obstaculo, recebendo o obstaculo, o renderer e o caminho da imagem, em string.
void set_obstacle_textures(Obstacle obstacle, SDL_Renderer *renderer, char* src);

// Retorna por referencia, quatro calculos de posisao para saber a colisao do obstaculo com outra coisa.
void get_obstacle_colision(Obstacle obstacle, double *x1, double *x2, double *y1, double *y2);

// Destroi a textura para liberar memoria
void destroy_obstacle_texture(Obstacle obstacle);

