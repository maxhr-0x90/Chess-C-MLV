#include "assets.h"

int(main)(){
  int i, j, yes;
  Piece *board[8][8];
  Piece set_piece[32];
  Coord xy;

  MLV_create_window("jeu", "jeu", CASE*8, CASE*8);
  init_plateau(board, set_piece);

  actualise_plateau(board);
  yes = 0;
  while(yes != 1){
    xy = clic();
    yes = est_piece(board, xy);
    printf("%d\n", yes);
  }
  MLV_wait_seconds(100);
  exit(0);
}
