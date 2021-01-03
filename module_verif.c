#include "assets.h"

/*-----Fonctions de détections essentielles-----*/
int est_piece(Piece *board[][8], Coord pos){
    return (board[pos.y][pos.x] != NULL);
}

int en_dehors(Coord pos){
  return !(pos.x >= 0 && pos.x <= 7 && pos.y >= 0 && pos.y <= 7);
}

int sur_allie(Piece *board[][8], Coord pos, Coord target){
  if(board[target.y][target.x] == NULL
    || board[target.y][target.x]->couleur != board[pos.y][pos.x]->couleur){
    return FALSE;
  }
  return TRUE;
}

int depasse_piece(Piece *board[][8], Coord pos, Coord target, Coord deplace){
  if(!(pos.x == (target.x - deplace.x) && pos.y == (target.y - deplace.y)) &&
   board[target.y - deplace.y][target.x - deplace.x] != NULL){
    return TRUE;
  }
  return FALSE;
}


/*-----Fonctions de calcul de mouvements possibles théoriques-----*/
void formeL_possible(Piece *board[][8], Coord pos, int *moves){
  int i;
  Coord dec, tmp_coord;
  char alterne_angle[] = {'c', 'C'};

  /*Initialisation du vecteur dec, valeur de decalage*/
  dec.x = 1;
  dec.y = -2;
  for (i = 0; i < 8; i++) {
    tmp_coord.x = pos.x + dec.x;
    tmp_coord.y = pos.y + dec.y;
    moves[i] = (!en_dehors(tmp_coord) && !sur_allie(board, pos, tmp_coord)) * -1;

    dec = rot_mode(dec, alterne_angle[i % 2]);
  }
}

void droit_possible(Piece *board[][8], Coord pos, int *moves){
  int i, j, valide;
  Coord dec, tmp_coord;

  /*Initialisation du vecteur dec, valeur de decalage*/
  dec.x = 0;
  dec.y = -1;

  for (i = 0; i < 8; i+=2) {
    valide = TRUE;
    tmp_coord = pos;
    j = 0;

    while (valide && j < board[pos.y][pos.x]->move.limitation) {
      tmp_coord.x = tmp_coord.x + dec.x;
      tmp_coord.y = tmp_coord.y + dec.y;
      valide = (
        !en_dehors(tmp_coord)
        && !sur_allie(board, pos, tmp_coord)
        && !depasse_piece(board, pos, tmp_coord, dec));

      if(valide){
        moves[i]++;
      }
      j++;
    }

    dec = rot_mode(dec, 90);
  }
}

void diagonal_possible(Piece *board[][8], Coord pos, int *moves){
  int i, j, valide;
  Coord dec, tmp_coord;

  /*Initialisation du vecteur dec, valeur de decalage*/
  dec.x = 1;
  dec.y = -1;

  for (i = 1; i < 8; i+=2) {
    valide = TRUE;
    tmp_coord = pos;
    j = 0;

    while (valide && j < board[pos.y][pos.x]->move.limitation) {
      tmp_coord.x = tmp_coord.x + dec.x;
      tmp_coord.y = tmp_coord.y + dec.y;
      valide = (
        !en_dehors(tmp_coord)
        && !sur_allie(board, pos, tmp_coord)
        && !depasse_piece(board, pos, tmp_coord, dec));

      if(valide){
        moves[i]++;
      }
      j++;
    }

    dec = rot_mode(dec, 90);
  }
}

void ajustement_p_possible(Piece *board[][8], Coord pos, int *moves){
  int i, en_passant;
  Coord tmp;
  Piece *pion = board[pos.y][pos.x];
  int ajust_mov = pion->move.ajustement[0] % 10;

  /*Vérifie dans l'ordre:
    1.La couleur
    2.La possibilité de déplacement
    3.La possibilité d'attaque
    4.La possibilité d'une prise en passant*/

  /*--1--*/
  if (pion->couleur == Blanc) {
    /*--2--*/
    i = 1;
    tmp.x = pos.x;
    tmp.y = pos.y - i;
    while (!en_dehors(tmp) && !est_piece(board, tmp) && i <= ajust_mov) {
      moves[0]++;
      i++;
      tmp.y = pos.y - i;
    }

    /*--3--*/
    tmp.x = pos.x - 1;
    tmp.y = pos.y - 1;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[tmp.y][tmp.x]->couleur == Noir) {
        moves[7] = 1;
      }
    }

    /*--4--*/
    tmp.y = pos.y;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[tmp.y][tmp.x]->couleur  == Noir) {
        en_passant = board[tmp.y][tmp.x]->move.ajustement[0] / 10;
        if(en_passant){
          moves[7] = 1;
        }
      }
    }

    /*--3--*/
    tmp.x = pos.x + 1;
    tmp.y = pos.y - 1;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[tmp.y][tmp.x]->couleur == Noir) {
        moves[1] = 1;
      }
    }

    /*--4--*/
    tmp.y = pos.y;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[tmp.y][tmp.x]->couleur  == Noir) {
        en_passant = board[tmp.y][tmp.x]->move.ajustement[0] / 10;
        if(en_passant){
          moves[1] = 1;
        }
      }
    }
  }

  /*--1--*/
  if (pion->couleur == Noir) {
    /*--2--*/
    i = 1;
    tmp.x = pos.x;
    tmp.y = pos.y + i;
    while (!en_dehors(tmp) && !est_piece(board, tmp) && i <= ajust_mov) {
      moves[4]++;
      i++;
      tmp.y = pos.y + i;
    }

    /*--3--*/
    tmp.x = pos.x - 1;
    tmp.y = pos.y + 1;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[pos.y + 1][pos.x - 1]->couleur == Blanc) {
        moves[5] = 1;
      }
    }

    /*--4--*/
    tmp.y = pos.y;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[tmp.y][tmp.x]->couleur  == Blanc) {
        en_passant = board[tmp.y][tmp.x]->move.ajustement[0] / 10;
        if(en_passant){
          moves[5] = 1;
        }
      }
    }

    /*--3--*/
    tmp.x = pos.x + 1;
    tmp.y = pos.y + 1;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[pos.y + 1][pos.x + 1]->couleur == Blanc) {
        moves[3] = 1;
      }
    }

    /*--4--*/
    tmp.y = pos.y;
    if (!en_dehors(tmp) && est_piece(board, tmp)){
      if (board[tmp.y][tmp.x]->couleur  == Blanc) {
        en_passant = board[tmp.y][tmp.x]->move.ajustement[0] / 10;
        if(en_passant){
          moves[3] = 1;
        }
      }
    }
  }
}

void ajustement_r_possible(Piece *board[][8], Coord pos, int *moves){
  Piece *roi = board[pos.y][pos.x];
  Coord tmp_coord;
  int count;

  if (roi->nbMouv == 0) {
    tmp_coord.x = pos.x + 1;
    tmp_coord.y = pos.y;
    count = 1;

    while(!en_dehors(tmp_coord) && !est_piece(board, tmp_coord)){
      count++;
      tmp_coord.x++;
    }

    if(!en_dehors(tmp_coord) && est_piece(board, tmp_coord)){
      if(board[tmp_coord.y][tmp_coord.x]->rang == Tour
        && board[tmp_coord.y][tmp_coord.x]->nbMouv == 0){
        moves[2] = 2;
      }
    }

    tmp_coord.x = pos.x - 1;
    count = 1;

    while(!en_dehors(tmp_coord) && !est_piece(board, tmp_coord)){
      count++;
      tmp_coord.x--;
    }

    if(!en_dehors(tmp_coord) && est_piece(board, tmp_coord)){
      if(board[tmp_coord.y][tmp_coord.x]->rang == Tour
        && board[tmp_coord.y][tmp_coord.x]->nbMouv == 0){
        moves[6] = 2;
      }
    }
  }
}

void moves_possibles(Piece *board[][8], Coord pos, int *moves){
  int i;
  for(i = 0; i < 9; i++){
    moves[i] = 0;
  }
  /*Déplacements en L (Cavalier)*/
  if(board[pos.y][pos.x]->move.formeL.val){
    formeL_possible(board, pos, moves);
  }

  /*Déplacements sur les droites*/
  if(board[pos.y][pos.x]->move.droit.val){
    droit_possible(board, pos, moves);
  }

  /*Déplacements sur les diagonales*/
  if(board[pos.y][pos.x]->move.diagonal.val){
    diagonal_possible(board, pos, moves);
  }

  /*Ajustement des déplacements pour le pion*/
  if(board[pos.y][pos.x]->move.ajustement[1] == 'p'){
    ajustement_p_possible(board, pos, moves);
  }

  /*Ajustement des déplacements pour le roque*/
  if(board[pos.y][pos.x]->move.ajustement[1] == 'r'){
    ajustement_r_possible(board, pos, moves);
  }
}


/*-----Fonctions de détections des déplacements légaux-----*/
Coord get_pos_roi(Piece *board[][8], unsigned int color){
  int i, j;
  Coord pos;
  pos.x = -1;
  pos.y = -1;

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL && board[i][j]->rang == Roi && board[i][j]->couleur == color){
        pos.x = j;
        pos.y = i;
        return pos;
      }
    }
  }
  return pos;
}


/*------Fonction déterminant si une case de l'échiquier est mortelle------*/

int est_mortel(Piece *board[][8], Coord pos, Joueur color){
  int i, j, x, moves[8];
  Coord enemy;

  /*Pour chaque pièce de l'échiquier, on vérifie si elle peut atteindre la case décrite par pos*/
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL && color !=board[i][j]->couleur){

        enemy.x = j;
        enemy.y = i;
        moves_possibles(board, enemy, moves);

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

/*------Fonction déterminant si le roi est échec (si la case ou il se trouve est mortelle)------*/

int est_echec(Piece *board[][8], unsigned int color){
  Coord pos = get_pos_roi(board, color);
  if(est_mortel(board, pos, color)){
    return 1;
  }
  return 0;
}


/*-----Fonctions de déplacements légaux / Moteur du jeu d'échec-----*/
void moves_legaux(Piece *board[][8], Coord pos, int *moves){
  int i, j, safe, roque_only;
  int del_start = -1;
  char alterne_angle[] = {'c', 'C'};
  Piece *swpPiece;
  Piece *tempPiece = board[pos.y][pos.x];
  Coord dec;
  Coord posRoi = get_pos_roi(board, tempPiece->couleur);

  moves_possibles(board, pos, moves);

  if(tempPiece->rang != Roi){
    moves[8] = est_echec(board, tempPiece->couleur);
  } else {
    moves[8] = 0;
  }

  /*Détection des pièces protégeants le roi*/
  if(!(est_echec(board, tempPiece->couleur))){
    board[pos.y][pos.x] = NULL;

    if(est_echec(board, tempPiece->couleur)){
      if(tempPiece->rang != Cavalier){
        if (pos.x == posRoi.x) {
          del_start = 1;
        }

        if (pos.y == posRoi.y) {
          del_start = 3;
        }

        if (pos.x - posRoi.x == pos.y - posRoi.y) {
          del_start = 0;
        }

        if (pos.x - posRoi.x == posRoi.y - pos.y) {
          del_start = 2;
        }

        for (i = del_start; i < del_start + 3 ; i++) {
          moves[i] = 0;
          moves[(i+4) % 8] = 0;
        }
      } else {
        for (j = 0; j < 8; j++) {
          moves[j] = 0;
        }
      }
    }

    board[pos.y][pos.x] = tempPiece;
  }

  /*Recherche des mouvements pouvant sauver le roi
    Prévention du suicide du roi*/
  if(est_echec(board, tempPiece->couleur) || tempPiece->rang == Roi){
    if(tempPiece->rang != Cavalier){
      dec.x = 0;
      dec.y = -1;
    } else {
      dec.x = 1;
      dec.y = -2;
    }
    board[pos.y][pos.x] = NULL;

    for (i = 0; i < 8; i++) {
      roque_only = 0;
      safe = 0;
      if(tempPiece->rang != Cavalier){
        for (j = 1; j <= moves[i]; j++) {
          swpPiece = board[pos.y + dec.y * j][pos.x + dec.x * j];
          board[pos.y + dec.y * j][pos.x + dec.x * j] = tempPiece;

          if(!(est_echec(board, tempPiece->couleur))){
            safe = j;
          } else if(tempPiece->rang == Roi && moves[i] == 2){
            roque_only = 1;
          }

          board[pos.y + dec.y * j][pos.x + dec.x * j] = swpPiece;
        }

      } else {
        swpPiece = board[pos.y + dec.y][pos.x + dec.x];
        board[pos.y + dec.y][pos.x + dec.x] = tempPiece;

        if(!(est_echec(board, tempPiece->couleur))){
          safe = -1;
        }

        board[pos.y + dec.y][pos.x + dec.x] = swpPiece;
      }

      /*Ajustement spécifique pour le roque*/
      if(roque_only){
        moves[i] = -safe;
      } else {
        moves[i] = safe;
      }

      if(tempPiece->rang != Cavalier){
        dec = rot_mode(dec, 45);
      } else {
        dec = rot_mode(dec, alterne_angle[i % 2]);
      }
    }

    board[pos.y][pos.x] = tempPiece;
  }
}

/*------Fonction déterminant si un mouvement est légal------*/

int est_legal(Piece *board[][8], Coord pos, Coord target, int *moves){
  int i, j, start;
  char alterne_angle[] = {'c', 'C'};
  Piece *tempPiece = board[pos.y][pos.x];
  Coord dec;

  if(tempPiece->rang != Cavalier){
    dec.x = 0;
    dec.y = -1;
  } else {
    dec.x = 1;
    dec.y = -2;
  }

  for (i = 0; i < 8; i++) {
    if(tempPiece->rang != Cavalier){
      if(moves[8]){
        if(moves[i]){
          start = moves[i];
        } else {
          start = 1;
        }
      } else {
        start = 1;
      }
      for (j = start; j <= moves[i]; j++) {
        if ((pos.x + dec.x*j) == target.x && (pos.y + dec.y*j) == target.y){
          return 1;
        }
      }

      if (moves[i] == -2){
        if ((pos.x + dec.x*2) == target.x){
          return 1;
        }
      }

    } else {
      if (pos.x + dec.x == target.x && pos.y + dec.y == target.y){
        if (moves[i] == -1){
        return 1;
        }
      }
    }

    if(tempPiece->rang != Cavalier){
      dec = rot_mode(dec, 45);
    } else {
      dec = rot_mode(dec, alterne_angle[i % 2]);
    }
  }

  return 0;
}


/*-------------Endgame-------------*/
int zero_moves(Piece *board[][8], Joueur color){
  int i, j, k, move[9];
  Coord pos;

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      pos.x = j;
      pos.y = i;
      if(board[i][j] != NULL && color == board[i][j]->couleur){

        /*Vérification qu'aucun mouvements n'est possible*/
        moves_legaux(board, pos, move);
        for(k = 0; k < 8; k++){
          if(move[k] != 0){
            return 0;
          }
        }
      }
    }
  }
  return 1;
}

int est_echec_et_mat(Piece *board[][8], Joueur color){
  int result;

  result = zero_moves(board, color);
  result &= est_echec(board, color);

  return result;
}

int est_pat(Piece *board[][8], Joueur color){
  int result;

  result = zero_moves(board, color);
  result &= !(est_echec(board, color));

  return result;
}

int seulement_rois(Piece *board[][8]){
  int i, j, count = 0;

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
        count++;
      }
    }
  }

  return (count == 2);
}

/*---Fonction vérifiant si un pion peut se changer---*/

void pion_ligne_finale(Piece *board[][8], Coord xy){
  int x = xy.x, y = xy.y, choix = 0;

  /*vérification que la pièce est un pion*/
  if(board[y][x]->rang == Pion){

    /*vérification de la position du pion sur la denirère ligne en fonction de sa couleur*/
    if(board[y][x]->couleur == Noir && y == 7){
      choix = choix_piece_pion(board[y][x]->couleur);
    }
    if(board[y][x]->couleur == Blanc && y == 0){
      choix = choix_piece_pion(board[y][x]->couleur);
    }
  }

  if(choix != 0){
    /*on initialise la pièce en fonction du choix du joueur (C.F. la fonction choix_piece_pion)*/
    board[y][x]->rang = choix;
    if(board[y][x]->rang == Reine){
      deplace_reine(board[y][x]);
    }
    if(board[y][x]->rang == Cavalier){
      deplace_cavalier(board[y][x]);
    }
    if(board[y][x]->rang == Tour){
      deplace_tour(board[y][x]);
    }
    if(board[y][x]->rang == Fou){
      deplace_fou(board[y][x]);
    }
  }
}

/*Mise à jour / Conservation de la cohérence du jeu*/
void maj_board(Piece *board[][8], Coord old, Coord new, int *morts_w, int *morts_b){
  int i, j;
  Piece *piece_deplacee = board[new.y][new.x];
  piece_deplacee->nbMouv += 1;

  /*Vérification de la prise en passant*/
  if(piece_deplacee->rang == Pion){
    if (piece_deplacee->couleur == Noir) {
      if (board[new.y - 1][new.x] != NULL) {
        if (board[new.y - 1][new.x]->move.ajustement[0] > 9) {
          board[new.y - 1][new.x] = NULL;
          morts_w[morts_w[0]+1] = Pion;
          morts_w[0]++;
          printf("%d\n", morts_w[morts_w[0]]);
        }
      }
    } else if (piece_deplacee->couleur == Blanc) {
      if (board[new.y + 1][new.x] != NULL) {
        if (board[new.y + 1][new.x]->move.ajustement[0] > 9) {
          board[new.y + 1][new.x] = NULL;
          morts_b[morts_b[0]+1] = Pion;
          morts_b[0]++;
          printf("%d\n", morts_b[morts_b[0]]);
        }
      }
    }
  }

  /*Réinitialisation des ajustements des pions -> car en_passant temporaire*/
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] != NULL) {
        if(board[i][j]->rang == Pion && board[i][j]->nbMouv > 0){
          board[i][j]->move.ajustement[0] = 1;
        }
      }
    }
  }

  /*Ajustement pour la possibilité de la prise en passant*/
  if(piece_deplacee->rang == Pion){
    if (abs(new.y - old.y) == 2) {
      piece_deplacee->move.ajustement[0] += 10;
    }
  }

  /*Déplace ment de la tour suite à un roque*/
  if(piece_deplacee->rang == Roi){
    if(new.x - old.x == 2){
      board[new.y][new.x - 1] = board[new.y][7];
      board[new.y][7] = NULL;
    } else if(new.x - old.x == -2){
      board[new.y][new.x + 1] = board[new.y][0];
      board[new.y][0] = NULL;
    }
  }

  /*Vérification de la potentielle transformation du pion*/
  pion_ligne_finale(board, new);
}
