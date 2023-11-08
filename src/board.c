#include "board.h"

void board_init(Board* board)
{
  board->bb_piece[bb_piece_white] = 0xFFFF00000000FFFF;
  board->bb_piece[bb_piece_black] = 0x000000000000FFFF;
  board->bb_piece[bb_piece_white_pawn] = 0x00FF000000000000;
  board->bb_piece[bb_piece_black_pawn] = 0x000000000000FF00;
}
