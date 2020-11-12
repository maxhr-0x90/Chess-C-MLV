#include "assets.h"

void save(Piece *board[][8], Joueur jActuel){
  int i, j, x;
  FILE* save = NULL;
  save = fopen("save", "w");

  x = 0;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
        x++;
      }
    }
  }
  fputc(jActuel, save);
  fputc(x, save);
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
        fputc(i, save);
        fputc(j, save);
        fputc(board[i][j]->rang, save);
        fputc(board[i][j]->couleur, save);
        fputc(board[i][j]->nbMouv, save);
        fputc(board[i][j]->estVivant.val, save);
        fputc(board[i][j]->move.droit.val, save);
        fputc(board[i][j]->move.diagonal.val, save);
        fputc(board[i][j]->move.formeL.val, save);
        fputc(board[i][j]->move.limitation, save);
        fputc(board[i][j]->move.ajustement[0], save);
        if(board[i][j]->move.ajustement[0] != 0){
          fputc(board[i][j]->move.ajustement[1], save);
        }
      }
    }
  }
  fclose(save);
}

Joueur load(Piece *board[][8], Piece pieces[32]){
  int i, j, x, y;
  Joueur jActuel;
  FILE* save = NULL;
  save = fopen("save", "r+");
  jActuel = fgetc(save);
  i = 0;
  j = fgetc(save);

  vider_plateau(board);
  for(i = 0; i < j; i++){

    x = fgetc(save);
    y = fgetc(save);
    pieces[i].rang = fgetc(save);
    pieces[i].couleur = fgetc(save);
    pieces[i].nbMouv = fgetc(save);
    pieces[i].estVivant.val = fgetc(save);
    pieces[i].move.droit.val = fgetc(save);
    pieces[i].move.diagonal.val = fgetc(save);
    pieces[i].move.formeL.val = fgetc(save);
    pieces[i].move.limitation = fgetc(save);
    pieces[i].move.ajustement[0] = fgetc(save);
    if(pieces[i].move.ajustement[0])
      pieces[i].move.ajustement[1] = fgetc(save);
    board[x][y] = &pieces[i];
  }

  fclose(save);
  return jActuel;
}
