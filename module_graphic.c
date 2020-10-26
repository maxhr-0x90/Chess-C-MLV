#include "assets.h"

/* Fonction ayant pour but de dessiner le damier de l'échiquier*/
void make_grid(){
  int x, y;
  for(y = 0; y < 8; y++)
    for(x = 0; x < 8; x++){
      MLV_draw_filled_rectangle( x*200, y*200, 100, 100, MLV_COLOR_WHITE);
      MLV_draw_filled_rectangle( 100+x*200, 100+y*200, 100, 100, MLV_COLOR_WHITE);
      MLV_draw_filled_rectangle( 100+x*200, y*200, 100, 100, MLV_COLOR_GREY15);
      MLV_draw_filled_rectangle( x*200, 100+y*200, 100, 100, MLV_COLOR_GREY15);
    }
  MLV_actualise_window();
}

/* Fonction ayant pour but de placer les pièces de  manière graphique et pour le moins provisoire*/
/* Sur le plateau.*/
void color_piece(Piece *board[8][8]){
  int i, j;
  MLV_Font* police = MLV_load_font("DejaVuSans.ttf", 60);
  char echecs[9][5] = {"R", "Re", "T", "F", "C", "P"};

  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++)
      if(board[i][j] != NULL)
        printf("%d\n", board[i][j]->rang);

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++)
      if(board[i][j] != NULL){
        printf("%d\n", board[i][j]->rang);
        MLV_draw_text_with_font(15+j*100, 10+i*100, echecs[board[i][j]->rang], police, MLV_COLOR_BLACK);
    }
    printf("\n");
  }
  MLV_actualise_window();
}

/* Fonction ayant pour but d'actualiser le plateau de manière graphique en prenant en compte la matrice*/
void actualise_plateau(Piece *board[8][8]){
  make_grid();
  color_piece(board);
}
