#include "../lib/obstacle.h"

struct obstacle_type
{
  int x, y;
  int height, width;
  SDL_Texture *texture;
};

bool obstacle_init(Obstacle *obstacle, int position_x, int position_y, int width, int height)
{

  (*obstacle) = malloc(sizeof(Obstacle));

  if ((*obstacle) != NULL)
  {
    (*obstacle)->x = position_x;
    (*obstacle)->y = position_y;
    (*obstacle)->height = height;
    (*obstacle)->width = width;

    return true;
  }

  return false;
}

void render_obstacle(SDL_Renderer *renderer, Obstacle *obstacle)
{
  SDL_Rect obstacleRect = {(*obstacle)->x, (*obstacle)->y, (*obstacle)->width, (*obstacle)->height};
  SDL_RenderCopy(renderer, (*obstacle)->texture, NULL, &obstacleRect);
}

void move_obstacle(Obstacle* obstacle)
{
  if ((*obstacle)->x < -(*obstacle)->width)
    (*obstacle)->x = WIDTH;

  (*obstacle)->x -= VELOCITY;
}

void set_obstacle_textures(Obstacle *obstacle, SDL_Renderer *renderer, char* src)
{
  SDL_Surface *surface;

  surface = IMG_Load(src);
  if (surface == NULL)
  {
    printf("Imagem no caminha '%s' nao foi encontrada!", src);
    SDL_Quit();
  }

  (*obstacle)->texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void get_obstacle_colision(Obstacle obstacle, double *x1, double *x2, double *y1, double *y2)
{
  *x1 = obstacle->x + obstacle->width  / 2;
  *x2 = obstacle->x - obstacle->width  / 2;
  *y1 = obstacle->y + obstacle->height / 2;
  *y2 = obstacle->y - obstacle->height / 2;
}

void destroy_obstacle_texture(Obstacle* obstacle)
{
  SDL_DestroyTexture((*obstacle)->texture);
}