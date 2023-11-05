#include "pawn.h"

void pawn_init(SDL_Renderer* renderer, Pawn* pawns[], int count)
{
  for(int i = 0; i < count; i++)
  {
    pawns[i]->isBlack = i >= (count / 2);
    pawns[i]->img = pawns[i]->isBlack ? 
      IMG_LoadTexture(renderer, "assets/pawn/black.png")
      : IMG_LoadTexture(renderer, "assets/pawn/white.png");

    if(pawns[i]->isBlack)
    {
      pawns[i]->y = 1;
      pawns[i]->x = i - 8;
    } else 
    {
      pawns[i]->y = 6;
      pawns[i]->x = i;
    }
  }
}
