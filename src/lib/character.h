#include "./main.h"

typedef struct character_type *Character;

// Cria o personagem
bool character_init(Character *character, int position_x, int position_y, int width, int height);

// Faz com que o persongem pule, retorna um bool, indicando se pulou ou nao.
void jump(Character character);

// Retorna se o personame pode realizar o pulo
bool can_jump(Character character);

void fall(Character character);

// Cria um especie de gravidade, onde o personagem e puxado para baixo.
void gravity(Character character);

// Renderiza o personagem na tela
void render_character_step(Character character, SDL_Renderer* renderer,  SDL_Window* window);

// Processa uma textura para o personagem
void set_character_textures(Character character, SDL_Renderer* renderer, char *src_texture1, char* src_texture2, char* src_texture3);

// Retorna por referencia, quatro calculos de posisao para saber a colisao do personagem com outra coisa.
void get_character_colision(Character character, double *x1, double *x2, double *y1, double *y2);

// Destroi a textura para liberar memoria
void destroy_character_texture(Character character);

