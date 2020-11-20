#include "assets.h"

void init_plateau(Piece *board[][8], Piece pieces[32]){
	vider_plateau(board);
	placer_pieces(board, pieces);
	init_pieces(board);
	init_deplacement(pieces);
}

void vider_plateau(Piece *board[][8]){
	int i,j;

	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			board[i][j] = NULL;
		}
	}
}

void placer_pieces(Piece *board[][8], Piece pieces[32]){
	int i;
	for(i = 0; i < 32; i++){
		pieces[i].nbMouv = 0;
		pieces[i].estVivant.val = TRUE;

		if(i < 16){
			pieces[i].couleur = Noir;
			board[i/8][i%8] = &pieces[i];
		} else {
			pieces[i].couleur = Blanc;
			board[i/8 + 4][i%8] = &pieces[i];
		}
	}
}

void init_pieces(Piece *board[][8]){
	int color, i, j;
	TypePiece rangee[] = {Tour, Cavalier, Fou, Reine, Roi, Fou, Cavalier, Tour};

	for(color = 0; color < 2; color++){
		for(i = 0; i < 8; i++){
			board[0 + color * 7][i]->rang = rangee[i];
		}

		for(j = 0; j < 8; j++){
			board[1 + color * 5][j]->rang = Pion;
		}
	}
}

void init_deplacement(Piece pieces[32]){
	int i;
	for(i = 0; i < 32; i++){
		switch(pieces[i].rang){
			case Roi: deplace_roi(&pieces[i]);break;
			case Reine: deplace_reine(&pieces[i]);break;
			case Tour: deplace_tour(&pieces[i]);break;
			case Fou: deplace_fou(&pieces[i]);break;
			case Cavalier: deplace_cavalier(&pieces[i]);break;
			case Pion: deplace_pion(&pieces[i]);break;
		}
	}
}

void deplace_roi(Piece *pieceptr){
	pieceptr->move.droit.val = TRUE;
	pieceptr->move.diagonal.val = TRUE;
	pieceptr->move.formeL.val = FALSE;
	pieceptr->move.limitation = 1;
	pieceptr->move.ajustement[0] = 0;
	pieceptr->move.ajustement[1] = 'r';
}

void deplace_reine(Piece *pieceptr){
	pieceptr->move.droit.val = TRUE;
	pieceptr->move.diagonal.val = TRUE;
	pieceptr->move.formeL.val = FALSE;
	pieceptr->move.limitation = 8;
	pieceptr->move.ajustement[0] = 0;
	pieceptr->move.ajustement[1] = '\0';
}

void deplace_tour(Piece *pieceptr){
	pieceptr->move.droit.val = TRUE;
	pieceptr->move.diagonal.val = FALSE;
	pieceptr->move.formeL.val = FALSE;
	pieceptr->move.limitation = 8;
	pieceptr->move.ajustement[0] = 0;
	pieceptr->move.ajustement[1] = '\0';
}

void deplace_fou(Piece *pieceptr){
	pieceptr->move.droit.val = FALSE;
	pieceptr->move.diagonal.val = TRUE;
	pieceptr->move.formeL.val = FALSE;
	pieceptr->move.limitation = 8;
	pieceptr->move.ajustement[0] = 0;
	pieceptr->move.ajustement[1] = '\0';
}

void deplace_cavalier(Piece *pieceptr){
	pieceptr->move.droit.val = FALSE;
	pieceptr->move.diagonal.val = FALSE;
	pieceptr->move.formeL.val = TRUE;
	pieceptr->move.limitation = 0;
	pieceptr->move.ajustement[0] = 0;
	pieceptr->move.ajustement[1] = '\0';
}

void deplace_pion(Piece *pieceptr){
	pieceptr->move.droit.val = FALSE;
	pieceptr->move.diagonal.val = FALSE;
	pieceptr->move.formeL.val = FALSE;
	pieceptr->move.limitation = 0;
	pieceptr->move.ajustement[0] = 2;
	pieceptr->move.ajustement[1] = 'p';
}
