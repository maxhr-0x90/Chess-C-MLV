#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>

#define CASE 96

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
	unsigned char nbMouv;
	Bool estVivant;
	Deplacement move;
} Piece;

typedef struct
{
	Piece *echiquier[8][8];
	Joueur jActuel;
} Config;

typedef struct
{
	int x;
	int y;
} Coord;

/*--------------------Module de vérification-----------------------*/

int est_piece(Piece *board[][8], Coord pos);
int est_legal(Piece *board[][8], Coord pos, Coord target);
void formeL_possible(Piece *board[][8], Coord pos, int *moves);
void droit_possible(Piece *board[][8], Coord pos, int *moves);
void diagonal_possible(Piece *board[][8], Coord pos, int *moves);
void ajustement_p_possible(Piece *board[][8], Coord pos, int *moves);
void moves_possible(Piece *board[][8], Coord pos, int *moves);
int est_mortel(Piece *board[][8], Coord pos, unsigned int color);
int est_echec(Piece *board[][8], unsigned int color);

/*-----------------------Module graphique--------------------------*/

void make_grid();
void color_piece();
void indic_deplace(Coord pos, int *moves);
void actualise_plateau(Piece *board[][8], Coord pos, int *moves);
Coord clic();

/*--------------------Module d'initialisation----------------------*/

void init_plateau(Piece *board[][8], Piece pieces[32]);
void vider_plateau(Piece *board[][8]);
void placer_pieces(Piece *board[][8], Piece pieces[32]);
void init_pieces(Piece *board[][8]);
void init_deplacement(Piece pieces[32]);

/*fonctions d'initialisation des déplacements*/
/**/void deplace_roi(Piece *pieceptr);
/**/void deplace_reine(Piece *pieceptr);
/**/void deplace_tour(Piece *pieceptr);
/**/void deplace_fou(Piece *pieceptr);
/**/void deplace_cavalier(Piece *pieceptr);
/**/void deplace_pion(Piece *pieceptr);
