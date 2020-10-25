#include <stdio.h>
#include <stdlib.h>

typedef enum{Blanc, Noir} Joueur;
typedef enum{Roi, Dame, Tour, Fou, Cavalier, Pion} TypePiece;

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
