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

void indic_deplace(Coord pos, int *moves){
  int i, j, swp;
  Coord dec = {0, -1};
  for (i = 0; i < 8; i++) {
    if(!moves[8]){
      for (j = 1; j <= moves[i]; j++) {
        MLV_draw_filled_circle(CASE*(dec.x*j + pos.x)+CASE/2, CASE*(dec.y*j + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
      }
    } else if (moves[8] && moves[i] != -1 && moves[i] != 0){
      MLV_draw_filled_circle(CASE*(dec.x*moves[i] + pos.x)+CASE/2, CASE*(dec.y*moves[i] + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
    }
    swp = dec.x;
    dec.x = sgn(swp - dec.y);
    dec.y = sgn(swp + dec.y);
  }

  dec.x = 1;
  dec.y = -2;
  for (i = 0; i < 8; i+=2) {
    if (moves[i] == -1) {
      MLV_draw_filled_circle(CASE*(dec.x + pos.x)+CASE/2, CASE*(dec.y + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
    }
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }

  dec.x = 2;
  dec.y = -1;
  for (i = 1; i < 8; i+=2) {
    if (moves[i] == -1) {
      MLV_draw_filled_circle(CASE*(dec.x + pos.x)+CASE/2, CASE*(dec.y + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
    }
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }

  MLV_actualise_window();
}

/* Fonction ayant pour but d'actualiser le plateau de manière graphique en prenant en compte la matrice*/
void actualise_plateau(Piece *board[][8], Coord pos, int *moves, int trajectoires){
  make_grid();
  color_piece(board);
  if(trajectoires){
    indic_deplace(pos, moves);
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
  if(touche == 's'){
    save(board, jActuel);
    exit(0);
  }
  return map;
}

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

void affichage_save(){
  MLV_Font* font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", CASE/2);
  MLV_draw_text_with_font(CASE/4, CASE*8+CASE/5, "Press S to Save&Quit", font, MLV_COLOR_RED);
  MLV_actualise_window();
  MLV_free_font(font);
}

void aff_leaderboard(){
  MLV_Font* font;
  JLeaderboard Lead[10];
  char score[50];
  int i = 0;
  lecture_leaderboard(Lead);
  MLV_create_window("Leaderboard", "Leaderboard", 4*CASE, 8*CASE);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 30);
  while(Lead[i].score != -1 && i != 10){
    MLV_draw_text_with_font(10, 20+50*i, Lead[i].pseudo, font, MLV_COLOR_RED);
    sprintf(score, "%d", Lead[i].score);
    MLV_draw_text_with_font(200, 20+50*i, score, font, MLV_COLOR_RED);
    i++;
  }
  MLV_actualise_window();
  MLV_free_font(font);
  MLV_wait_mouse(NULL, NULL);
  MLV_free_window();
}
