#include "assets.h"

/*------Fonction permettant la sauvegarde de la matrice de jeu------*/

void save(Piece *board[][8], Joueur jActuel, int save_state, int *morts_w, int *morts_b){
  int i, j, x;
  FILE* save = NULL;
  char save_name[12];
  sprintf(save_name, "saves/save%d", save_state);
  remove(save_name);
  save = fopen(save_name, "a+");

  x = 0;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
        x++;
      }
    }
  }
  fputc(jActuel, save);
  fputc(x, save);
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
        fputc(i, save);
        fputc(j, save);
        fputc(board[i][j]->rang, save);
        fputc(board[i][j]->couleur, save);
        fputc(board[i][j]->nbMouv, save);
        fputc(board[i][j]->move.droit.val, save);
        fputc(board[i][j]->move.diagonal.val, save);
        fputc(board[i][j]->move.formeL.val, save);
        fputc(board[i][j]->move.limitation, save);
        fputc(board[i][j]->move.ajustement[0], save);
        if(board[i][j]->move.ajustement[0] != 0){
          fputc(board[i][j]->move.ajustement[1], save);
        }
      }
    }
  }
  fputc(morts_w[0], save);
  for(i = 1; i < morts_w[0]+1; i++){
    fputc(morts_w[i], save);
  }
  fputc(morts_b[0], save);
  for(i = 1; i < morts_b[0]+1; i++){
    fputc(morts_b[i], save);
  }
  fclose(save);
}

/*------Fonction permettant le chargement de la matrice de jeu------*/

Joueur load(Piece *board[][8], Piece pieces[32], int save_state, int *morts_w, int *morts_b){
  int i, j, x, y;
  Joueur jActuel;
  FILE* save = NULL;
  char save_name[12];
  sprintf(save_name, "saves/save%d", save_state);
  save = fopen(save_name, "r+");

  jActuel = fgetc(save);
  i = 0;
  j = fgetc(save);

  vider_plateau(board);
  for(i = 0; i < j; i++){

    x = fgetc(save);
    y = fgetc(save);
    pieces[i].rang = fgetc(save);
    pieces[i].couleur = fgetc(save);
    pieces[i].nbMouv = fgetc(save);
    pieces[i].move.droit.val = fgetc(save);
    pieces[i].move.diagonal.val = fgetc(save);
    pieces[i].move.formeL.val = fgetc(save);
    pieces[i].move.limitation = fgetc(save);
    pieces[i].move.ajustement[0] = fgetc(save);
    if(pieces[i].move.ajustement[0]){
      pieces[i].move.ajustement[1] = fgetc(save);
    }
    board[x][y] = &pieces[i];
  }
  morts_w[0] = fgetc(save);
  for(i = 1; i < morts_w[0]+1; i++){
    morts_w[i] = fgetc(save);
  }
  morts_b[0] = fgetc(save);
  for(i = 1; i < morts_b[0]+1; i++){
    morts_b[i] = fgetc(save);
  }
  fclose(save);
  return jActuel;
}

/*------Fonction lisant un fichier texte et le mettant dans une string------*/

void lecture_fic_lead(char *str){
  char c;
  int i = 0;
  FILE* lb = NULL;

  lb = fopen("leaderboard", "r+");

  if (lb == NULL){
    printf("Impossible, rien à analyser\n");
    exit(-1);
  }

  do {
    c = fgetc(lb);
    str[i] = c;
    i++;
  } while(c != EOF);
  str[i] = '\0';
  fclose(lb);
}

/*------Fonction d'input pour les pseudos a la fin du jeu------*/

void lect_pseudos(JLeaderboard *j1, JLeaderboard *j2){
  char* text1;
  char* text2;
  MLV_Font *font;

  MLV_create_window("Leaderboard", "Leaderboard", 800, 200);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 30);

  MLV_wait_input_box_with_font(10, 50, 800, 90, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_COLOR_BLACK, "Player 1 (Les Blancs): ", &text1, font);
  MLV_wait_input_box_with_font(10, 50, 800, 90, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_COLOR_BLACK, "Player 2 (Les Noirs): ", &text2, font);

  sprintf(j1->pseudo, "%s", text1);
  sprintf(j2->pseudo, "%s", text2);

  MLV_free_window();
}


/*------Fonction d'input pour les pseudos a la fin du jeu------*/

void lecture_leaderboard(JLeaderboard Leaderboard[10]){
  int i, j, k, champ;
  char dump[500], lead[1000];
  lecture_fic_lead(lead);

  i = 0;
  k = 0;
  champ = 0;
  while(lead[k+1] != '\0'){
    if(champ == 0){
      j = 0;
      while(lead[k] != '|' && lead[k] != EOF){
        dump[j] = lead[k];
        j++;
        k++;
        champ = 1;
      }
      Leaderboard[i].score = (int)strtol(dump, NULL, 10);
      k++;
      dump[0] = '\0';
    }
    if(champ == 1 && lead[k+3] != '\0'){
      j = 0;
      do{
        Leaderboard[i].pseudo[j] = lead[k];
        j++;
        k++;
        champ = 0;
      }while(lead[k] != '|' && lead[k+1] != '\0' && lead[k] != '\n');
      k++;

    }
    i++;
  }
  for(j = i; j < 10; j++){
    Leaderboard[i].score = -1;
  }
}

void tri_leaderboard(int scores[2]){
  int i, j;
  JLeaderboard j1, j2, Lead[10];
  FILE *lb = NULL;
  lect_pseudos(&j1, &j2);
  lecture_leaderboard(Lead);

  j1.score = scores[0];
  j2.score = scores[1];

  i = 0;
  while(j1.score < Lead[i].score && i < 10){
    i++;
  }
  if(i != 10 && !strcmp(Lead[i].pseudo, j1.pseudo)){
    Lead[i].score += j1.score;
  }
  else{
    if(i != 10){
      for(j = 9; j > i; j--){
        Lead[j] = Lead[j-1];
      }
      Lead[j] = j1;
    }
  }

  i = 0;
  while(j2.score < Lead[i].score && i < 10){
    i++;
  }
  if(i != 10 && !strcmp(Lead[i].pseudo, j2.pseudo)){
    Lead[i].score += j2.score;
  }
  else{
    if(i != 10){
      for(j = 9; j > i; j--){
        Lead[j] = Lead[j-1];
      }
      Lead[j] = j2;
    }
  }

  i = 0;

  remove("leaderboard");
  lb = fopen("leaderboard", "a+");
  if (lb == NULL){
    printf("Impossible, rien à analyser\n");
    exit(-1);
  }
  while(Lead[i].score != -1 && i != 10){
    fprintf(lb, "%d|", Lead[i].score);
    fprintf(lb, "%s|", Lead[i].pseudo);
    i++;
  }
  fclose(lb);
}


/*------Fonction calculant le score des joueurs------*/

int score(Piece *board[][8], Joueur color){
  int i, j, score;
  score = 39;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL && board[i][j]->couleur == color && board[i][j]->rang != Roi){
        switch(board[i][j]->rang){
          case Reine:
            score -= 9;
            break;
          case Tour:
            score -= 5;
            break;
          case Fou:
            score -= 3;
            break;
          case Cavalier:
            score -= 3;
            break;
          case Pion:
            score -= 1;
            break;
          default:
            break;
        }
      }
    }
  }
  return score;
}
