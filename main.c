#include "assets.h"

int main(){
  int choix, scores[2];

  choix = menu();
  while (choix != 8){
    switch(choix){
      case 1:
        screen_fin_partie(jeu(1, scores));
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
  MLV_create_window("ok", "ok", CASE*8, CASE*8);
  MLV_clear_window(MLV_COLOR_WHITE);
  choix_piece_pion(1);
  exit(0);
}
