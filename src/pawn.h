#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
  int x, y;
  SDL_Texture* img;
  bool isBlack;
} Pawn;

void pawn_init(SDL_Renderer* renderer, Pawn* pawns[], int count);
