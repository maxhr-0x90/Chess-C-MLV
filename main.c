#include "assets.h"

int main(){
  int scores[2], endgame;
  ChoixMenu choix;

  choix = menu();
  while (choix != Quit){
    switch(choix){
      case Play:
        endgame = jeu(0, scores);
        if(endgame != -1){
          screen_fin_partie(endgame);
          if (endgame != 2) {
            update_leaderboard(scores);
          }
        }
        break;
      case Load:
        endgame = jeu(save_state(), scores);
        if(endgame != -1){
          screen_fin_partie(endgame);
          if (endgame != 2) {
            update_leaderboard(scores);
          }
        }
        break;
      case Editor:
        endgame = jeu(8, scores);
        if(endgame != -1){
          screen_fin_partie(endgame);
          if (endgame != 2) {
            update_leaderboard(scores);
          }
        }
        break;
      case Leaderboard:
        aff_leaderboard();
        break;
      default:
        break;
    }
    choix = menu();
  }
  exit(0);
}
