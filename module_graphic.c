#include "assets.h"

/*GESTION DE L'AFFICHAGE*/

/* Fonction ayant pour but de dessiner le damier de l'échiquier*/
void make_grid(){
  int x, y;
  MLV_draw_filled_rectangle(0, 0, 8*CASE, 8*CASE, MLV_COLOR_BLACK);
  for(y = 0; y < 4; y++)
    for(x = 0; x < 4; x++){
      MLV_draw_filled_rectangle(x*CASE*2, y*CASE*2, CASE, CASE, MLV_COLOR_WHITE);
      MLV_draw_filled_rectangle(CASE+x*CASE*2, CASE+y*CASE*2, CASE, CASE, MLV_COLOR_WHITE);
    }
}

/* Fonction ayant pour but de placer les pièces de manière graphique sur le plateau.*/
void color_piece(Piece *board[][8]){
  int i, j;
	char path[30];
	char *folder = "ressources/pieces/";
	char *ext = ".png";
	char color[][2] = {"B", "N"};
	char images_tab[][5] = {"roi", "dame", "tour", "fou", "cava", "pion"};
	MLV_Image *image;

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
				strcpy(path, folder);
				strcat(path, images_tab[board[i][j]->rang]);
				strcat(path, color[board[i][j]->couleur]);
				strcat(path, ext);
				image = MLV_load_image(path);

        MLV_resize_image(image, CASE, CASE);
        MLV_draw_image(image, CASE*j, CASE*i);
				path[0] = '\0';
			}
		}
	}
  MLV_actualise_window();
}

void indic_deplace(Piece *board[][8], Coord pos, int *moves){
  int i, j;
  char alterne_angle[] = {'c', 'C'};
  Coord dec;
  Piece *tempPiece = board[pos.y][pos.x];

  if(tempPiece->rang != Cavalier){
    dec.x = 0;
    dec.y = -1;
  } else {
    dec.x = 1;
    dec.y = -2;
  }

  for (i = 0; i < 8; i++) {
    if(tempPiece->rang != Cavalier){
      if(!moves[8]){
        for (j = 1; j <= moves[i]; j++) {
          MLV_draw_filled_circle(CASE*(dec.x*j + pos.x)+CASE/2, CASE*(dec.y*j + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
        }
      } else if (moves[8] && moves[i] != -1 && moves[i] != 0){
        MLV_draw_filled_circle(CASE*(dec.x*moves[i] + pos.x)+CASE/2, CASE*(dec.y*moves[i] + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
      }

      if (moves[i] == -2){
        MLV_draw_filled_circle(CASE*(dec.x*2 + pos.x)+CASE/2, CASE*(dec.y*2 + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
      }

    } else {
      if (moves[i] == -1) {
        MLV_draw_filled_circle(CASE*(dec.x + pos.x)+CASE/2, CASE*(dec.y + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
      }
    }

    if(tempPiece->rang != Cavalier){
      dec = rot_mode(dec, 45);
    } else {
      dec = rot_mode(dec, alterne_angle[i % 2]);
    }
  }

  MLV_actualise_window();
}

/* Fonction ayant pour but d'actualiser le plateau de manière graphique en prenant en compte la matrice*/
void actualise_plateau(Piece *board[][8], Coord pos, int *moves, int trajectoires){
  make_grid();
  color_piece(board);
  if(trajectoires){
    indic_deplace(board, pos, moves);
  }
}

/*GESTION DU CLIC*/

Coord clic_or_save(Piece *board[][8], Joueur jActuel, Montre *clock1, Montre *clock2, Montre clock_init, int *morts_w, int *morts_b, int *Save){
  Coord map;
  int x, y;
  int save_button = 0;
  x = -1;
  y = -1;
  /*Par défaut les coordonnées sont -1 et -1 pour correspondre a la boucle while de la fonction jeu qui permet un clic fluide et non statique durant le jeu*/
  map.x = x;
  map.y = y;

  /*On attend que l'utilisateur clique ou sauvegarde*/
  while(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_PRESSED && save_button == 0){

    /*On saisis la position de la souris en temps réel*/
    MLV_get_mouse_position(&map.x, &map.y);
    map.x /= CASE;
    map.y /= CASE;

    /*Si un des boutons de save est enfoncé alors la variable save_button vaut la valeur de la save_state choisie*/
    if(MLV_get_keyboard_state(MLV_KEYBOARD_AMPERSAND) == MLV_PRESSED){
      save_button = 1;
    }
    if(MLV_get_keyboard_state(MLV_KEYBOARD_WORLD_73) == MLV_PRESSED){
      save_button = 2;
    }
    if(MLV_get_keyboard_state(MLV_KEYBOARD_QUOTEDBL) == MLV_PRESSED){
      save_button = 3;
    }
    if(MLV_get_keyboard_state(MLV_KEYBOARD_QUOTE) == MLV_PRESSED){
      save_button = 4;
    }
    if(MLV_get_keyboard_state(MLV_KEYBOARD_LEFTPAREN) == MLV_PRESSED){
      save_button = 5;
    }
    if(MLV_get_keyboard_state(MLV_KEYBOARD_MINUS) == MLV_PRESSED){
      save_button = 6;
    }

    /*On met à jour le timer puis on l'affiche*/
    update_time(clock1, clock2, clock_init);
    draw_timer(clock1, jActuel);
  }

  /*On appelle la fonction de save en fonction de la variable save_button*/
  switch(save_button){
    case 1:
      save(board, jActuel, 1, morts_w, morts_b, clock1, clock2);
      Save[0] = 1;
      return map;
    case 2:
      save(board, jActuel, 2, morts_w, morts_b, clock1, clock2);
      Save[0] = 1;
      return map;
    case 3:
      save(board, jActuel, 3, morts_w, morts_b, clock1, clock2);
      Save[0] = 1;
      return map;
    case 4:
      save(board, jActuel, 4, morts_w, morts_b, clock1, clock2);
      Save[0] = 1;
      return map;
    case 5:
      save(board, jActuel, 5, morts_w, morts_b, clock1, clock2);
      Save[0] = 1;
      return map;
    case 6:
      save(board, jActuel, 6, morts_w, morts_b, clock1, clock2);
      Save[0] = 1;
      return map;
    default:
      break;
  }
  return map;
}

/*------Fonction affichant l'écran de fin de partie------*/

void screen_fin_partie(Joueur color){
  MLV_Font *font;
  MLV_create_window("fin", "fin", 400, 100);

  font = MLV_load_font("ressources/polices/police_anc.ttf", 40);
  switch (color){
    case 0: MLV_draw_text_with_font(35, 30, "Les Noirs gagnent", font, MLV_COLOR_RED2); break;
    case 1: MLV_draw_text_with_font(33, 30, "Les Blancs gagnent", font, MLV_COLOR_RED2); break;
    case 2: MLV_draw_text_with_font(30, 30, "Aucun coup légal, pat", font, MLV_COLOR_RED2); break;
  }

  MLV_actualise_window();
  MLV_wait_seconds(3);
  MLV_free_font(font);
  MLV_free_window();
}

/*------Fonction affichant le texte rappellant au joueur qu'il peut sauvegarder------*/

void affichage_save(){
  MLV_Font* font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", CASE/4);
  MLV_draw_text_with_font(CASE/4, CASE*8+CASE/5, "Press 1-6 to Save&Quit", font, MLV_COLOR_RED);
  MLV_actualise_window();
  MLV_free_font(font);
}

/*------Fonction affichant le leaderboard------*/

void aff_leaderboard(){
  MLV_Font* font;
  JLeaderboard Lead[10];
  char score[50];
  int i = 0;
  lecture_leaderboard(Lead);
  MLV_create_window("Leaderboard", "Leaderboard", 400, 800);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 30);
  while(i < 10 && Lead[i].score != -1){
    MLV_draw_text_with_font(10, 20+50*i, Lead[i].pseudo, font, MLV_COLOR_RED);
    sprintf(score, "%d", Lead[i].score);
    MLV_draw_text_with_font(300, 20+50*i, score, font, MLV_COLOR_RED);
    i++;
  }
  MLV_actualise_window();
  MLV_free_font(font);
  MLV_wait_mouse(NULL, NULL);
  MLV_free_window();
}

/*------Fonction permettant le choix de la save state------*/

int save_state(){
  int x, y, clic, choix;
  MLV_Font *font1, *font2;

  MLV_create_window("save_state", "save_state", 400, 800);
  font1 = MLV_load_font("ressources/polices/police_anc.ttf", 50);
  font2 = MLV_load_font("ressources/polices/police_anc.ttf", 55);

  choix = 1;
  clic = 0;
  while(!clic){
    MLV_clear_window(MLV_COLOR_BLACK);

    MLV_draw_text_with_font(130, 50, "Save 1", font1, MLV_COLOR_RED2);
    MLV_draw_text_with_font(130, 170, "Save 2", font1, MLV_COLOR_RED2);
    MLV_draw_text_with_font(130, 290, "Save 3", font1, MLV_COLOR_RED2);
    MLV_draw_text_with_font(130, 410, "Save 4", font1, MLV_COLOR_RED2);
    MLV_draw_text_with_font(130, 530, "Save 5", font1, MLV_COLOR_RED2);
    MLV_draw_text_with_font(130, 650, "Save 6", font1, MLV_COLOR_RED2);

    MLV_get_mouse_position(&x, &y);

    if(130 < x && x < 270){
      if(60 < y && y < 140){
        MLV_draw_text_with_font(127, 50, "Save 1", font2, MLV_COLOR_ORANGE);
        choix = 1;
      }
      if(180 < y && y < 240){
        MLV_draw_text_with_font(127, 170, "Save 2", font2, MLV_COLOR_ORANGE);
        choix = 2;
      }
      if(300 < y && y < 380){
        MLV_draw_text_with_font(127, 290, "Save 3", font2, MLV_COLOR_ORANGE);
        choix = 3;
      }
      if(420 < y && y < 500){
        MLV_draw_text_with_font(127, 410, "Save 4", font2, MLV_COLOR_ORANGE);
        choix = 4;
      }
      if(540 < y && y < 620){
        MLV_draw_text_with_font(127, 530, "Save 5", font2, MLV_COLOR_ORANGE);
        choix = 5;
      }
      if(660 < y && y < 740){
        MLV_draw_text_with_font(127, 650, "Save 6", font2, MLV_COLOR_ORANGE);
        choix = 6;
      }
      if(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED){
        clic++;
      }
    }
    MLV_actualise_window();
  }

  MLV_free_font(font1);
  MLV_free_font(font2);
  MLV_free_window();
  return choix;
  exit(0);
}

/*---Fonction permettant le choix de la pièce quand le pion peut se changer---*/

int choix_piece_pion(Joueur color){
  int x, y, clic, choix;
  MLV_Image *cava, *reine, *fou, *tour;
  MLV_Sound* transf_sound;
  transf_sound = MLV_load_sound("ressources/OST/changePion.wav");

  if(color){
    cava = MLV_load_image("ressources/pieces/cavaN.png");
    tour = MLV_load_image("ressources/pieces/tourN.png");
    reine = MLV_load_image("ressources/pieces/dameN.png");
    fou = MLV_load_image("ressources/pieces/fouN.png");
  }
  else{
    cava = MLV_load_image("ressources/pieces/cavaB.png");
    tour = MLV_load_image("ressources/pieces/tourB.png");
    reine = MLV_load_image("ressources/pieces/dameB.png");
    fou = MLV_load_image("ressources/pieces/fouB.png");
  }
  MLV_resize_image(cava, CASE*1.5, CASE*1.5);
  MLV_resize_image(tour, CASE*1.5, CASE*1.5);
  MLV_resize_image(reine, CASE*1.5, CASE*1.5);
  MLV_resize_image(fou, CASE*1.5, CASE*1.5);

  choix = 1;
  clic = 0;
  while(!clic){
    MLV_draw_filled_rectangle(CASE*1, CASE*2.5, CASE*6, CASE*3, MLV_COLOR_BLACK);

    MLV_get_mouse_position(&x, &y);
    if(CASE*3.25 < y && y < CASE*4.75){
      if(CASE*1.4 < x && x < CASE*2.6){
        choix = 4;
        MLV_draw_filled_rectangle(CASE*1.5, CASE*3.25, CASE*0.95, CASE*1.5, MLV_COLOR_RED);
      }
      if(CASE*2.8 < x && x < CASE*4){
        choix = 3;
        MLV_draw_filled_rectangle(CASE*2.9, CASE*3.25, CASE*0.91, CASE*1.5, MLV_COLOR_RED);
      }
      if(CASE*4.2 < x && x < CASE*5.4){
        choix = 1;
        MLV_draw_filled_rectangle(CASE*4.3, CASE*3.25, CASE*0.91, CASE*1.5, MLV_COLOR_RED);
      }
      if(CASE*5.6 < x && x < CASE*6.8){
        choix = 2;
        MLV_draw_filled_rectangle(CASE*5.7, CASE*3.25, CASE*0.91, CASE*1.5, MLV_COLOR_RED);
      }
      if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
        clic++;
      }
    }
    MLV_draw_image(cava, CASE*1.2, CASE*3.25);
    MLV_draw_image(fou, CASE*2.6, CASE*3.25);
    MLV_draw_image(reine, CASE*4, CASE*3.25);
    MLV_draw_image(tour, CASE*5.4, CASE*3.25);
    MLV_actualise_window();
  }
  MLV_free_image(cava);
  MLV_free_image(reine);
  MLV_free_image(tour);
  MLV_free_image(fou);
  MLV_play_sound(transf_sound, 0.5);
  return choix;
}

void draw_timer(Montre *clock, Joueur jActuel){
   MLV_Font *font;
   char montre[20];

   font = MLV_load_font("ressources/polices/police_anc.ttf", CASE/2);
   sprintf(montre, "%d:%02d:%02d", clock->h, clock->m, clock->s);
   if(jActuel){
     MLV_draw_filled_rectangle(CASE*6, CASE*8, CASE*2, CASE*0.7, MLV_COLOR_BLACK);
     MLV_draw_text_with_font(6*CASE, 8*CASE, montre, font, MLV_COLOR_RED);
   }
   else{
     MLV_draw_filled_rectangle(CASE*4, CASE*8, CASE*2, CASE*0.7, MLV_COLOR_BLACK);
     MLV_draw_text_with_font(4*CASE, 8*CASE, montre, font, MLV_COLOR_RED);
   }
   MLV_actualise_window();
   MLV_free_font(font);
}

void actualise_morts(int *morts_w, int *morts_b){
  int i;
  MLV_Image *cava, *reine, *fou, *tour, *pion;

  cava = MLV_load_image("ressources/pieces/cavaN.png");
  tour = MLV_load_image("ressources/pieces/tourN.png");
  reine = MLV_load_image("ressources/pieces/dameN.png");
  fou = MLV_load_image("ressources/pieces/fouN.png");
  pion = MLV_load_image("ressources/pieces/pionN.png");
  MLV_resize_image(cava, CASE*0.5, CASE*0.5);
  MLV_resize_image(tour, CASE*0.5, CASE*0.5);
  MLV_resize_image(reine, CASE*0.5, CASE*0.5);
  MLV_resize_image(fou, CASE*0.5, CASE*0.5);
  MLV_resize_image(pion, CASE*0.5, CASE*0.5);

  for(i = 1; i < morts_b[0]+1; i++){
    if(morts_b[i] == 1){
      MLV_draw_image(reine, i*CASE*0.5-CASE*0.4, CASE*8.7);
    }
    if(morts_b[i] == 2){
      MLV_draw_image(tour, i*CASE*0.5-CASE*0.4, CASE*8.7);
    }
    if(morts_b[i] == 3){
      MLV_draw_image(fou, i*CASE*0.5-CASE*0.4, CASE*8.7);
    }
    if(morts_b[i] == 4){
      MLV_draw_image(cava, i*CASE*0.5-CASE*0.4, CASE*8.7);
    }
    if(morts_b[i] == 5){
      MLV_draw_image(pion, i*CASE*0.5-CASE*0.4, CASE*8.7);
    }
  }
  cava = MLV_load_image("ressources/pieces/cavaB.png");
  tour = MLV_load_image("ressources/pieces/tourB.png");
  reine = MLV_load_image("ressources/pieces/dameB.png");
  fou = MLV_load_image("ressources/pieces/fouB.png");
  pion = MLV_load_image("ressources/pieces/pionB.png");
  MLV_resize_image(cava, CASE*0.5, CASE*0.5);
  MLV_resize_image(tour, CASE*0.5, CASE*0.5);
  MLV_resize_image(reine, CASE*0.5, CASE*0.5);
  MLV_resize_image(fou, CASE*0.5, CASE*0.5);
  MLV_resize_image(pion, CASE*0.5, CASE*0.5);

  for(i = 1; i < morts_w[0]+1; i++){
    if(morts_w[i] == 1){
      MLV_draw_image(reine, i*CASE*0.5-CASE*0.4, CASE*9.3);
    }
    if(morts_w[i] == 2){
      MLV_draw_image(tour, i*CASE*0.5-CASE*0.4, CASE*9.3);
    }
    if(morts_w[i] == 3){
      MLV_draw_image(fou, i*CASE*0.5-CASE*0.4, CASE*9.3);
    }
    if(morts_w[i] == 4){
      MLV_draw_image(cava, i*CASE*0.5-CASE*0.4, CASE*9.3);
    }
    if(morts_w[i] == 5){
      MLV_draw_image(pion, i*CASE*0.5-CASE*0.4, CASE*9.3);
    }
  }

  MLV_free_image(cava);
  MLV_free_image(reine);
  MLV_free_image(tour);
  MLV_free_image(fou);
  MLV_free_image(pion);
}

void dessiner_pieces(int emplacement){
  MLV_Image *cava, *reine, *fou, *tour, *roi, *pion, *cross;

  MLV_draw_filled_rectangle(CASE, CASE*8, CASE*8, CASE*2, MLV_COLOR_BLACK);
  if(emplacement < 13){
    MLV_draw_filled_rectangle(CASE+CASE*(emplacement%6), CASE*8+(emplacement/6)*CASE, CASE, CASE, MLV_COLOR_RED);
  }
  else{
    MLV_draw_rectangle(CASE*7, CASE*8.5, CASE, CASE, MLV_COLOR_RED);
  }
  cross = MLV_load_image("ressources/assets/cross.png");
  roi = MLV_load_image("ressources/pieces/roiN.png");
  reine = MLV_load_image("ressources/pieces/dameN.png");
  tour = MLV_load_image("ressources/pieces/tourN.png");
  fou = MLV_load_image("ressources/pieces/fouN.png");
  cava = MLV_load_image("ressources/pieces/cavaN.png");
  pion = MLV_load_image("ressources/pieces/pionN.png");
  MLV_resize_image(cross, CASE, CASE);
  MLV_resize_image(roi, CASE, CASE);
  MLV_resize_image(reine, CASE, CASE);
  MLV_resize_image(tour, CASE, CASE);
  MLV_resize_image(fou, CASE, CASE);
  MLV_resize_image(cava, CASE, CASE);
  MLV_resize_image(pion, CASE, CASE);
  MLV_draw_image(roi, CASE, CASE*8);
  MLV_draw_image(reine, CASE*2, CASE*8);
  MLV_draw_image(tour, CASE*3, CASE*8);
  MLV_draw_image(fou, CASE*4, CASE*8);
  MLV_draw_image(cava, CASE*5, CASE*8);
  MLV_draw_image(pion, CASE*6, CASE*8);
  MLV_draw_image(cross, CASE*7, CASE*8.5);


  roi = MLV_load_image("ressources/pieces/roiB.png");
  reine = MLV_load_image("ressources/pieces/dameB.png");
  tour = MLV_load_image("ressources/pieces/tourB.png");
  fou = MLV_load_image("ressources/pieces/fouB.png");
  cava = MLV_load_image("ressources/pieces/cavaB.png");
  pion = MLV_load_image("ressources/pieces/pionB.png");
  MLV_resize_image(roi, CASE, CASE);
  MLV_resize_image(reine, CASE, CASE);
  MLV_resize_image(tour, CASE, CASE);
  MLV_resize_image(fou, CASE, CASE);
  MLV_resize_image(cava, CASE, CASE);
  MLV_resize_image(pion, CASE, CASE);
  MLV_draw_image(roi, CASE, CASE*9);
  MLV_draw_image(reine, CASE*2, CASE*9);
  MLV_draw_image(tour, CASE*3, CASE*9);
  MLV_draw_image(fou, CASE*4, CASE*9);
  MLV_draw_image(cava, CASE*5, CASE*9);
  MLV_draw_image(pion, CASE*6, CASE*9);
}
