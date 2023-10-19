#include "../lib/game_state.h"

struct game_state_type
{
    Map map;
    Ground ground;
    Obstacle obstacle_cactus;
    Character character;
    int delay;
};

bool game_state_init(Game_state *game_state, int delay)
{
    (*game_state) = malloc(sizeof(Game_state));

    map_init(&(*game_state)->map, 0, 0, WIDTH * 2, HEIGHT);
    ground_init(&(*game_state)->ground, 0, 364, 150, WIDTH * 2);
    obstacle_init(&(*game_state)->obstacle_cactus, WIDTH, 300, 54, 64);
    character_init(&(*game_state)->character, 25, 300, 64, 60);
    (*game_state)->delay = delay;
}

void game_load_textures(Game_state *game_state, SDL_Renderer *renderer)
{
    set_map_textures(&(*game_state)->map, renderer, "images/map_loop2.png");
    set_ground_texture(&(*game_state)->ground, renderer, "images/grass.png");
    set_obstacle_textures(&(*game_state)->obstacle_cactus, renderer, "images/cactus.png");
    set_character_textures(&(*game_state)->character, renderer, "images/t_rex1.png", "images/t_rex2.png", "images/t_rex3.png");
}

void move_everithing(Game_state *game_state)
{
    move_map(&(*game_state)->map);
    move_ground(&(*game_state)->ground);
    move_obstacle(&(*game_state)->obstacle_cactus);
    gravity(&(*game_state)->character);
}

void game_render(Game_state *game_state, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    render_map(((*game_state)->map), renderer);
    render_ground(renderer, ((*game_state)->ground));
    render_obstacle(renderer, &((*game_state)->obstacle_cactus));
    render_character_step(renderer, &((*game_state)->character));

    SDL_RenderPresent(renderer);

    SDL_Delay((*game_state)->delay);
}

bool process_events(Game_state *game_state, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Event event;
    bool stop = false;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                stop = true;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                stop = true;
                break;
            case SDLK_UP:
                for (int i = 0; i < 13; i++)
                {
                    jump(&(*game_state)->character, renderer);
                    move_everithing(game_state);
                    game_render(game_state, renderer);
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

bool are_colliding(Game_state *game_state)
{
    double c_x1, c_x2, c_y1, c_y2;
    double o_x1, o_x2, o_y1, o_y2;

    get_character_colision(((*game_state)->character), &c_x1, &c_x2, &c_y1, &c_y1);
    get_obstacle_colision(((*game_state)->obstacle_cactus), &o_x1, &o_x2, &o_y1, &o_y1);

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

void destroy_textures(Game_state *game_state)
{
    destroy_map_texture(&(*game_state)->map);
    destroy_ground_texture(&(*game_state)->ground);
    destroy_character_texture(&(*game_state)->character);
    destroy_obstacle_texture(&(*game_state)->obstacle_cactus);
}
