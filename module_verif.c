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
    return 0;
  }
  return 1;
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
   board[target.y - deplace.y][target.x - deplace.x] != NULL){
    return 1;
  }
  return 0;
}

void formeL_posssible(Piece *board[][8], Coord pos, int *moves){
  int i, swp;
  Coord dec;
  Coord tmp;

  /*initialisation du vecteur dec, valeur de decalages*/
  dec.x = 1;
  dec.y = -2;
  for (i = 0; i < 8; i+=2) {
    tmp.x = pos.x + dec.x;
    tmp.y = pos.y + dec.y;
    moves[i] = (!en_dehors(tmp) && !sur_allie(board, pos, tmp)) * -1;

    /*Rotation de 90° du vecteur dec*/
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }

  /*initialisation du vecteur dec, valeur de decalages*/
  dec.x = 2;
  dec.y = -1;
  for (i = 1; i < 8; i+=2) {
    tmp.x = pos.x + dec.x;
    tmp.y = pos.y + dec.y;
    moves[i] = (!en_dehors(tmp) && !sur_allie(board, pos, tmp)) * -1;

    /*Rotation de 90° du vecteur dec*/
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }
}

void droit_posssible(Piece *board[][8], Coord pos, int *moves){
  int i, j, valide, swp;
  Coord dec;
  Coord tmp;

  /*initialisation du vecteur dec, valeur de decalages*/
  dec.x = 0;
  dec.y = -1;

  for (i = 0; i < 8; i+=2) {
    valide = 1;
    tmp = pos;
    j = 0;
    while (valide && j < board[pos.y][pos.x]->move.limitation) {
      tmp.x = tmp.x + dec.x;
      tmp.y = tmp.y + dec.y;
      valide = !en_dehors(tmp) && !sur_allie(board, pos, tmp) && !depasse_piece(board, pos, tmp, dec);
      if(valide){
        moves[i]++;
      }
      j++;
    }

    /*Rotation de 90° du vecteur dec*/
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }
}

void diagonal_posssible(Piece *board[][8], Coord pos, int *moves){
  int i, j, valide, swp;
  Coord dec;
  Coord tmp;

  /*initialisation du vecteur dec, valeur de decalages*/
  dec.x = 1;
  dec.y = -1;

  for (i = 1; i < 8; i+=2) {
    valide = 1;
    tmp = pos;
    j = 0;
    while (valide && j < board[pos.y][pos.x]->move.limitation) {
      tmp.x = tmp.x + dec.x;
      tmp.y = tmp.y + dec.y;
      valide = !en_dehors(tmp) && !sur_allie(board, pos, tmp) && !depasse_piece(board, pos, tmp, dec);
      if(valide){
        moves[i]++;
      }
      j++;
    }

    /*Rotation de 90° du vecteur dec*/
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }
}

void ajustement_p_posssible(Piece *board[][8], Coord pos, int *moves){
  int i, j;
  Coord tmp;

  if (board[pos.y][pos.x]->couleur == Blanc) {
    i = 1;
    tmp.x = pos.x;
    tmp.y = pos.y - i;
    while (!en_dehors(tmp) && board[tmp.y][tmp.x] == NULL && i <= board[pos.y][pos.x]->move.ajustement[0]) {
      moves[0]++;
      i++;
      tmp.y = pos.y - i;
    }

    tmp.x = pos.x - 1;
    tmp.y = pos.y - 1;
    if (!en_dehors(tmp) && board[tmp.y][tmp.x] != NULL && board[pos.y - 1][pos.x - 1]->couleur == Noir){
      moves[7] = 1;
    }

    tmp.x = pos.x + 1;
    if (!en_dehors(tmp) && board[tmp.y][tmp.x] != NULL && board[pos.y - 1][pos.x + 1]->couleur == Noir){
      moves[1] = 1;
    }
  }

  if (board[pos.y][pos.x]->couleur == Noir) {
    i = 1;
    tmp.x = pos.x;
    tmp.y = pos.y + i;
    while (!en_dehors(tmp) && board[tmp.y][tmp.x] == NULL && i <= board[pos.y][pos.x]->move.ajustement[0]) {
      moves[4]++;
      i++;
      tmp.y = pos.y + i;
    }

    tmp.x = pos.x - 1;
    tmp.y = pos.y + 1;
    if (!en_dehors(tmp) && board[tmp.y][tmp.x] != NULL && board[pos.y + 1][pos.x - 1]->couleur == Blanc){
      moves[5] = 1;
    }

    tmp.x = pos.x + 1;
    if (!en_dehors(tmp) && board[tmp.y][tmp.x] != NULL && board[pos.y + 1][pos.x + 1]->couleur == Blanc){
      moves[3] = 1;
    }
  }
}

void moves_possible(Piece *board[][8], Coord pos, int *moves){
  if(board[pos.y][pos.x]->move.formeL.val){
    formeL_posssible(board, pos, moves);
  }

  if(board[pos.y][pos.x]->move.droit.val){
    droit_posssible(board, pos, moves);
  }

  if(board[pos.y][pos.x]->move.diagonal.val){
    diagonal_posssible(board, pos, moves);
  }

  if(board[pos.y][pos.x]->move.ajustement[1] == 'p'){
    ajustement_p_posssible(board, pos, moves);
  }
}
