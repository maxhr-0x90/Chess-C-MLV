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
	char path[25];
	char *folder = "ressources/";
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

Coord clic_or_save(Piece *board[][8], Joueur jActuel){
  Coord map;
  int x, y;
  int touche;
  x = -1;
  y = -1;
  map.x = x;
  map.y = y;
  touche = ' ';
  while(en_dehors(map) && touche != 's'){
    MLV_wait_keyboard_or_mouse( NULL, NULL, &touche, &x, &y);

    map.x = x/CASE;
    map.y = y/CASE;
  }
  switch(touche){
    case '1':
      save(board, jActuel, 1);
      exit(0);
      break;
    case '2':
      save(board, jActuel, 2);
      exit(0);
      break;
    case '3':
      save(board, jActuel, 3);
      exit(0);
      break;
    case '4':
      save(board, jActuel, 4);
      exit(0);
      break;
    case '5':
      save(board, jActuel, 5);
      exit(0);
      break;
    case '6':
      save(board, jActuel, 6);
      exit(0);
      break;
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
    if(color){
      MLV_draw_text_with_font(33, 30, "Les Blancs gagnent", font, MLV_COLOR_RED2);
    }
    else{
      MLV_draw_text_with_font(35, 30, "Les Noirs gagnent", font, MLV_COLOR_RED2);
    }
    MLV_actualise_window();
    MLV_wait_seconds(3);
    MLV_free_font(font);
    MLV_free_window();
}

/*------Fonction affichant le texte rappellant au joueur qu'il peut sauvegarder------*/

void affichage_save(){
  MLV_Font* font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", CASE/2);
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
  MLV_create_window("Leaderboard", "Leaderboard", 4*CASE, 8*CASE);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 30);
  do{
    MLV_draw_text_with_font(10, 20+50*i, Lead[i].pseudo, font, MLV_COLOR_RED);
    sprintf(score, "%d", Lead[i].score);
    MLV_draw_text_with_font(200, 20+50*i, score, font, MLV_COLOR_RED);
    i++;
  }while(Lead[i].score != -1 && i != 10);
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
  printf("%d\n", choix);
  return choix;
  exit(0);
}

/*---Fonction permettant le choix de la pièce quand le pion peut se changer---*/

int choix_piece_pion(Joueur color){
  int x, y, clic, choix;
  MLV_Image *cava, *reine, *fou, *tour;

  if(color){
    cava = MLV_load_image("ressources/cavaN.png");
    tour = MLV_load_image("ressources/tourN.png");
    reine = MLV_load_image("ressources/dameN.png");
    fou = MLV_load_image("ressources/fouN.png");
  }
  else{
    cava = MLV_load_image("ressources/cavaB.png");
    tour = MLV_load_image("ressources/tourB.png");
    reine = MLV_load_image("ressources/dameB.png");
    fou = MLV_load_image("ressources/fouB.png");
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
  return choix;
}
