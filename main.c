#include "assets.h"

int(main)(){
  int i, j;
  Piece *board[8][8];
  Piece set_piece[32];

  MLV_create_window("jeu", "jeu", 800, 800);
  init_plateau(board, set_piece);
  actualise_plateau(board);
  MLV_wait_seconds(100);
  exit(0);
}
