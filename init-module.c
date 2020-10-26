#include "assets.h"

void init_plateau(Piece *board[8][8], Piece pieces[32]){
	int i;
	vider_plateau(board);
	placer_pieces(board, pieces);
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
		pieces[i].posInit.val = 1;
		pieces[i].estVivant.val = 1;

		if(i < 16){
			pieces[i].couleur = Noir;
			board[i/8][i%8] = &pieces[i];
		} else {
			pieces[i].couleur = Blanc;
			board[i/8 + 4][i%8] = &pieces[i];
		}
	}
}

void init_pieces(Piece *board[8][8]){
	int color, i, j;
	TypePiece rangee[] = {Tour, Cavalier, Fou, Roi, Reine, Fou, Cavalier, Tour};

	for(color = 0; color < 2; color++){
		for(i = 0; i < 8; i++){
			board[0 + color * 7][i]->rang = rangee[i];
		}

		for(j = 0; j < 8; j++){
			board[1 + color * 5][j]->rang = Pion;
		}
	}

}
