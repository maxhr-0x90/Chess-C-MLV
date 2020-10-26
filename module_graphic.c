#include "assets.h"

/*GESTION DE L'AFFICHAGE*/

/* Fonction ayant pour but de dessiner le damier de l'échiquier*/
void make_grid(){
  int x, y;
  MLV_draw_filled_rectangle(0, 0, CASE*8, CASE*8, MLV_COLOR_GREY15);
  for(y = 0; y < 8; y++)
    for(x = 0; x < 8; x++){
      MLV_draw_filled_rectangle( x*CASE*2, y*CASE*2, CASE, CASE, MLV_COLOR_WHITE);
      MLV_draw_filled_rectangle( CASE+x*CASE*2, CASE+y*CASE*2, CASE, CASE, MLV_COLOR_WHITE);
    }
}

/* Fonction ayant pour but de placer les pièces de manière graphique sur le plateau.*/
void color_piece(Piece *board[][8]){
  int i, j;
	char path[25];
	char *folder = "ressources/";
	char *ext = ".png";
	char images_tab[][5] = {"roi", "dame", "tour", "fou", "cava", "pion"};
	MLV_Image *image;

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
				strcpy(path, folder);
				strcat(path, images_tab[board[i][j]->rang]);
				strcat(path, ext);
				image = MLV_load_image(path);

        MLV_draw_image(image, CASE*j, CASE*i);
				path[0] = '\0';
			}
		}
	}
  MLV_actualise_window();
}

/* Fonction ayant pour but d'actualiser le plateau de manière graphique en prenant en compte la matrice*/
void actualise_plateau(Piece *board[][8]){
  make_grid();
  color_piece(board);
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
