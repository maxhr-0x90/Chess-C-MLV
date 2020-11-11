#include "assets.h"

int jeu(){
  Piece set_piece[32];
  Coord pos, target;
  int i, loop, moves[9];
  Config jeu;
  MLV_Sound* move_sound;

  MLV_create_window("jeu", "jeu", CASE*8, CASE*8);
  MLV_init_audio();
  move_sound = MLV_load_sound("ressources/OST/move.wav");

  jeu.jActuel = Blanc;
  /*init_plateau(jeu.echiquier, set_piece);*/
  load(jeu.echiquier, set_piece);
  actualise_plateau(jeu.echiquier, pos, moves, 0);

  loop = 1;
  while(loop){
    pos = clic();
    if(est_piece(jeu.echiquier, pos) && jeu.echiquier[pos.y][pos.x]->couleur == jeu.jActuel){
      for(i = 0; i<9; i++){
        moves[i] = 0;
      }
      moves_legaux(jeu.echiquier, pos, moves);
      actualise_plateau(jeu.echiquier, pos, moves, 1);

      target = clic();
      if(est_legal(jeu.echiquier, pos, target, moves)){
        jeu.echiquier[target.y][target.x] = jeu.echiquier[pos.y][pos.x];
        jeu.echiquier[pos.y][pos.x] = NULL;
        jeu.jActuel = (jeu.jActuel+1)%2;
        MLV_play_sound(move_sound, 0.2);
      }
      actualise_plateau(jeu.echiquier, pos, moves, 0);
    }
    if(est_echec_et_mat(jeu.echiquier, jeu.jActuel)){
      printf("c'est tout bon\n");
      loop = 0;
    }
  }
  MLV_play_sound(move_sound, 0.5);
  MLV_free_audio();
  MLV_free_window();

  return jeu.jActuel;
}
