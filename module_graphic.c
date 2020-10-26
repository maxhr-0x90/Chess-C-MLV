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
  MLV_Font* police = MLV_load_font("DejaVuSans.ttf", CASE/2);
  char echecs[9][5] = {"R", "Re", "T", "F", "C", "P"};

  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++)
      if(board[i][j] != NULL)
        MLV_draw_text_with_font(CASE/7+j*CASE, CASE/10+i*CASE, echecs[board[i][j]->rang], police, MLV_COLOR_BLACK);
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
