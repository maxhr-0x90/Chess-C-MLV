#include "assets.h"

Coord editor_clic(){
  Coord pos;
  MLV_wait_mouse(&pos.x, &pos.y);
  return pos;
}

int presence_roi(Piece *board[][8], Joueur color){
  int i, j, nb_roi = 0;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL && board[i][j]->rang == Roi && board[i][j]->couleur == color){
        nb_roi++;
      }
    }
  }
  return nb_roi;
}

int analyse_editor_clic_1(Coord pos, int act_choix){
  int x = pos.x, y = pos.y, piece_choisie;
  if(y > CASE*8 && CASE < x && x < CASE*7){
    if(CASE < x && x < CASE*2){
      piece_choisie = 0;
    }
    if(CASE*2 < x && x < CASE*3){
      piece_choisie = 1;
    }
    if(CASE*3 < x && x < CASE*4){
      piece_choisie = 2;
    }
    if(CASE*4 < x && x < CASE*5){
      piece_choisie = 3;
    }
    if(CASE*5 < x && x < CASE*6){
      piece_choisie = 4;
    }
    if(CASE*6 < x && x < CASE*7){
      piece_choisie = 5;
    }
    if(CASE*9 < y && y < CASE*10){
      piece_choisie += 6;
    }
    return piece_choisie;
  }
  return act_choix;
}

void analyse_editor_clic_2(Piece *board[][8], Piece *set_pieces, Coord pos, int choix){
  Joueur Jmodif = choix < 6;
  Piece nvPiece;
  int i = 0, x = pos.x/CASE, y = pos.y/CASE;
  if(pos.y < CASE*8){
    while(set_pieces[i].couleur != Nulle){
      i++;
    }
    if(presence_roi(board, Jmodif) != 1){
      if(board[y][x] == NULL){
        nvPiece.rang = choix%6;
        nvPiece.couleur = Jmodif;
        set_pieces[i] = nvPiece;
        board[y][x] = &set_pieces[i];
      }
      else{
        board[y][x]->rang = choix%6;
        nvPiece.couleur = Jmodif;
      }
    }
    else{
      if(choix%6 != 0){
        if(board[y][x] == NULL){
          nvPiece.rang = choix%6;
          nvPiece.couleur = Jmodif;
          set_pieces[i] = nvPiece;
          board[y][x] = &set_pieces[i];
        }
        else{
          board[y][x]->rang = choix%6;
          nvPiece.couleur = Jmodif;
        }
      }
    }
  }
}



void dessiner_pieces(int emplacement){
  MLV_Image *cava, *reine, *fou, *tour, *roi, *pion, *cross;

  MLV_draw_filled_rectangle(CASE, CASE*8, CASE*6, CASE*2, MLV_COLOR_BLACK);
  MLV_draw_filled_rectangle(CASE+CASE*(emplacement%6), CASE*8+(emplacement/6)*CASE, CASE, CASE, MLV_COLOR_RED);

  roi = MLV_load_image("ressources/assets/cross.png");
  roi = MLV_load_image("ressources/pieces/roiN.png");
  reine = MLV_load_image("ressources/pieces/dameN.png");
  tour = MLV_load_image("ressources/pieces/tourN.png");
  fou = MLV_load_image("ressources/pieces/fouN.png");
  cava = MLV_load_image("ressources/pieces/cavaN.png");
  pion = MLV_load_image("ressources/pieces/pionN.png");
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

void editor(Piece *board[][8], Piece *set_pieces){
  int i, j, piece_choisie = 0;
  Piece nul;
  Coord pos;
  for(i = 0; i < 64; i++){
    nul.couleur = Nulle;
    set_pieces[i] = nul;
  }
  MLV_create_window("editor_mod", "editor_mod", CASE*8, CASE*10);
  dessiner_pieces(piece_choisie);
  vider_plateau(board);
  make_grid();
  MLV_actualise_window();
  while(1){
    pos = editor_clic();
    piece_choisie = analyse_editor_clic_1(pos, piece_choisie);
    analyse_editor_clic_2(board, set_pieces, pos, piece_choisie);
    dessiner_pieces(piece_choisie);
    make_grid();
    /*
    for(i = 0; i < 8; i++){
      for(j = 0; j < 8; j++){
        if(board[i][j] != NULL){
          printf("%d ", board[i][j]->rang);
        }
        else{
          printf("N ");
        }
      }
      printf("\n");
    }
    */
    color_piece(board);
  }
  MLV_wait_seconds(3);
  exit(0);
}
