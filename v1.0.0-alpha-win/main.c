#include ".\SDL2\include\SDL2\SDL.h"
#include ".\SDL2\include\SDL2\SDL_image.h"
#include ".\SDL2\include\SDL2\SDL_mixer.h"
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 640
#define HEIGHT 480
#define GRAVITY 0.25

typedef struct {
  int x, y;
  int height, width;
  SDL_Texture* player_texture1;
  SDL_Texture* player_texture2;
  SDL_Texture* player_texture3;
  bool step;
  bool pulando;
  double velocity;
} Player;

typedef struct {
  int x, y;
  int height, width;
  SDL_Texture* cactus_texture;
} Cactus;

typedef struct {
  int x, y;
  int height, width;
  SDL_Texture* grass_texture;
} Grass;

typedef struct {
  int x, y;
  int height, width;
  SDL_Texture* map_texture;
} Map;

typedef struct {
  Player player;
  Cactus cactus;
  Grass grass;
  Map map;
} GameState;

int processEvents(SDL_Window* window, GameState* gameState, SDL_Renderer* renderer);
void doRender(SDL_Renderer* renderer, GameState* gameState);
bool areColliding(GameState gameState);
void processTextures(SDL_Renderer* renderer, SDL_Texture** texture, char* src);
void player_render(GameState* gameState, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{

  SDL_Init(SDL_INIT_VIDEO);
  Mix_Init(MIX_INIT_MP3);

  bool stop = false;

  SDL_Window* window = NULL;
  SDL_Renderer* render = NULL;
  SDL_Surface* player_texture_surface = NULL;
  SDL_Surface* map_img_surface = NULL;
  SDL_Surface* cactus_text_surface = NULL;

  GameState gameState;

  gameState.map.x = 0;
  gameState.map.y = 0;
  gameState.map.height = HEIGHT;
  gameState.map.width = WIDTH * 2;


  gameState.player.x = 25;
  gameState.player.y = 300;
  gameState.player.height = 64;
  gameState.player.width = 60;
  gameState.player.velocity = 0;
  gameState.player.step = false;

  gameState.grass.y = gameState.player.height + gameState.player.y;
  gameState.grass.x = 0;
  gameState.grass.height = 150;
  gameState.grass.width = WIDTH * 2;


  gameState.cactus.x = WIDTH;
  gameState.cactus.y = 300;
  gameState.cactus.width = 54;
  gameState.cactus.height = 64;

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

  Mix_Music* main_song = Mix_LoadMUS("./audios/Minecraft - 128.mp3");
  Mix_Chunk* death_sound = Mix_LoadWAV("./audios/villager_damage.mp3");

  Mix_PlayMusic(main_song, -1);

  window = SDL_CreateWindow("Jogo mais foda do mes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  processTextures(render, &gameState.player.player_texture1, "./images/t_rex1.png");
  processTextures(render, &gameState.player.player_texture2, "./images/t_rex2.png");
  processTextures(render, &gameState.player.player_texture3, "./images/t_rex3.png");
  processTextures(render, &gameState.grass.grass_texture, "./images/grass.png");
  processTextures(render, &gameState.map.map_texture, "./images/map_loop2.png");
  processTextures(render, &gameState.cactus.cactus_texture, "./images/cactus.png");


  while (!stop) {
    stop = processEvents(window, &gameState, render);
    doRender(render, &gameState);

    if (areColliding(gameState)) {
      printf("Relou\n");
      stop = true;
    }

    SDL_Delay(10);
  }

  Mix_PlayChannel(-1, death_sound, 0);
  SDL_Delay(1200);

  SDL_DestroyTexture(gameState.map.map_texture);
  SDL_DestroyTexture(gameState.player.player_texture1);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);

  SDL_Quit();
  return 0;
}

void processTextures(SDL_Renderer* renderer, SDL_Texture** texture, char* src)
{
  SDL_Surface* surface;

  surface = IMG_Load(src);
  if (surface == NULL) {
    printf("Imagem nao encontrada!");
    SDL_Quit();
    exit(1);
  }

  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

int processEvents(SDL_Window* window, GameState* gameState, SDL_Renderer* renderer)
{
  SDL_Event event;
  bool stop;

  // Gravidade
  if (gameState->player.y < 300) {
    gameState->player.velocity += GRAVITY;
    gameState->player.y += gameState->player.velocity;
    if (gameState->player.y > 300)
      gameState->player.y = 300;
  }

  if (gameState->player.y == 300)
    gameState->player.velocity = 0;

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
            if (gameState->player.y == 300) {
              for (int i = 0; gameState->player.y > 135; i++) {
                gameState->player.y -= 10;
                doRender(renderer, gameState);
                SDL_Delay(10);
              }
            }

            break;
        }
        break;
      case SDL_QUIT:
        stop = true;
        break;

    }
  }

  return stop;
}

void doRender(SDL_Renderer* renderer, GameState* gameState)
{

  if (gameState->cactus.x < -gameState->cactus.width)
    gameState->cactus.x = WIDTH;

  gameState->cactus.x -= 4;

  if (gameState->map.x < -gameState->map.width / 2)
    gameState->map.x = 0;

  gameState->map.x -= 4;

  if (gameState->grass.x < -gameState->grass.width / 2)
    gameState->grass.x = 0;

  gameState->grass.x -= 4;

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_Rect mapRect = { gameState->map.x, gameState->map.y, gameState->map.width, gameState->map.height };
  SDL_RenderCopy(renderer, gameState->map.map_texture, NULL, &mapRect);

  SDL_Rect grassRect = { gameState->grass.x, gameState->grass.y, gameState->grass.width, gameState->grass.height };
  SDL_RenderCopy(renderer, gameState->grass.grass_texture, NULL, &grassRect);

  SDL_Rect cactusRect = { gameState->cactus.x, gameState->cactus.y, gameState->cactus.width, gameState->cactus.height };
  SDL_RenderCopy(renderer, gameState->cactus.cactus_texture, NULL, &cactusRect);

  player_render(gameState, renderer);

  SDL_RenderPresent(renderer);
}

void player_render(GameState* gameState, SDL_Renderer* renderer)
{
  if (gameState->player.y == 300) {
    if (gameState->player.step) {
      SDL_Rect playerRect = { gameState->player.x, gameState->player.y, gameState->player.width, gameState->player.height };
      SDL_RenderCopy(renderer, gameState->player.player_texture1, NULL, &playerRect);
      gameState->player.step = false;
    } else {
      SDL_Rect playerRect = { gameState->player.x, gameState->player.y, gameState->player.width, gameState->player.height };
      SDL_RenderCopy(renderer, gameState->player.player_texture2, NULL, &playerRect);
      gameState->player.step = true;
    }
  } else {
    SDL_Rect playerRect = { gameState->player.x, gameState->player.y, gameState->player.width, gameState->player.height };
    SDL_RenderCopy(renderer, gameState->player.player_texture1, NULL, &playerRect);
  }
}

bool areColliding(GameState gameState)
{

  if (gameState.player.x + gameState.player.width / 2 < gameState.cactus.x - gameState.cactus.width / 2) return false;
  if (gameState.player.x - gameState.player.width / 2 > gameState.cactus.x + gameState.cactus.width / 2) return false;
  if (gameState.player.y + gameState.player.height / 2 < gameState.cactus.y - gameState.cactus.height / 2) return false;
  if (gameState.player.y - gameState.player.height / 2 > gameState.cactus.y + gameState.cactus.height / 2) return false;

  return true;
}