#include "assets.h"

int jeu(int choix, int *scores){
  Piece set_piece[32];
  Coord pos, target;
  int i, mat, moves[9];
  Config jeu;
  MLV_Sound* move_sound;

  MLV_create_window("jeu", "jeu", CASE*8, CASE*9);
  MLV_init_audio();
  move_sound = MLV_load_sound("ressources/OST/move.wav");
  mat = 0;

  if(choix == 1){
    init_plateau(jeu.echiquier, set_piece);
    jeu.jActuel = Blanc;
  }
  if(choix == 2){
    jeu.jActuel = load(jeu.echiquier, set_piece);
  }
  actualise_plateau(jeu.echiquier, pos, moves, 0);
  affichage_save();
  while(!mat){
    pos = clic_or_save(jeu.echiquier, jeu.jActuel);

    if(est_piece(jeu.echiquier, pos) && jeu.echiquier[pos.y][pos.x]->couleur == jeu.jActuel){
      for(i = 0; i<9; i++){
        moves[i] = 0;
      }
      moves_legaux(jeu.echiquier, pos, moves);
      actualise_plateau(jeu.echiquier, pos, moves, 1);

      target = clic_or_save(jeu.echiquier, jeu.jActuel);

      if(est_legal(jeu.echiquier, pos, target, moves)){
        jeu.echiquier[target.y][target.x] = jeu.echiquier[pos.y][pos.x];
        jeu.echiquier[pos.y][pos.x] = NULL;
        jeu.jActuel = (jeu.jActuel+1)%2;
        MLV_play_sound(move_sound, 0.2);
      }
      actualise_plateau(jeu.echiquier, pos, moves, 0);
    }
    mat = est_echec_et_mat(jeu.echiquier, jeu.jActuel);
  }

  if(!jeu.jActuel){
    scores[1] = score(jeu.echiquier, Noir)+200;
    scores[0] = score(jeu.echiquier, Blanc);
  }
  else{
    scores[1] = score(jeu.echiquier, Noir)+200;
    scores[0] = score(jeu.echiquier, Blanc);
  }
  MLV_play_sound(move_sound, 0.5);
  MLV_free_sound(move_sound);
  MLV_free_audio();
  MLV_free_window();

  return jeu.jActuel;
}
