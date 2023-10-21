#include "./lib/game_state.h"

int main(int argc, char* argv[])
{
  Game_state the_game;
  bool stop = false;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  window = SDL_CreateWindow("Jogo mais foda do mes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);


  game_state_init(&the_game, 15);
  game_load_textures(the_game, renderer);

  while (!stop) {
    
    stop = process_events(the_game, window, renderer);
    move_everithing(the_game, window);
    game_render(the_game, renderer, window);

    if (are_colliding(the_game))
      stop = true;
  } 

  destroy_textures(the_game);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();

  return 0;
}
