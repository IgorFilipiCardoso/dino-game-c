#include "../lib/ground.h"

struct ground_type
{
  int x, y;
  int height, width;
  SDL_Texture *texture;
};

bool ground_init(Ground *ground, int position_x, int position_y, int height, int width)
{
  (*ground) = malloc(sizeof(Ground));


  if ((*ground) != NULL)
  {
    printf("Banada do Chao ----\n");
    (*ground)->y = position_y;
    (*ground)->x = position_x;
    (*ground)->height = height;
    (*ground)->width = width;

    return true;
  }

  return false;
}

void move_ground(Ground *ground)
{
  if ((*ground)->x < -(*ground)->width / 2)
    (*ground)->x = 0;

  (*ground)->x -= VELOCITY;
}

void render_ground(SDL_Renderer *renderer, Ground* ground)
{
  SDL_Rect grassRect = {(*ground)->x, (*ground)->y, (*ground)->width, (*ground)->height};
  SDL_RenderCopy(renderer, (*ground)->texture, NULL, &grassRect);
}

void set_ground_texture(Ground *ground, SDL_Renderer *renderer, char *src)
{
  SDL_Surface *surface;

  surface = IMG_Load(src);
  if (surface == NULL)
  {
    printf("Imagem no caminha '%s' nao foi encontrada!", src);
    SDL_Quit();
  }

  (*ground)->texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void destroy_ground_texture(Ground* ground)
{
  SDL_DestroyTexture((*ground)->texture);
}