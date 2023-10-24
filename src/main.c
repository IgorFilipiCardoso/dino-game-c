#include "./include/game_state.h"

int main(int argc, char* argv[])
{
  Game_state the_game;
  bool stop = false;

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  window = SDL_CreateWindow("Jogo mais foda do mes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);


  game_state_init(&the_game, 25);
  game_load_textures(the_game, renderer);
  game_render(the_game, renderer, window);

  game_menu(the_game, renderer, window, &stop);

  while (!stop) {

    stop = process_events(the_game, window, renderer);
    move_everything(the_game, window);
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
