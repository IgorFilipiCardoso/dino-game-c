#include "./main.h"

typedef struct character_type *Character;

// Cria o personagem
bool init_character(Character *character, int position_x, int position_y, int width, int height);

// Faz com que o persongem pule, retorna um bool, indicando se pulou ou nao.
bool jump(Character* character, SDL_Renderer* renderer);

// Cria um especie de gravidade, onde o personagem e puxado para baixo.
void gravity(Character* character);

// Renderiza o personagem na tela
void render_character_step(SDL_Renderer* renderer, Character* character);

// Processa uma textura para o personagem
void set_character_textures(Character* character, SDL_Renderer* renderer, char *src_texture1, char* src_texture2, char* src_texture3);

// Retorna por referencia, quatro calculos de posisao.
void get_colision(Character character, int *x1, int *x2, int *y1, int *y2);


