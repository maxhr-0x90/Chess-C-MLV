#include "assets.h"

int est_piece(Piece *board[][8], Coord pos){
  if(board[pos.y][pos.x] != NULL){
    return 1;
  }else{
    return 0;
  }
}

int est_legal(Piece *board[][8], Coord pos, Coord target){
  int i, j;

  if(board[target.y][target.x] == NULL ||
     board[target.y][target.x]->couleur == (board[pos.y][pos.x]->couleur+1)%2){

    if(board[pos.y][pos.x]->move.formeL.val){
      if(pos.x == target.x-2 || pos.x == target.x+2){
        if(pos.y == target.y-1 || pos.y == target.y+1){
          return 1;
        }
      }

      if(pos.x == target.x-1 || pos.x == target.x+1){
        if(pos.y == target.y-2 || pos.y == target.y+2){
          return 1;
        }
      }
    }

    if(board[pos.y][pos.x]->move.droit.val){
      if(pos.x == target.x || pos.y == target.y){
        if(abs(pos.x-target.x) <= board[pos.y][pos.x]->move.limitation &&
           abs(pos.y-target.y) <= board[pos.y][pos.x]->move.limitation ){
             return 1;
        }
      }
    }

    if(board[pos.y][pos.x]->move.diagonal.val){
      if(abs(pos.x-target.x) == abs(pos.y-target.y) && abs(pos.y-target.y) <= board[pos.y][pos.x]->move.limitation){
        return 1;
      }
    }

  if(board[pos.y][pos.x]->move.ajustement[1] = 'f'){
    if(pos.x == target.x){
      if(board[pos.y][pos.x]->couleur == Blanc
         && pos.y - target.y <= board[pos.y][pos.x]->move.ajustement[0]
         && board[pos.y-1][pos.x] == NULL){
        board[pos.y][pos.x]->move.ajustement[0] = 1;
        return 1;
      }
      if(board[pos.y][pos.x]->couleur == Noir
         && target.y - pos.y <= board[pos.y][pos.x]->move.ajustement[0]
         && board[pos.y+1][pos.x] == NULL){
        board[pos.y][pos.x]->move.ajustement[0] = 1;
        return 1;
        }
      }
    if(pos.x == target.x - 1 || pos.x == target.x + 1){
      printf("ok\n");
      if(board[pos.y][pos.x]->couleur == Blanc
         && pos.y == target.y + 1
         && board[target.y][target.x] != NULL){
           return 1;
        }
      if(board[pos.y][pos.x]->couleur == Noir
         && pos.y == target.y - 1
         && board[target.y][target.x] != NULL){
           return 1;
        }
      }
    }
  }
  return 0;
}
