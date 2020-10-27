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
        *verif = 1;
    }
    if(board[pos.y][pos.x]->couleur == Noir
     && target.y - pos.y <= board[pos.y][pos.x]->move.ajustement[0]
     && target.y - pos.y > 0
     && board[pos.y+1][pos.x] == NULL){
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

    if(board[pos.y][pos.x]->move.ajustement[1] == 'p'){
      legal_ajustement_f(board, pos, target, &verif);
      if(verif == 1){
        board[pos.y][pos.x]->move.ajustement[0] = 1;
      }
    }
  }
 return verif;
}

int en_dehors(Coord pos){
  if (pos.x >= 0 && pos.x <= 7 && pos.y >= 0 && pos.y <= 7) {
    return 1;
  }
  return 0;
}

int sur_allie(Piece *board[][8], Coord pos, Coord target){
  if(board[target.y][target.x] == NULL
    || board[target.y][target.x]->couleur != board[pos.y][pos.x]->couleur){
    return 0;
  }
  return 1;
}

int depasse_piece(Piece *board[][8], Coord pos, Coord target, Coord deplace){
  if(!(pos.x == (target.x - deplace.x) && pos.y == (target.y - deplace.y)) &&
   board[target.x - deplace.x][target.y - deplace.y] != NULL){
    return 1;
  }
  return 0;
}

void moves_possible(Piece *board[][8], Coord pos, int *moves){
  int i, j, valide, swp;
  int pos_cava[] = {1, 2, 2, 1, -1, -2, -2, -1};
  Coord dec;
  Coord tmp;

  if(board[pos.y][pos.x]->move.formeL.val){
    for (i = 0; i < 8; i++) {
      tmp = {pos.x + pos_cava[i], pos.y + pos_cava[(i-2) % 8]}
      moves[i] = en_dehors(tmp) && sur_allie(board, pos, tmp);
    }
  }

  if(board[pos.y][pos.x]->move.droit.val){
    dec = {0, -1};

    for (i = 0; i < 8; i+=2) {
      valide = 1;
      tmp = pos;
      while (valide && j < board[pos.y][pos.x]->move.limitation) {
        tmp.x = tmp.x + dec.x;
        tmp.y = tmp.y + dec.y;
        valide = !en_dehors(tmp) && !sur_allie(board, pos, tmp) && !depasse_piece(board, pos, tmp, dec);
      }

      swp = dec.x;
      dec.x = -dec.y;
      dec.y = dec.x;
    }
  }

  if(board[pos.y][pos.x]->move.diagonal.val){
    dec = {1, -1};

    for (i = 0; i < 8; i+=2) {
      valide = 1;
      tmp = pos;
      while (valide && j < board[pos.y][pos.x]->move.limitation) {
        tmp.x = tmp.x + dec.x;
        tmp.y = tmp.y + dec.y;
        valide = !en_dehors(tmp) && !sur_allie(board, pos, tmp) && !depasse_piece(board, pos, tmp, dec);
      }

      swp = dec.x;
      dec.x = -dec.y;
      dec.y = dec.x;
    }
  }

  if(board[pos.y][pos.x]->move.ajustement[1] == 'p'){

  }
}
