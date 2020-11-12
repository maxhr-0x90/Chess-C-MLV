#include "assets.h"

int(main)(){
  int choix = menu();
  while (choix != 3){
    if(choix == 1){
      screen_fin_partie(jeu(1));
    }
    if(choix == 2){
      screen_fin_partie(jeu(2));
    }
    choix = menu();
  }
  exit(0);
}
