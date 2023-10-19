#include "../lib/map.h"

struct map_type
{
    int x, y;
    int height, width;
    SDL_Texture *texture;
};

bool map_init(Map *map, int position_x, int position_y, int width, int height)
{
    (*map) = malloc(sizeof(Map));

    if ((*map) != NULL)
    {
        (*map)->height = height;
        (*map)->width = width;
        (*map)->x = position_x;
        (*map)->y = position_y;

        return true;
    }

    return false;
}

void set_map_textures(Map *map, SDL_Renderer *renderer, char *src)
{
    SDL_Surface *surface;

    surface = IMG_Load(src);

    if (surface == NULL)
    {
        printf("Imagem no caminho '%s' nao foi encontrada!", src);
        SDL_Quit();
    }

    (*map)->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

}

void move_map(Map *map)
{
    if ((*map)->x < -(*map)->width / 2)
    (*map)->x = 0;

    (*map)->x -= VELOCITY;
}

void render_map(Map map, SDL_Renderer* renderer)
{
    SDL_Rect mapRect = {map->x, map->y, map->width, map->height};
    SDL_RenderCopy(renderer, map->texture, NULL, &mapRect);
}

void destroy_map_texture(Map* map){
    SDL_DestroyTexture((*map)->texture);
}