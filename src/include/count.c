#include "../lib/count.h" 

struct count_type {
    SDL_Surface* text_surface;
    SDL_Texture* text_texture;
    SDL_Rect text_rect;
    SDL_Color white_color;
    TTF_Font* font;
    double counting;
};

void count_init(Count* count)
{
    (*count) = malloc(sizeof(struct count_type));

    (*count)->white_color.r = 255;
    (*count)->white_color.g = 255;
    (*count)->white_color.b = 255;
    (*count)->text_rect.x = 40;
    (*count)->text_rect.y = 40;
    (*count)->text_rect.w = 50;
    (*count)->text_rect.h = 30;
    (*count)->counting = 0;
}

void set_count_texture(Count count, SDL_Renderer* renderer, char* src)
{
    count->font = TTF_OpenFont(src, 24);
}

int get_count(Count count)
{
    return count->counting;
}

void render_count(Count count, SDL_Renderer* renderer)
{
    char counting_text[10];
    int counting_int = count->counting;
    snprintf(counting_text, 10, "%d", counting_int);

    count->text_surface = TTF_RenderText_Solid(count->font, counting_text, count->white_color);
    count->text_texture = SDL_CreateTextureFromSurface(renderer, count->text_surface);
    SDL_RenderCopy(renderer, count->text_texture, NULL, &count->text_rect);

    count->counting += 0.25;
}


void destroy_texture_count(Count count)
{
    SDL_DestroyTexture(count->text_texture);
    TTF_CloseFont(count->font);
}




