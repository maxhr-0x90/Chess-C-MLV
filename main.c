#include "assets.h"

int main(){
  int choix, scores[2];

  choix = menu();
  while (choix != 3){
    switch(choix){
      case 1:
        screen_fin_partie(jeu(1, scores));
        tri_leaderboard(scores);
        break;
      case 2:
        screen_fin_partie(jeu(2, scores));
        tri_leaderboard(scores);
        break;
      case 4:
        aff_leaderboard();
        break;
      default:
        break;
    }
    choix = menu();
  }
  exit(0);
}
