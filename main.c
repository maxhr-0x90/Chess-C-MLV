#include "assets.h"

int main(){
  int choix, scores[2];

  choix = menu();
  while (choix != 8){
    switch(choix){
      case 1:
        screen_fin_partie(jeu(0, scores));
        tri_leaderboard(scores);
        break;
      case 2:
        screen_fin_partie(jeu(save_state(), scores));
        tri_leaderboard(scores);
        break;
      case 9:
        aff_leaderboard();
        break;
      default:
        break;
    }
    choix = menu();
  }/*
  Piece *board[8][8];
  Piece set[64];
  editor(board, set);penis
  */exit(0);
}
