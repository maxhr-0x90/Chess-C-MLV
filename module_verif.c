#include "assets.h"

int est_piece(Piece *board[][8], Coord pos){
  if(board[pos.y][pos.x] != NULL)
    return 1;
  else
    return 0;
}

int est_legal(Piece *board[][8], Coord pos, Coord target){

  if(board[target.y][target.x] == NULL || board[target.y][target.x]->couleur == (board[pos.y][pos.x]->couleur+1)%2){
    return 1;
  }
  else
    return 0;
}
