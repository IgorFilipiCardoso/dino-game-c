#include "../lib/character.h"

struct character_type
{
  int x, y;
  int height, width;
  SDL_Texture *character_texture1;
  SDL_Texture *character_texture2;
  SDL_Texture *character_texture3;
  bool step;
  double velocity;
};

bool init_character(Character *character, int position_x, int position_y, int width, int height)
{

  (*character) = malloc(sizeof(Character));

  if ((*character) != NULL)
  {
    (*character)->x = position_x;
    (*character)->y = position_y;
    (*character)->height = height;
    (*character)->width = width;
    (*character)->velocity = 0;
    (*character)->step = false;

    return true;
  }

  return false;
}

// Faz com que o persongem pule, retorna um bool, indicando se pulou ou nao.
bool jump(Character *character, SDL_Renderer *renderer)
{
  if ((*character)->y == 300)
  {
    for (int i = 0; (*character)->y > 135; i++)
    {
      (*character)->y -= 10;
      render_character_step(renderer, character);
      SDL_Delay(DELAY);
    }
  }
}
// Cria um especie de gravidade, onde o personagem e puxado para baixo.
void gravity(Character *character)
{
  (*character)->velocity += GRAVITY;
  (*character)->y += (*character)->velocity;
  if ((*character)->y > 300)
    (*character)->y = 300;
}

// Renderiza o personagem na tela
void render_character_step(SDL_Renderer *renderer, Character *character)
{
  if ((*character)->y == 300)
  {
    if ((*character)->step)
    {
      render_character(renderer, character, (*character)->character_texture1);
      (*character)->step = false;
    }
    else
    {
      render_character(renderer, character, (*character)->character_texture2);
      (*character)->step = true;
    }
  }
  else
  {
    render_character(renderer, character, (*character)->character_texture1);
  }
}

void render_character(SDL_Renderer *renderer, Character *character, SDL_Texture **texture)
{
  SDL_Rect characterRect = {(*character)->x, (*character)->y, (*character)->width, (*character)->height};
  SDL_RenderCopy(renderer, *texture, NULL, &characterRect);
}

// Processa uma textura para o personagem
void set_character_textures(Character *character, SDL_Renderer *renderer, char *src_texture1, char *src_texture2, char *src_texture3)
{
  set_one_texture((*character)->character_texture1, renderer, src_texture1);
  set_one_texture((*character)->character_texture2, renderer, src_texture2);
  set_one_texture((*character)->character_texture3, renderer, src_texture3);
}

void set_one_texture(SDL_Texture **texture, SDL_Renderer *renderer, char *src)
{
  SDL_Surface *surface;

  surface = IMG_Load(src);
  if (surface == NULL)
  {
    printf("Imagem nao encontrada!");
    SDL_Quit();
    exit(1);
  }

  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}