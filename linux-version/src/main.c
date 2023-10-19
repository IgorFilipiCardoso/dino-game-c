#include "./lib/game_state.h"

int main(int argc, char *argv[])
{
    Game_state the_game;
    bool stop;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    window = SDL_CreateWindow("Jogo mais foda do mes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    game_state_init(&the_game, 10);

    game_load_textures(&the_game, renderer);

    while (!stop)
    {
        game_render(&the_game, renderer);
        stop = process_events(&the_game, window, renderer);
        move_everithing(&the_game);
        if (are_colliding(&the_game))
        {
            stop = true;
        }

    
    }

    destroy_textures(&the_game);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}
