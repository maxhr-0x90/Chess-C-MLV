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

int analyse_choix(Coord pos, int act_choix){
  int x = pos.x, y = pos.y, piece_choisie;
  if(CASE*8.6 < y && y < CASE*9.5 && 0 < x && x < CASE){
    return 14;
  }
  if(CASE*8.5 < y && y < CASE*9.5 && CASE*7 < x && x < CASE*8){
    return 13;
  }
  if(CASE*8 < y && y < CASE*10 && CASE < x && x < CASE*7){
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

void analyse_clic_plateau(Piece *board[][8], Piece *set_pieces, Coord pos, int choix){
  Joueur Jmodif = choix < 6;
  Piece nvPiece;
  int i = 0, x = pos.x/CASE, y = pos.y/CASE, assign = 0;

  if(pos.y < CASE*8 && choix != 13){
    if(presence_roi(board, Jmodif) != 1){
      nvPiece.rang = choix%6;
      nvPiece.couleur = Jmodif;
      assign = 1;
    }
    else{
      if(choix%6 != 0){
        nvPiece.rang = choix%6;
        nvPiece.couleur = Jmodif;
        assign = 1;
      }
    }

    /*initialise la pièce dans le plateau si toutefois le joueur à choisi une pièce (en fonction de ton rang)*/
    if(assign){
      switch(nvPiece.rang){
        case Roi:
          deplace_roi(&nvPiece);
          break;
        case Reine:
          deplace_reine(&nvPiece);
          break;
        case Tour:
          deplace_tour(&nvPiece);
          break;
        case Cavalier:
          deplace_cavalier(&nvPiece);
          break;
        case Fou:
          deplace_fou(&nvPiece);
          break;
        case Pion:
          deplace_pion(&nvPiece);
          break;
      }
      if(board[y][x] != NULL){
        board[y][x]->rang = nvPiece.rang;
        board[y][x]->couleur = nvPiece.couleur;
        board[y][x]->move = nvPiece.move;
      } else {
        while(set_pieces[i].couleur != Nulle){
          i++;
        }
        set_pieces[i] = nvPiece;
        board[y][x] = &set_pieces[i];
      }
    }
  }
  else{
    if(y < 8){
      if(board[y][x] != NULL){
        board[y][x]->couleur = Nulle;
        board[y][x] = NULL;
      }
    }
  }
}

/*Fonction principale du mode editor*/
void editor(Piece *board[][8], Piece *set_pieces){
  int i, piece_choisie = 0, sortie = 0;
  Piece nul;
  Coord pos;
  MLV_Font *font;

  for(i = 0; i < 64; i++){
    nul.couleur = Nulle;
    set_pieces[i] = nul;
  }
  MLV_create_window("editor_mod", "editor_mod", CASE*8, CASE*10.5);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 20);
  MLV_draw_text_with_font(CASE*1.4, CASE*10, "To save and play, click on OK", font, MLV_COLOR_RED);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 40);
  MLV_draw_text_with_font(CASE*0.1, CASE*8.6, "OK", font, MLV_COLOR_GREEN);
  
  MLV_free_font(font);

  dessiner_pieces(piece_choisie);
  vider_plateau(board);
  make_grid();
  MLV_actualise_window();

  while(!sortie){
    pos = editor_clic();
    piece_choisie = analyse_choix(pos, piece_choisie);

    if(piece_choisie < 14){
      analyse_clic_plateau(board, set_pieces, pos, piece_choisie);
      dessiner_pieces(piece_choisie);
      make_grid();
      color_piece(board);
    }
    else{
      if(presence_roi(board, Noir) && presence_roi(board, Blanc) && !est_echec(board, Noir) && !est_echec(board, Blanc)){
        sortie = 1;
      }
    }
  }
  MLV_free_window();
}
