#include "assets.h"

int(main)(){
  Piece *board[8][8];
  Piece set_piece[32];
  Coord pos, target;
  int i, moves[8];
  for(i = 0; i<8; i++){
    moves[i] = 0;
  }

  MLV_create_window("jeu", "jeu", CASE*8, CASE*8);
  init_plateau(board, set_piece);
  actualise_plateau(board, pos, moves);
  while(1){
    pos = clic();
    while(!(est_piece(board, pos)))
      pos = clic();

    for(i = 0; i<8; i++){
      moves[i] = 0;
    }
    moves_possible(board, pos, moves);
    if(est_mortel(board, pos)){
      printf("est mortel\n");
    }
    else{
      printf("est pas mortel\n");
    }
    actualise_plateau(board, pos, moves);

    target = clic();
      while(est_piece(board, target) && board[target.y][target.x]->couleur == board[pos.y][pos.x]->couleur){
        target = clic();
      }
    board[target.y][target.x] = board[pos.y][pos.x];
    board[pos.y][pos.x] = NULL;
    actualise_plateau(board, pos, moves);
  }

  MLV_wait_seconds(100);
  exit(0);
}
