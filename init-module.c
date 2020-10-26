#include "assets.h"

void init_plateau(Piece *board[8][8]){
	Piece set_piece[32];
	vider_plateau(board);
	placer_pieces(board, set_piece);
	init_pieces(board);
}

void vider_plateau(Piece *board[8][8]){
	int i,j;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			board[i][j] = NULL;
		}
	}
}

void placer_pieces(Piece *board[8][8], Piece pieces[32]){
	int i;
	for(i = 0; i < 32; i++){
		pieces[i].posInit = 1;
		pieces[i].estVivant = 1;

		if(i < 16){
			pieces[i].couleur = Noir;
			board[i/8][i] = &pieces[i];
		} else {
			pieces[i].couleur = Blanc;
			board[i/8 + 6][i] = &pieces[i];
		}
	}
}

void init_pieces(Piece *board[8][8]){
	int color, i;
	TypePiece rangee[8] = {Tour, Cavalier, Fou, Roi, Reine, Fou, Cavalier, Tour};
	for(color = 0; color < 2; color++){
		for(i = 0; i < 8; i++){
			board[0 + color * 7][i]->rang = rangee[8];
		}

		for(i = 0; i < 8; i++){
			board[1 + color * 6][i]->rang = Pion;
		}
	}
}
