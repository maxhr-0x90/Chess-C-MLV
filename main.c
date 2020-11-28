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
  }
  exit(0);
}
