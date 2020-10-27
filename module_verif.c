#include "assets.h"

int est_piece(Piece *board[][8], Coord pos){
  if(board[pos.y][pos.x] != NULL){
    return 1;
  }else{
    return 0;
  }
}

void legal_L(Piece *board[][8], Coord pos, Coord target, int* verif){
  if(pos.x == target.x-2 || pos.x == target.x+2){
    if(pos.y == target.y-1 || pos.y == target.y+1){
      *verif = 1;
    }
  }

  if(pos.x == target.x-1 || pos.x == target.x+1){
    if(pos.y == target.y-2 || pos.y == target.y+2){
      *verif = 1;
    }
  }
}

void legal_droit(Piece *board[][8], Coord pos, Coord target, int* verif){
  if(pos.x == target.x || pos.y == target.y){
    if(abs(pos.x-target.x) <= board[pos.y][pos.x]->move.limitation &&
       abs(pos.y-target.y) <= board[pos.y][pos.x]->move.limitation ){
         *verif = 1;
    }
  }
}

void legal_diag(Piece *board[][8], Coord pos, Coord target, int* verif){
  if(abs(pos.x-target.x) == abs(pos.y-target.y) && abs(pos.y-target.y) <= board[pos.y][pos.x]->move.limitation){
    *verif = 1;
  }
}

void legal_ajustement_f(Piece *board[][8], Coord pos, Coord target, int* verif){
  if(pos.x == target.x){
    if(board[pos.y][pos.x]->couleur == Blanc
       && pos.y - target.y <= board[pos.y][pos.x]->move.ajustement[0]
       && pos.y - target.y > 0
       && board[pos.y-1][pos.x] == NULL){
      board[pos.y][pos.x]->move.ajustement[0] = 1;
      *verif = 1;
    }
    if(board[pos.y][pos.x]->couleur == Noir
       && target.y - pos.y <= board[pos.y][pos.x]->move.ajustement[0]
       && target.y - pos.y > 0
       && board[pos.y+1][pos.x] == NULL){
      board[pos.y][pos.x]->move.ajustement[0] = 1;
        *verif = 1;
    }
  }
  if(pos.x == target.x - 1 || pos.x == target.x + 1){
    printf("ok\n");
    if(board[pos.y][pos.x]->couleur == Blanc
       && pos.y == target.y + 1
       && board[target.y][target.x] != NULL){
         *verif = 1;
    }
    if(board[pos.y][pos.x]->couleur == Noir
       && pos.y == target.y - 1
       && board[target.y][target.x] != NULL){
         *verif = 1;
    }
  }
}

int est_legal(Piece *board[][8], Coord pos, Coord target){
  int i, j, verif;
  verif = 0;

  if(board[target.y][target.x] == NULL ||
     board[target.y][target.x]->couleur != board[pos.y][pos.x]->couleur){

    if(board[pos.y][pos.x]->move.formeL.val){
      legal_L(board, pos, target, &verif);
    }

    if(board[pos.y][pos.x]->move.droit.val){
      legal_droit(board, pos, target, &verif);
    }

    if(board[pos.y][pos.x]->move.diagonal.val){
      legal_diag(board, pos, target, &verif);
    }

    if(board[pos.y][pos.x]->move.ajustement[1] = 'f'){
      legal_ajustement_f(board, pos, target, &verif);
    }
  }
 return verif;
}
