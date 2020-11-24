#include "assets.h"

/*------Fonction de déroulement d'une partie'------*/

int jeu(int choix, int *scores){
  Piece set_piece[32];
  Coord pos, target;
  int i, mat, moves[9];
  Config jeu;
  MLV_Sound* move_sound;

  MLV_create_window("jeu", "jeu", CASE*8, CASE*9);
  MLV_init_audio();
  move_sound = MLV_load_sound("ressources/OST/move.wav");
  mat = FALSE;

  if(choix == 1){
    init_plateau(jeu.echiquier, set_piece);
    jeu.jActuel = Blanc;
  }
  if(1 < choix && choix < 8){
    jeu.jActuel = load(jeu.echiquier, set_piece, choix);
  }
  actualise_plateau(jeu.echiquier, pos, moves, FALSE);
  affichage_save();
  while(!mat){
    pos = clic_or_save(jeu.echiquier, jeu.jActuel);

    if(est_piece(jeu.echiquier, pos) && jeu.echiquier[pos.y][pos.x]->couleur == jeu.jActuel){
      for(i = 0; i < 9; i++){
        moves[i] = 0;
      }
      moves_legaux(jeu.echiquier, pos, moves);
      actualise_plateau(jeu.echiquier, pos, moves, TRUE);

      target = clic_or_save(jeu.echiquier, jeu.jActuel);

      if(est_legal(jeu.echiquier, pos, target, moves)){
        jeu.echiquier[target.y][target.x] = jeu.echiquier[pos.y][pos.x];
        jeu.echiquier[pos.y][pos.x] = NULL;
        maj_board(jeu.echiquier, pos, target);
        jeu.jActuel = (jeu.jActuel+1)%2;
        pion_ligne_finale(jeu.echiquier, target);
        MLV_play_sound(move_sound, 0.2);
      }
      actualise_plateau(jeu.echiquier, pos, moves, FALSE);
    }
    mat = est_echec_et_mat(jeu.echiquier, jeu.jActuel);
  }

  if(!jeu.jActuel){
    scores[0] = score(jeu.echiquier, Blanc);
    scores[1] = score(jeu.echiquier, Noir)+200;
  }
  else{
    scores[0] = score(jeu.echiquier, Blanc)+200;
    scores[1] = score(jeu.echiquier, Noir);
  }
  MLV_play_sound(move_sound, 0.5);
  MLV_free_sound(move_sound);
  MLV_free_audio();
  MLV_free_window();

  return jeu.jActuel;
}
