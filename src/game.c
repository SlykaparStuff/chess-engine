#include "game.h"

#define BOARD_SQUARE_WIDTH (game->width / 8)
#define BOARD_SQUARE_HEIGHT (game->height / 8)

enum img_index{
  img_white_pawn,
  img_white_rook,
  img_white_knight,
  img_white_bishop,
  img_white_queen,
  img_white_king,
  img_black_pawn,
  img_black_rook,
  img_black_knight,
  img_black_bishop,
  img_black_queen,
  img_black_king
};

void update(Game* game);
void render(Game* game);
void render_pieces(Game* game);
void init_textures(Game* game);
u64 set_bit(Game* game, u64 number, int x, int y, bool set, bool white);
u64 move_piece(Game* game, u64 number, int xFrom, int yFrom, int xTo, int yTo, bool white);
bool checkValidMove(Game* game, int x, int y);
void capturePiece(Game* game, int x, int y, bool white);

void game_init(Game* game, SDL_Window* window, SDL_Renderer* renderer, int width, int height)
{
  // Sets all game variables
  game->width = width;
  game->height = height;
  game->running = true;
  game->window = window;
  game->renderer = renderer;
  game->piecePressed = false;
  game->pieceX = 0;
  game->pieceY = 0;
  game->pieceType = 0;
  game->moveTurn = true;
  // init textures
  init_textures(game);
  board_init(game->board);
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
    game->board->bb_piece[bb_piece_white] = 0;
    game->board->bb_piece[bb_piece_black] = 0;
    game->board->bb_occupied = 0;  
    game->board->bb_empty = 0;
    
     for(int i = 2; i <= 7; i++)
    {
      game->board->bb_piece[bb_piece_white] = game->board->bb_piece[bb_piece_white] | game->board->bb_piece[i];
    }
    for(int i = 8; i <= 13; i++)
    {
      game->board->bb_piece[bb_piece_black] = game->board->bb_piece[bb_piece_black] | game->board->bb_piece[i];
    }

    game->board->bb_occupied = game->board->bb_piece[bb_piece_white] | game->board->bb_piece[bb_piece_black];
    game->board->bb_empty = ~game->board->bb_occupied;

    // Checks for User closing window
    if(game->event.type == SDL_QUIT)
    {
      game->running = false;
      return;
    } else if(game->event.type == SDL_MOUSEBUTTONDOWN)
    {
      int x = game->event.motion.x / BOARD_SQUARE_WIDTH;
      int y = game->event.motion.y / BOARD_SQUARE_HEIGHT;
      //printf("Mouse pressed on x:%d | y:%d\n", x, y);

      if(game->piecePressed)
      {
        if(checkValidMove(game, x, y))
        {
          game->board->bb_piece[game->pieceType] = move_piece(game, game->board->bb_piece[game->pieceType],
                                                              game->pieceX, game->pieceY, x, y, game->pieceType < 7);

          if(game->pieceType < 7 && ((1ULL << (y * 8 + x)) & game->board->bb_piece[bb_piece_black]))
          {
            capturePiece(game, x, y, false);
          } else if(game->pieceType > 7 && ((1ULL << (y * 8 + x)) & game->board->bb_piece[bb_piece_white]))
          {
            capturePiece(game, x, y, true);
          }
          game->moveTurn = !game->moveTurn;
        }
        game->piecePressed = false;
        game->pieceType = 0;
      } else 
      {
        u64 mask = (1ULL << (y * 8 + x));
        if(game->board->bb_occupied & mask)
        {
          for(int i = 2; i <= 13; i++)
          {
            if(game->board->bb_piece[i] & mask)
            {
              game->pieceType = i;
            }
          }

          if(game->pieceType <= 7 == game->moveTurn) {
            game->piecePressed = true;
            game->pieceX = x;
            game->pieceY = y;
          } else 
          {
            game->pieceType = 0;
            game->piecePressed = false;
            game->pieceX = 0;
            game->pieceY = 0;
          }
        }
      }
    }
  }
}

void render(Game* game)
{
  SDL_RenderClear(game->renderer);

  // Draws chess board
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
  
  if(game->piecePressed)
  {
    SDL_Rect rect = (SDL_Rect){ game->pieceX * BOARD_SQUARE_WIDTH, game->pieceY * BOARD_SQUARE_HEIGHT,
      BOARD_SQUARE_WIDTH, BOARD_SQUARE_HEIGHT };
    if(game->pieceX % 2 - game->pieceY % 2 != 0)
    {
      SDL_SetRenderDrawColor(game->renderer, 100, 111, 64, 255);
    } else 
    {
      SDL_SetRenderDrawColor(game->renderer, 130, 151, 105, 255);
    }
    
    SDL_RenderFillRect(game->renderer, &rect);
  }

  render_pieces(game);

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderPresent(game->renderer);
}

void render_pieces(Game* game)
{
    for (int rank = 0; rank < 8; rank++) {
      for (int file = 0; file < 8; file++) {
        int square = rank * 8 + file;
        uint64_t mask = 1ULL << square;
        SDL_Rect rect = (SDL_Rect){ file * BOARD_SQUARE_WIDTH, rank * BOARD_SQUARE_HEIGHT,
          BOARD_SQUARE_WIDTH, BOARD_SQUARE_HEIGHT };
        
        if (game->board->bb_piece[bb_piece_white_pawn] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_pawn], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_rook] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_rook], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_knight] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_knight], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_bishop] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_bishop], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_queen] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_queen], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_king] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_king], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_pawn] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_pawn], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_rook] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_rook], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_knight] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_knight], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_bishop] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_bishop], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_queen] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_queen], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_king] & mask) 
        {
         SDL_RenderCopy(game->renderer, game->img[img_black_king], NULL, &rect);
        } 
      }
    }
}

void init_textures(Game* game)
{
  game->img[img_white_pawn] = IMG_LoadTexture(game->renderer, "assets/pawn/white.png");
  game->img[img_white_rook] = IMG_LoadTexture(game->renderer, "assets/rook/white.png");
  game->img[img_white_knight] = IMG_LoadTexture(game->renderer, "assets/knight/white.png");
  game->img[img_white_bishop] = IMG_LoadTexture(game->renderer, "assets/bishop/white.png");
  game->img[img_white_queen] = IMG_LoadTexture(game->renderer, "assets/queen/white.png");
  game->img[img_white_king] = IMG_LoadTexture(game->renderer, "assets/king/white.png");
  game->img[img_black_pawn] = IMG_LoadTexture(game->renderer, "assets/pawn/black.png");
  game->img[img_black_rook] = IMG_LoadTexture(game->renderer, "assets/rook/black.png");
  game->img[img_black_knight] = IMG_LoadTexture(game->renderer, "assets/knight/black.png");
  game->img[img_black_bishop] = IMG_LoadTexture(game->renderer, "assets/bishop/black.png");
  game->img[img_black_queen] = IMG_LoadTexture(game->renderer, "assets/queen/black.png");
  game->img[img_black_king] = IMG_LoadTexture(game->renderer, "assets/king/black.png");
}

u64 set_bit(Game* game, u64 number, int x, int y, bool set, bool white) {
  if(set) 
  {
    if(white)
    {
      game->board->bb_piece[bb_piece_white] = game->board->bb_piece[bb_piece_white] | (1ULL << (y * 8 + x));
    } else {
      game->board->bb_piece[bb_piece_black] = game->board->bb_piece[bb_piece_black] | (1ULL << (y * 8 + x));
    }
    game->board->bb_occupied = game->board->bb_piece[bb_piece_white] | game->board->bb_piece[bb_piece_black];
    // Set the bit to 1
    return number | (1ULL << (y * 8 + x));
  } else {
    if(white)
    {
      game->board->bb_piece[bb_piece_white] = game->board->bb_piece[bb_piece_white] & ~(1ULL << (y * 8 + x));
    } else {
      game->board->bb_piece[bb_piece_black] = game->board->bb_piece[bb_piece_black] & ~(1ULL << (y * 8 + x));
    }
    game->board->bb_occupied = game->board->bb_piece[bb_piece_white] | game->board->bb_piece[bb_piece_black];
    // Set the bit to 0
    return number & ~(1ULL << (y * 8 + x));
  }
}

u64 move_piece(Game* game, u64 number, int xFrom, int yFrom, int xTo, int yTo, bool white)
{
  u64 ret = set_bit(game, number, xFrom, yFrom, 0, white);
  return set_bit(game, ret, xTo, yTo, 1, white);
}

bool checkValidMove(Game* game, int x, int y)
{
  if(game->pieceType == bb_piece_white_pawn)
  {
    if(game->board->bb_occupied & (1ULL << (y * 8 + x)) && x == game->pieceX)
      return false;

    if(game->pieceY == 6 && x == game->pieceX && y == game->pieceY - 2)
    {
      return true;
    } else if(x == game->pieceX && y == game->pieceY - 1)
    {
      return true;
    } else if((x == game->pieceX - 1 || x == game->pieceX + 1) && y == game->pieceY - 1 
              && (game->board->bb_piece[bb_piece_black] & (1ULL << (y * 8 + x))))
    {
      return true;
    }
  } else if(game->pieceType == bb_piece_black_pawn)
  {
    if(game->board->bb_occupied & (1ULL << (y * 8 + x)) && x == game->pieceX)
      return false;

    if(game->pieceY == 1 && x == game->pieceX && y == game->pieceY + 2)
    {
      return true;
    } else if(x == game->pieceX && y == game->pieceY + 1)
    {
      return true;
    } else if((x == game->pieceX - 1 || x == game->pieceX + 1) && y == game->pieceY + 1 
              && (game->board->bb_piece[bb_piece_white] & (1ULL << (y * 8 + x))))
    {
      return true;
    }
  }

  
  else if(game->pieceType == bb_piece_white_knight && !(game->board->bb_piece[bb_piece_white] & (1ULL << (y * 8 + x))))
  {
    if(x == game->pieceX - 1 && y == game->pieceY - 2)
    {
      return true;
    } else if(x == game->pieceX + 1 && y == game->pieceY - 2)
    {
      return true;
    } else if(x == game->pieceX - 1 && y == game->pieceY + 2)
    {
      return true;
    } else if(x == game->pieceX + 1 && y == game->pieceY + 2)
    {
      return true;
    } else if(x == game->pieceX - 2 && y == game->pieceY - 1)
    {
      return true;
    } else if(x == game->pieceX + 2 && y == game->pieceY - 1)
    {
      return true;
    } else if(x == game->pieceX - 2 && y == game->pieceY + 1)
    {
      return true;
    } else if(x == game->pieceX + 2 && y == game->pieceY + 1)
    {
      return true;
    }
  }else if(game->pieceType == bb_piece_black_knight && !(game->board->bb_piece[bb_piece_black] & (1ULL << (y * 8 + x))))
  {
    if(x == game->pieceX - 1 && y == game->pieceY - 2)
    {
      return true;
    } else if(x == game->pieceX + 1 && y == game->pieceY - 2)
    {
      return true;
    } else if(x == game->pieceX - 1 && y == game->pieceY + 2)
    {
      return true;
    } else if(x == game->pieceX + 1 && y == game->pieceY + 2)
    {
      return true;
    } else if(x == game->pieceX - 2 && y == game->pieceY - 1)
    {
      return true;
    } else if(x == game->pieceX + 2 && y == game->pieceY - 1)
    {
      return true;
    } else if(x == game->pieceX - 2 && y == game->pieceY + 1)
    {
      return true;
    } else if(x == game->pieceX + 2 && y == game->pieceY + 1)
    {
      return true;
    }
  } 

  
  else if(game->pieceType == bb_piece_white_rook && !(game->board->bb_piece[bb_piece_white] & (1ULL << (y * 8 + x))))
  {
    if(x == game->pieceX || y == game->pieceY)
    {
      return true;
    }
  }else if(game->pieceType == bb_piece_black_rook && !(game->board->bb_piece[bb_piece_black] & (1ULL << (y * 8 + x))))
  {
    if(x == game->pieceX || y == game->pieceY)
    {
      return true;
    }
  }


  else if(game->pieceType == bb_piece_white_bishop && !(game->board->bb_piece[bb_piece_white] & (1ULL << (y * 8 + x))))
  {
    int max;
    for(int i = 0; i < 8; i++)
    {
      if(x == game->pieceX + i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX + i && y == game->pieceY - i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY - i)
      {
        return true;
      }
    }
  }else if(game->pieceType == bb_piece_black_bishop && !(game->board->bb_piece[bb_piece_black] & (1ULL << (y * 8 + x))))
  {
    int max;
    for(int i = 0; i < 8; i++)
    {
      if(x == game->pieceX + i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX + i && y == game->pieceY - i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY - i)
      {
        return true;
      }
    }
  }


  else if(game->pieceType == bb_piece_white_king && !(game->board->bb_piece[bb_piece_white] & (1ULL << (y * 8 + x))))
  {
    if(x == game->pieceX + 1 && y == game->pieceY + 1)
    {
      return true;
    } else if(x == game->pieceX - 1 && y == game->pieceY + 1)
    {
      return true;
    } else if(x == game->pieceX + 1 && y == game->pieceY - 1)
    {
      return true;
    } else if(x == game->pieceX - 1 && y == game->pieceY - 1)
    {
      return true;
    } else if((x + 1 == game->pieceX || x - 1 == game->pieceX) && y == game->pieceY)
    {
      return true;
    } else if((y + 1 == game->pieceY || y - 1 == game->pieceY) && x == game->pieceX)
    {
      return true;
    }
  }else if(game->pieceType == bb_piece_black_king && !(game->board->bb_piece[bb_piece_black] & (1ULL << (y * 8 + x))))
  {
    if(x == game->pieceX + 1 && y == game->pieceY + 1)
    {
      return true;
    } else if(x == game->pieceX - 1 && y == game->pieceY + 1)
    {
      return true;
    } else if(x == game->pieceX + 1 && y == game->pieceY - 1)
    {
      return true;
    } else if(x == game->pieceX - 1 && y == game->pieceY - 1)
    {
      return true;
    } else if((x + 1 == game->pieceX || x - 1 == game->pieceX) && y == game->pieceY)
    {
      return true;
    } else if((y + 1 == game->pieceY || y - 1 == game->pieceY) && x == game->pieceX)
    {
      return true;
    }
  }


  else if(game->pieceType == bb_piece_white_queen && !(game->board->bb_piece[bb_piece_white] & (1ULL << (y * 8 + x))))
  {
    for(int i = 0; i < 8; i++)
    {
      if(x == game->pieceX + i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX + i && y == game->pieceY - i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY - i)
      {
        return true;
      } else if(y == game->pieceY)
      {
        return true;
      } else if(x == game->pieceX)
      {
        return true;
      }
    }
  }else if(game->pieceType == bb_piece_black_queen && !(game->board->bb_piece[bb_piece_black] & (1ULL << (y * 8 + x))))
  {
    for(int i = 0; i < 8; i++)
    {
      if(x == game->pieceX + i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY + i)
      {
        return true;
      } else if(x == game->pieceX + i && y == game->pieceY - i)
      {
        return true;
      } else if(x == game->pieceX - i && y == game->pieceY - i)
      {
        return true;
      } else if(y == game->pieceY)
      {
        return true;
      } else if(x == game->pieceX)
      {
        return true;
      }
    }
  }

  return false;
}

void capturePiece(Game* game, int x, int y, bool white)
{
  int capturePieceType;

  if(white)
  {
    for(int i = 2; i <= 7; i++)
    {
      if(game->board->bb_piece[i] & (1ULL << (y * 8 + x)))
      {
        capturePieceType = i;
      }
    }
  } else
  {
    for(int i = 8; i <= 13; i++)
    {
      if(game->board->bb_piece[i] & (1ULL << (y * 8 + x)))
      {
        capturePieceType = i;
      }
    }
  }

  if(!capturePieceType || capturePieceType > 13)
    return;

  game->board->bb_piece[capturePieceType] = set_bit(game, game->board->bb_piece[capturePieceType], x, y,
                                                    false, capturePieceType > 7);
}
