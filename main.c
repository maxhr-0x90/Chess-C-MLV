#include "assets.h"

int(main)(){
  int choix = menu();
  while (choix != 3){
    if(choix == 1){
      screen_fin_partie(jeu());
    }

    choix = menu();
  }
  exit(0);
}
