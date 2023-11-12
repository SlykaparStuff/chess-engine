#include "board.h"

void board_init(Board* board)
{
  board->bb_piece[bb_piece_white] = 0xFFFF00000000FFFF;
  board->bb_piece[bb_piece_black] = 0x000000000000FFFF;
  board->bb_piece[bb_piece_white_pawn] = 0x00FF000000000000; // Initial position of the white pawns
  board->bb_piece[bb_piece_black_pawn] = 0x000000000000FF00; // Initial position of the black pawns
  
  board->bb_piece[bb_piece_white_rook] = 0x8100000000000000; // Initial position of the white rooks
  board->bb_piece[bb_piece_black_rook] = 0x0000000000000081; // Initial position of the black rooks

  board->bb_piece[bb_piece_white_knight] = 0x4200000000000000; // Initial position of the white knights
  board->bb_piece[bb_piece_black_knight] = 0x0000000000000042; // Initial position of the black knights

  board->bb_piece[bb_piece_white_bishop] = 0x2400000000000000; // Initial position of the white bishops
  board->bb_piece[bb_piece_black_bishop] = 0x0000000000000024; // Initial position of the black bishops

  board->bb_piece[bb_piece_white_queen] = 0x0800000000000000; // Initial position of the white queen
  board->bb_piece[bb_piece_black_queen] = 0x0000000000000008; // Initial position of the black queen

  board->bb_piece[bb_piece_white_king] = 0x1000000000000000; // Initial position of the white king
  board->bb_piece[bb_piece_black_king] = 0x0000000000000010; // Initial position of the black king
}
