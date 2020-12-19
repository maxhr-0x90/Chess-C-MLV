#include "assets.h"

int main(){
  int scores[2];
  ChoixMenu choix;

  choix = menu();
  while (choix != Quit){
    switch(choix){
      case Play:
        screen_fin_partie(jeu(0, scores));
        tri_leaderboard(scores);
        break;
      case Load:
        screen_fin_partie(jeu(save_state(), scores));
        tri_leaderboard(scores);
        break;
      case Editor:
        screen_fin_partie(jeu(8, scores));
        tri_leaderboard(scores);
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
