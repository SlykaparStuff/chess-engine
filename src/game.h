#include "pawn.h"

typedef struct
{
  int width, height;
  bool running;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  Pawn* pawns[16];
} Game;

// Initializes the game struct using the parsed in values
void game_init(Game* game, SDL_Window* window, SDL_Renderer* renderer, int width, int height);
// Starts the mainloop
void game_mainloop(Game* game);
