#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include <time.h>

#define CASE 75

#define TRUE 1
#define FALSE 0

/*-------------------Définitions de types------------------------*/

typedef enum{Blanc, Noir, Nulle} Joueur;
typedef enum{Roi, Reine, Tour, Fou, Cavalier, Pion} TypePiece;
typedef enum{Play, Editor, Load, Quit, Leaderboard} ChoixMenu;

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

typedef struct
{
	int score;
	char pseudo[50];
} JLeaderboard;

typedef struct
{
	int h;
	int m;
	int s;
} Montre;

/*----------------------Module mathématique------------------------*/
int sgn(int i);
Coord rotation(Coord vect, float mat_rot[]);
Coord rot_mode(Coord vect, char mode);

/*--------------------Module de vérification-----------------------*/

int est_piece(Piece *board[][8], Coord pos);
void formeL_possible(Piece *board[][8], Coord pos, int *moves);
void droit_possible(Piece *board[][8], Coord pos, int *moves);
void diagonal_possible(Piece *board[][8], Coord pos, int *moves);
void ajustement_p_possible(Piece *board[][8], Coord pos, int *moves);
void ajustement_r_possible(Piece *board[][8], Coord pos, int *moves);
int en_dehors(Coord pos);
void moves_possibles(Piece *board[][8], Coord pos, int *moves);
Coord get_pos_roi(Piece *board[][8], unsigned int color);
int est_mortel(Piece *board[][8], Coord pos, Joueur color);
int est_echec(Piece *board[][8], unsigned int color);
void moves_legaux(Piece *board[][8], Coord pos, int *moves);
int est_legal(Piece *board[][8], Coord pos, Coord target, int *moves);
int zero_moves(Piece *board[][8], Joueur color);
int est_echec_et_mat(Piece *board[][8], Joueur color);
int est_pat(Piece *board[][8], Joueur color);
int seulement_rois(Piece *board[][8]);
void pion_ligne_finale(Piece *board[][8], Coord xy);
void maj_board(Piece *board[][8], Coord old, Coord new, int *morts_w, int *morts_b);

/*-----------------------Module graphique--------------------------*/

void make_grid();
void color_piece();
void indic_deplace(Piece *board[][8], Coord pos, int *moves);
void actualise_plateau(Piece *board[][8], Coord pos, int *moves, int trajectoires);
Coord clic_or_save(Piece *board[][8], Joueur jActuel, Montre *clock1, Montre *clock2, Montre clock_init, int *morts_w, int *morts_b, int *Save);
void screen_fin_partie(Joueur color);
void affichage_save();
void aff_leaderboard();
int save_state();
int choix_piece_pion(Joueur color);
void draw_timer(Montre *clock, Joueur jActuel);
void actualise_morts(int *morts_w, int *morts_b);
void dessiner_pieces(int emplacement);

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

/*-------------------------Module du menu---------------------------*/

/*void leaderboard();*/
ChoixMenu menu();

/*-------------------------Module de jeu----------------------------*/

int jeu(int choix, int *scores);

/*---------------------Module de sauvegarde-------------------------*/

void save(Piece *board[][8], Joueur jActuel, int save_state, int *morts_w, int *morts_b, Montre *clock1, Montre *clock2);
Joueur load(Piece *board[][8], Piece pieces[32], int save_state, int *morts_w, int *morts_b, Montre *clock1, Montre *clock2);
void lect_pseudos(JLeaderboard *j1, JLeaderboard *j2);
int lecture_leaderboard(JLeaderboard Leaderboard[10]);
void update_leaderboard(int scores[2]);

/*------------------------Module du timer----------------------------*/

int compt_sec(Montre *clock);
void reinject_clock(Montre *clock, int sec);
void set_local_time(Montre *clock);
void update_time(Montre *clock1, Montre *clock2, Montre clock_init);
void set_clock(Montre *clock);

/*-------------------Module editor----------------------*/

void editor(Piece *board[][8], Piece *set_pieces);
