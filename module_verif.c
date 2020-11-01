#include "assets.h"

int est_piece(Piece *board[][8], Coord pos){
  if(board[pos.y][pos.x] != NULL){
    return 1;
  }else{
    return 0;
  }
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
  int i;
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

int est_mortel(Piece *board[][8], Coord pos, unsigned int color){
  int i, j, x, moves[8];
  Coord enemy;

  printf("%d %d\n", pos.x, pos.y);

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL && board[pos.y][pos.x]->couleur !=board[i][j]->couleur){

        printf("%d, %d\n", i, j);
        enemy.x = j;
        enemy.y = i;

        for(x = 0; x < 8; x++){
          moves[x] = 0;
        }
        moves_possible(board, enemy, moves);
        for(x = 0; x < 8; x++){
          printf("%d ", moves[x]);
        }
        printf("\n");
        for(x = 0; x < 8; x++){
          if(pos.x < enemy.x){
            if(pos.y < enemy.y){
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[7] == -1){
                if(enemy.y == pos.y+2 && enemy.x == pos.x+1){
                  return 1;
                }
              }
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[6] == -1){
                if(enemy.y == pos.y+1 && enemy.x == pos.x+2){
                  return 1;
                }
              }
              if(moves[7] >= (enemy.y-pos.y) && (enemy.y-pos.y) == (enemy.x-pos.x)){
                return 1;
              }
            }
            if(pos.y == enemy.y){
              if(moves[6] >= (enemy.x-pos.x)){
                return 1;
              }
            }
            if(pos.y > enemy.y){
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[5] == -1){
                if(enemy.y == pos.y-1 && enemy.x == pos.x+2){
                  return 1;
                }
              }
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[4] == -1){
                if(enemy.y == pos.y-2 && enemy.x == pos.x+1){
                  return 1;
                }
              }
              if(moves[5] >= (pos.y-enemy.y) && (pos.y-enemy.y) == (enemy.x-pos.x)){
                return 1;
              }
            }
          }
          if(pos.x > enemy.x){
            if(pos.y > enemy.y){
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[3] == -1){
                if(enemy.y == pos.y-2 && enemy.x == pos.x-1){
                  return 1;
                }
              }
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[2] == -1){
                if(enemy.y == pos.y-1 && enemy.x == pos.x-2){
                  return 1;
                }
              }
              if(moves[3] >= (pos.y-enemy.y) && (pos.y-enemy.y) == (pos.x-enemy.x)){
                return 1;
              }
            }
            if(pos.y == enemy.y){
              if(moves[2] >= (pos.x-enemy.x)){
                return 1;
              }
            }
            if(pos.y < enemy.y){
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[1] == -1){
                if(enemy.y == pos.y+1 && enemy.x == pos.x-2){
                  return 1;
                }
              }
              if(board[enemy.y][enemy.x]->rang == Cavalier && moves[0] == -1){
                if(enemy.y == pos.y+2 && enemy.x == pos.x-1){
                  return 1;
                }
              }
              if(moves[1] >= (pos.x-enemy.x) && (pos.x-enemy.x) == (enemy.y-pos.y)){
                return 1;
              }
            }
          }
          if(pos.x == enemy.x){
            if(pos.y > enemy.y){
              if(moves[4] >= (pos.y-enemy.y)){
                return 1;
              }
            }
            if(pos.y < enemy.y){
              if(moves[0] >= (enemy.y-pos.y)){
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
