#include "../include/game_state.h"

struct game_state_type {
  Map map;
  Ground ground;
  Queue obstacles_queue;
  Obstacle obstacle;
  Character character;
  Count count;
  double delay;
};

void game_jumping(Game_state game_state, SDL_Renderer* renderer, SDL_Window* window);

bool game_state_init(Game_state* game_state, int delay)
{

  (*game_state) = malloc(sizeof(struct game_state_type));

  if ((*game_state) != NULL) {
    map_init(&(*game_state)->map, 0, 0, WIDTH * 2, HEIGHT);
    ground_init(&(*game_state)->ground, 0, 364, 150, WIDTH * 2);
    character_init(&(*game_state)->character, 25, 300, 64, 60);
    count_init(&(*game_state)->count);

    queue_init(&(*game_state)->obstacles_queue);

    obstacle_init(&(*game_state)->obstacle, WIDTH, 300, 54, 64);
    queue_enqueue((*game_state)->obstacles_queue, (*game_state)->obstacle);

    obstacle_init(&(*game_state)->obstacle, WIDTH, 300, 54, 64);
    queue_enqueue((*game_state)->obstacles_queue, (*game_state)->obstacle);

    obstacle_init(&(*game_state)->obstacle, WIDTH, 300, 54, 64);
    queue_enqueue((*game_state)->obstacles_queue, (*game_state)->obstacle);

    (*game_state)->delay = delay;

    return true;
  }

  return false;
}

void game_load_textures(Game_state game_state, SDL_Renderer* renderer)
{
  Queue queue_aux;
  queue_init(&queue_aux);

  set_map_textures((game_state->map), renderer, "images/map_loop2.png");
  set_ground_texture((game_state->ground), renderer, "images/grass.png");
  set_character_textures((game_state->character), renderer, "images/t_rex1.png", "images/t_rex2.png", "images/t_rex3.png");
  set_count_texture(game_state->count, renderer, "fonts/VCR_OSD_MONO_1.001.ttf");

  while (!queue_is_empty(game_state->obstacles_queue)) {
    game_state->obstacle = queue_dequeue(game_state->obstacles_queue);
    set_obstacle_textures((game_state->obstacle), renderer, "images/cactus.png");

    queue_enqueue(queue_aux, game_state->obstacle);
  }

  while (!queue_is_empty(queue_aux)) {
    game_state->obstacle = queue_dequeue(queue_aux);
    queue_enqueue(game_state->obstacles_queue, game_state->obstacle);
  }
}

void game_menu(Game_state game_state, SDL_Renderer* renderer, SDL_Window* window, bool* quit)
{
  SDL_Event event;
  bool stop = false;
  int width, height;

  SDL_GL_GetDrawableSize(window, &width, &height);

  TTF_Font* font = TTF_OpenFont("fonts/VCR_OSD_MONO_1.001.ttf", 128);
  if (font == NULL)
    printf("Fonte nao encontrada!\n");

  SDL_Color White = { 255, 255, 255 };
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Aperte 'Espaco' para iniciar!", White);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

  SDL_Rect Message_rect = { width / 2 - (width - (width * 0.25)) / 2, height / 2 - 20, width - (width * 0.25), 40 };
  SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

  SDL_RenderPresent(renderer);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);

  TTF_CloseFont(font);

  while (!stop && !*quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_WINDOWEVENT_CLOSE:
          if (window) {
            SDL_DestroyWindow(window);
            window = NULL;
            *quit = true;
          }
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              *quit = true;
              break;
            case SDLK_UP:
              stop = true;
              break;
            case SDLK_SPACE:
              stop = true;
              break;
          }
          break;
        case SDL_QUIT:
          *quit = true;
          break;
      }
    }
  }
}

void move_everything(Game_state game_state, SDL_Window* window)
{
  move_map((game_state->map));
  move_ground((game_state->ground));
  gravity((game_state->character));
  move_obstacle((game_state->obstacle), window);

  if (has_passed(game_state->obstacle)) {
    set_passed(game_state->obstacle);
    queue_enqueue(game_state->obstacles_queue, game_state->obstacle);
    game_state->obstacle = queue_dequeue(game_state->obstacles_queue);
  }
}

void game_render(Game_state game_state, SDL_Renderer* renderer, SDL_Window* window)
{

  SDL_RenderClear(renderer);

  render_map(((game_state)->map), renderer, window);
  render_ground(((game_state)->ground), renderer, window);
  render_character_step(((game_state)->character), renderer, window);
  render_obstacle(game_state->obstacle, renderer, window);
  render_count(game_state->count, renderer);

  // if (get_count(game_state->count) % 100 == 0) {
  //   game_state->delay -= 0.2;
  // }


  SDL_RenderPresent(renderer);

  SDL_Delay(game_state->delay);
}

bool process_events(Game_state game_state, SDL_Window* window, SDL_Renderer* renderer)
{
  bool stop = false;
  SDL_Event event;
  int width, height;

  SDL_GL_GetDrawableSize(window, &width, &height);


  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_WINDOWEVENT_CLOSE:
        if (window) {
          SDL_DestroyWindow(window);
          window = NULL;
          stop = true;
        }
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            stop = true;
            break;
          case SDLK_UP:
            game_jumping(game_state, renderer, window);
          case SDLK_SPACE:
            game_jumping(game_state, renderer, window);
            break;
          case SDLK_DOWN:
            if (!can_jump(game_state->character)) {
              for (int i = 0; i < (height / 80); i++) {
                gravity((game_state->character));
              }
            }
            break;
          case SDL_QUIT:
            stop = true;
            break;
        }
    }
  }

  return stop;
}

void game_jumping(Game_state game_state, SDL_Renderer* renderer, SDL_Window* window)
{
  int width, height;

  SDL_GL_GetDrawableSize(window, &width, &height);

  if (can_jump(game_state->character)) {
    for (int i = 0; i < (height / 24); i++) {
      jump((game_state->character), height);
      move_everything(game_state, window);
      game_render(game_state, renderer, window);
    }
  }
}

bool are_colliding(Game_state game_state)
{
  double c_x1, c_x2, c_y1, c_y2;
  double o_x1, o_x2, o_y1, o_y2;

  get_character_colision((game_state->character), &c_x1, &c_x2, &c_y1, &c_y2);
  get_obstacle_colision((game_state->obstacle), &o_x1, &o_x2, &o_y1, &o_y2);

  if (c_x1 < o_x2)
    return false;
  if (c_x2 > o_x1)
    return false;
  if (c_y1 < o_y2)
    return false;
  if (c_y2 > o_y1)
    return false;

  return true;
}

void destroy_textures(Game_state game_state)
{
  destroy_map_texture((game_state->map));
  destroy_ground_texture((game_state->ground));
  destroy_character_texture((game_state->character));
  destroy_obstacle_texture((game_state->obstacle));

  while (!queue_is_empty(game_state->obstacles_queue)) {
    game_state->obstacle = queue_dequeue(game_state->obstacles_queue);
    destroy_obstacle_texture((game_state->obstacle));
  }

}
