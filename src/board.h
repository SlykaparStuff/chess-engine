#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define WHITE 0
#define BLACK 1

enum enumSquare {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
};

// index in the bitboard array
enum enumPiece
{
  bb_piece_white,
  bb_piece_black,
  bb_piece_white_pawn,
  bb_piece_white_rook,
  bb_piece_white_knight,
  bb_piece_white_bishop,
  bb_piece_white_queen,
  bb_piece_white_king,
  bb_piece_black_pawn,
  bb_piece_black_rook,
  bb_piece_black_knight,
  bb_piece_black_bishop,
  bb_piece_black_queen,
  bb_piece_black_king
};

// bb = bitboard
typedef struct
{
  u64 bb_piece[14];
  u64 bb_empty;
  u64 bb_occupied;
} Board;
