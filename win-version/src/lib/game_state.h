#include "./main.h"
#include "./character.h"
#include "./ground.h"
#include "./map.h"
#include "./obstacle.h"

typedef struct game_state_type *Game_state;

// Inicia o jogo e define o delay, que e o quao lento o jogo vai rodar, quanto menor, mais rapido.
bool game_state_init(Game_state* game_state, int delay);

// Carrega as texturas do jogo nos TAD e no renderer.
void game_load_textures(Game_state* game_state, SDL_Renderer* renderer);

// Move, de acordo com a velocidade, todos da esquerda para direita.
void move_everithing(Game_state *game_state);

// Renderiza tudo na tela, 1 frame.
void game_render(Game_state* game_state, SDL_Renderer* renderer);

// Processa os eventos, como cliques e entradas do teclado. Se retornar true indica que o jogo deve parar.
bool process_events(Game_state* game_state, SDL_Window *window, SDL_Renderer* renderer, SDL_Event event);

// Retorna se o personagem e se algum obstaculo colidiu.
bool are_colliding(Game_state* game_state);

// Destroi todas as texturar e libera a memoria.
void destroy_textures(Game_state* game_state);


