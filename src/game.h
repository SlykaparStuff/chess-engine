#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
  int width, height;
  bool running;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
} Game;

void game_init(Game* game, SDL_Window* window, SDL_Renderer* renderer, int width, int height);
void game_mainloop(Game* game);
