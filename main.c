#include "assets.h"

int main(){
  int scores[2], endgame;
  ChoixMenu choix;

  choix = menu();
  while (choix != Quit){
    switch(choix){
      case Play:
        endgame = jeu(0, scores);
        screen_fin_partie(endgame);
        if (endgame != 2) {
          update_leaderboard(scores);
        }
        break;
      case Load:
        endgame = jeu(save_state(), scores);
        screen_fin_partie(endgame);
        if (endgame != 2) {
          update_leaderboard(scores);
        }
        break;
      case Editor:
        endgame = jeu(8, scores);
        screen_fin_partie(endgame);
        if (endgame != 2) {
          update_leaderboard(scores);
        }
        break;
      case Leaderboard:
        aff_leaderboard();
        break;
      default:
        break;
    }
    choix = menu();
  }/*
  JLeaderboard lb[10];
  lecture_leaderboard(lb);*/
  exit(0);
}
