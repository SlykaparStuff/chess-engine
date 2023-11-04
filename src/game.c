#include "game.h"

#define BOARD_SQUARE_WIDTH (game->width / 8)
#define BOARD_SQUARE_HEIGHT (game->height / 8)

void update(Game* game);
void render(Game* game);
void cleanup(Game* game);

void game_init(Game* game, SDL_Window* window, SDL_Renderer* renderer, int width, int height)
{
  game->width = width;
  game->height = height;
  game->running = true;
  game->window = window;
  game->renderer = renderer;
}

void game_mainloop(Game* game)
{
  while(game->running)
  {
    update(game);
    render(game);
  }
}

void update(Game* game)
{
  while(SDL_PollEvent(&game->event))
  {
    if(game->event.type == SDL_QUIT)
    {
      cleanup(game);
      game->running = false;
    }
  }
}

void render(Game* game)
{
  SDL_RenderClear(game->renderer);

  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      SDL_Rect rect = (SDL_Rect){ x * BOARD_SQUARE_WIDTH, y * BOARD_SQUARE_HEIGHT, BOARD_SQUARE_WIDTH, BOARD_SQUARE_HEIGHT };
      if(x % 2 - y % 2 != 0)
      {
        SDL_SetRenderDrawColor(game->renderer, 181, 136, 99, 255);
      } else 
      {
        SDL_SetRenderDrawColor(game->renderer, 240, 217, 181, 255);
      }

      SDL_RenderFillRect(game->renderer, &rect);
    }
  }

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderPresent(game->renderer);
}

void cleanup(Game* game)
{
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
}
