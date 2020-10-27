#include "assets.h"

/*GESTION DE L'AFFICHAGE*/

/* Fonction ayant pour but de dessiner le damier de l'échiquier*/
void make_grid(){
  int x, y;
  MLV_draw_filled_rectangle(0, 0, 8*CASE, 8*CASE, MLV_COLOR_BLACK);
  for(y = 0; y < 8; y++)
    for(x = 0; x < 8; x++){
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

        MLV_draw_image(image, CASE*j, CASE*i);
				path[0] = '\0';
			}
		}
	}
  MLV_actualise_window();
}

int sgn(int i){
  if (i > 0) {
    return 1;
  } else if (i < 0) {
    return -1;
  } else {
    return 0;
  }
}

void indic_deplace(Coord pos, int *moves){
  int i, j, swp;
  Coord dec = {0, -1};
  for (i = 0; i < 8; i++) {
    for (j = 1; j <= moves[i]; j++) {
      MLV_draw_filled_circle(CASE*(dec.x*j + pos.x)+CASE/2, CASE*(dec.y*j + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
    }
    swp = dec.x;
    dec.x = sgn(swp - dec.y);
    dec.y = sgn(swp + dec.y);
  }

  dec.x = 1;
  dec.y = -2;
  for (i = 0; i < 8; i+=2) {
    if (moves[i] == -1) {
      MLV_draw_filled_circle(CASE*(dec.x*j + pos.x)+CASE/2, CASE*(dec.y*j + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
    }
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }

  dec.x = 2;
  dec.y = -1;
  for (i = 1; i < 8; i+=2) {
    if (moves[i] == -1) {
      MLV_draw_filled_circle(CASE*(dec.x*j + pos.x)+CASE/2, CASE*(dec.y*j + pos.y)+CASE/2, CASE/6, MLV_rgba(63, 238, 63, 150));
    }
    swp = dec.x;
    dec.x = -dec.y;
    dec.y = swp;
  }

  MLV_actualise_window();
}

/* Fonction ayant pour but d'actualiser le plateau de manière graphique en prenant en compte la matrice*/
void actualise_plateau(Piece *board[][8], Coord pos, int *moves){
  make_grid();
  color_piece(board);
  indic_deplace(pos, moves);
}

/*GESTION DU CLIC*/

Coord clic(){
  Coord map;
  int x, y;
  MLV_wait_mouse(&x, &y);

  map.x = x/CASE;
  map.y = y/CASE;
  return map;
}
