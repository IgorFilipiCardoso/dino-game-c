#include "./main.h"

typedef struct map_type *Map;

// Inicia o TAD do mapa, tendo como argumentos, o propio mapa, a posicao dele e o tamanho.
bool map_init(Map* map, int position_x, int position_y, int width, int height);

// Recebe o mapa, o renderer e o caminho da textura do mapa.
void set_map_textures(Map* map, SDL_Renderer* renderer, char* src);

// Move o mapa da direita para esquerda, ate a metade do mapa, apos isso ele volta para o inicio, fazendo um loop e dando um efeito de movimento.
void move_map(Map* map);

// Coloca o mapa para o renderer, ficando ao aguardo de mostrar na tela.
void render_map(Map map, SDL_Renderer* renderer);

// Destroi a textura para liberar memoria
void destroy_map_texture(Map* map);