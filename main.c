#include "assets.h"

int(main)(){
  Piece *board[8][8];
  Piece set_piece[32];
  Coord pos, target;

  MLV_create_window("jeu", "jeu", CASE*8, CASE*8);
  init_plateau(board, set_piece);
  actualise_plateau(board);
  while(1){
    pos = clic();
    while(!(est_piece(board, pos)))
      pos = clic();

    target = clic();
    if(est_legal(board, pos, target)){
      board[target.y][target.x] = board[pos.y][pos.x];
      board[pos.y][pos.x] = NULL;
      actualise_plateau(board);
    }
    actualise_plateau(board);
  }

  MLV_wait_seconds(100);
  exit(0);
}
