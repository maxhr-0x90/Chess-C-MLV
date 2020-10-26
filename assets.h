#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

/*-------------------Définitions de types------------------------*/

typedef enum{Blanc, Noir} Joueur;
typedef enum{Roi, Reine, Tour, Fou, Cavalier, Pion} TypePiece;

typedef struct
{
	unsigned char val;
} Bool;

typedef struct
{
	Bool droit;
	Bool diagonal;
	Bool formeL;
	char limitation;
	char ajustement[2];
} Deplacement;

typedef struct
{
	TypePiece rang;
	Joueur couleur;
	Bool posInit;
	Bool estVivant;
	Deplacement move;
} Piece;

typedef struct
{
	Piece *echiquier[8][8];
	Joueur jActuel;
} Config;

/*--------------------Module de vérification-----------------------*/


/*-----------------------Module graphique--------------------------*/

void make_grid();
void color_piece();
void actualise_plateau(Piece *board[][8]);

/*--------------------Module d'initialisation----------------------*/

void init_plateau(Piece *board[8][8], Piece pieces[32]);
void vider_plateau(Piece *board[8][8]);
void placer_pieces(Piece *board[8][8], Piece pieces[32]);
void init_pieces(Piece *board[8][8]);
