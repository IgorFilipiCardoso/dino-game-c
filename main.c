#include ".\src\include\SDL2\SDL.h"
#include ".\src\include\SDL2\SDL_image.h"
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 640 
#define HEIGHT 480

typedef struct {
  int x, y;
  SDL_Texture* player_texture;
} Player;

typedef struct {
  SDL_Texture* map_texture;
  int x, y;
} Map;

typedef struct {
  Player player;
  Map map;
} GameState;

int processEvents(SDL_Window* window, GameState* gameState);
void doRender(SDL_Renderer* renderer, GameState* gameState);

int main(int argc, char* argv[])
{
  bool stop = false;

  SDL_Window* window = NULL;
  SDL_Renderer* render = NULL;
  SDL_Surface* player_texture_surface = NULL;
  SDL_Surface* map_img_surface = NULL;

  GameState gameState;

  gameState.map.x = 0;
  gameState.map.y = 0;

  gameState.player.x = 220;
  gameState.player.y = 140;

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Jogo mais foda do mes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  player_texture_surface = IMG_Load("./images/t_rex.png");
  if (player_texture_surface == NULL) {
    printf("Imagem do 'player' nao encontrada!");
    SDL_Quit();
    return 1;
  }

  map_img_surface = IMG_Load("./images/map.png");
  if (map_img_surface == NULL)
  {
    printf("Imagem do 'mapa' nao encontrada!");
    SDL_Quit();
    return 1;
  }

  gameState.map.map_texture = SDL_CreateTextureFromSurface( render, map_img_surface);
  gameState.player.player_texture = SDL_CreateTextureFromSurface( render, player_texture_surface);

  SDL_FreeSurface(map_img_surface);
  SDL_FreeSurface(player_texture_surface);

  while (!stop) {
    stop = processEvents(window, &gameState);
    doRender(render, &gameState);

    SDL_Delay(10);
  }

  SDL_DestroyTexture(gameState.map.map_texture);
  SDL_DestroyTexture(gameState.player.player_texture);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);

  SDL_Quit();
  return 0;
}


int processEvents(SDL_Window* window, GameState* gameState)
{
  SDL_Event event;
  bool stop;

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
        }
        break;
      case SDL_QUIT:
        stop = true;
        break;
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
      gameState->player.x -= 10;
    if (state[SDL_SCANCODE_RIGHT])
      gameState->player.x += 10;
    if (state[SDL_SCANCODE_UP])
      gameState->player.y -= 10;
    if (state[SDL_SCANCODE_DOWN])
      gameState->player.y += 10;
  }
  
  if (gameState->map.x == -480)
      gameState->map.x = 0;
    
    gameState->map.x -= 3;

  return stop;
}

void doRender(SDL_Renderer* renderer, GameState* gameState)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_Rect mapRect = { gameState->map.x, gameState->map.y, WIDTH*2, HEIGHT};
  SDL_RenderCopy(renderer, gameState->map.map_texture, NULL, &mapRect);

  SDL_Rect playerRect = {gameState->player.x, gameState->player.y, 64, 64};
  SDL_RenderCopy(renderer, gameState->player.player_texture, NULL, &playerRect);

  SDL_RenderPresent(renderer);
}