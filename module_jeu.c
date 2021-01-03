#include "assets.h"

/*------Fonction de déroulement d'une partie------*/

int jeu(int choix, int *scores){
  Piece set_piece[64];
  Coord pos, target;
  int i, mat, pat, moves[9], morts_w[64], morts_b[64], save = 0;
  Config jeu;
  MLV_Sound* move_sound;
  MLV_Music *music1;
  Montre clock_init, clock_white, clock_black;

  /*Cas où le mode editor est choisi*/
  if(choix == 8){
    editor(jeu.echiquier, set_piece);
    jeu.jActuel = Blanc;
    morts_b[0] = 0;
    morts_w[0] = 0;
  }

  MLV_create_window("jeu", "jeu", CASE*8, CASE*10);
  MLV_init_audio();
  move_sound = MLV_load_sound("ressources/OST/move.wav");
  music1 = MLV_load_music("ressources/OST/balade1.wav");
  mat = FALSE;
  pat = FALSE;

  /*Cas où l'on lance une nouvelle partie*/
  if(choix == 0){
    init_plateau(jeu.echiquier, set_piece);
    jeu.jActuel = Blanc;
    morts_b[0] = 0;
    morts_w[0] = 0;
  }

  /*Initialisation des struct montre*/
  set_clock(&clock_white);
  set_clock(&clock_black);
  set_local_time(&clock_init);

  /*Cas où l'on charge une partie*/
  if(0 < choix && choix < 8){
    jeu.jActuel = load(jeu.echiquier, set_piece, choix, morts_w, morts_b, &clock_white, &clock_black);
    reinject_clock(&clock_init, compt_sec(&clock_init)-(compt_sec(&clock_white) + compt_sec(&clock_black)));
  }
  else{
    update_time(&clock_white, &clock_black, clock_init);
  }

  /*Affichage graphique initial*/
  actualise_plateau(jeu.echiquier, pos, moves, FALSE);
  actualise_morts(morts_w, morts_b);
  draw_timer(&clock_white, Blanc);
  draw_timer(&clock_black, Noir);
  affichage_save();

  MLV_play_music(music1, 0.6, -1);

  while(!mat && !pat && !save){

    /*Boucle servant à saisir le premier clic du joueur actuel*/
    pos.x = -1;
    while(pos.x == -1){
      if(jeu.jActuel){
        pos = clic_or_save(jeu.echiquier, jeu.jActuel, &clock_black, &clock_white, clock_init, morts_w, morts_b, &save);
      }
      else{
        pos = clic_or_save(jeu.echiquier, jeu.jActuel, &clock_white, &clock_black, clock_init, morts_w, morts_b, &save);
      }
    }

    /*On vérifie que la position choisie par le joueur est celle d'une pièce et que la pièce choisie est de même couleur que le joueur actuel */
    if(est_piece(jeu.echiquier, pos) && jeu.echiquier[pos.y][pos.x]->couleur == jeu.jActuel){

      /*On remet le tableau de move à zero*/
      for(i = 0; i < 9; i++){
        moves[i] = 0;
      }

      /*On remplit le tableau de move avec les moves légaux de la pièce*/
      moves_legaux(jeu.echiquier, pos, moves);
      actualise_plateau(jeu.echiquier, pos, moves, TRUE);

      /*Boucle servant à saisir le deuxième clic de l'utilisateur*/
      target.x = -1;
      while(target.x == -1){
        if(jeu.jActuel){
          target = clic_or_save(jeu.echiquier, jeu.jActuel, &clock_black, &clock_white, clock_init, morts_w, morts_b, &save);
        }
        else{
          target = clic_or_save(jeu.echiquier, jeu.jActuel, &clock_white, &clock_black, clock_init, morts_w, morts_b, &save);
        }
      }

      /*Vérification de la légalité du déplacement de la pièce vers la position target*/
      if(est_legal(jeu.echiquier, pos, target, moves)){

        /*Cas où la position target n'est pas nulle, c'est à dire qu'elle est une pièce, et que cette pièce n'est pas de la couleur du joueur actuel*/
        if(jeu.echiquier[target.y][target.x] != NULL && jeu.echiquier[target.y][target.x]-> couleur != jeu.jActuel){
          if(jeu.jActuel){
            morts_w[morts_w[0]+1] = (int)jeu.echiquier[target.y][target.x]->rang;
            morts_w[0]++;
          }
          else{
            morts_b[morts_b[0]+1] = (int)jeu.echiquier[target.y][target.x]->rang;
            morts_b[0]++;
          }
        }

        /*Déplacement de la pièce*/
        jeu.echiquier[target.y][target.x] = jeu.echiquier[pos.y][pos.x];

        /*Remise à NULL de la case de l'échiquier qui contenait la pièce*/
        jeu.echiquier[pos.y][pos.x] = NULL;

        maj_board(jeu.echiquier, pos, target, morts_w, morts_b);
        jeu.jActuel = (jeu.jActuel+1)%2;

        MLV_play_sound(move_sound, 0.2);
      }
      actualise_plateau(jeu.echiquier, pos, moves, FALSE);
      actualise_morts(morts_w, morts_b);
    }
    mat = est_echec_et_mat(jeu.echiquier, jeu.jActuel);
    pat = est_pat(jeu.echiquier, jeu.jActuel) || seulement_rois(jeu.echiquier);
  }

  /*Cas où le joueur à choisi de sauvegarder*/
  if(save){
    MLV_free_sound(move_sound);
    MLV_free_music(music1);
    MLV_free_audio();
    MLV_free_window();
    return -1;
  }

  /*On fixe le score en fonction du dernier joueur dans le cas où la partie a fini sur un mat*/
  if(!jeu.jActuel){
    scores[0] = -50;
    scores[1] = 200;
  }
  else{
    scores[0] = 200;
    scores[1] = -50;
  }

  MLV_free_sound(move_sound);
  MLV_free_music(music1);
  MLV_free_audio();
  MLV_free_window();

  /*Si le jeu a fini sur un mat, on retourne le joueur actuel, sinon on retourne 2, soit la couleur Nulle symbolisant le pat*/
  if(mat){
    return jeu.jActuel;
  } else {
    return 2;
  }
}
