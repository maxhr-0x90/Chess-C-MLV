#include "assets.h"

/*------Fonction permettant la sauvegarde de la matrice de jeu------*/

void save(Piece *board[][8], Joueur jActuel, int save_state, int *morts_w, int *morts_b, Montre *clock1, Montre *clock2){
  int i, j, x;
  FILE* save = NULL;
  char save_name[12];

  /*On prend le chemin de la save state en fonction du numéro choisi dans la fonction dédiée et on l'ouvre*/
  sprintf(save_name, "saves/save%d", save_state);
  remove(save_name);
  save = fopen(save_name, "a+");

  /*On calcule le nombre de pièce afin de faire une boucle for dans la fonction load et non une boucle while*/
  x = 0;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if(board[i][j] != NULL){
        x++;
      }
    }
  }

  /*On met dans le fichier le joueur actuel ainsi que le nombre de pièce dans le plateau*/
  fputc(jActuel, save);
  fputc(x, save);

  /*On insère les coordonnées et toutes les caractéristiques des pièces dans le fichier*/
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

  /*On insère le nombre et le rang des pièces mortes dans le fichier*/
  fputc(morts_w[0], save);
  for(i = 1; i < morts_w[0]+1; i++){
    fputc(morts_w[i], save);
  }
  fputc(morts_b[0], save);
  for(i = 1; i < morts_b[0]+1; i++){
    fputc(morts_b[i], save);
  }

  /*On insère le temps de jeu des deux joueurs dans le fichier*/
  fputc(clock2->h, save);
  fputc(clock2->m, save);
  fputc(clock2->s, save);
  fputc(clock1->h, save);
  fputc(clock1->m, save);
  fputc(clock1->s, save);

  fclose(save);
}

/*------Fonction permettant le chargement de la matrice de jeu------*/

Joueur load(Piece *board[][8], Piece pieces[32], int save_state, int *morts_w, int *morts_b, Montre *clock1, Montre *clock2){
  int i, j, x, y;
  Joueur jActuel;
  FILE* save = NULL;
  char save_name[12];

  /*On prend le chemin de la save state en fonction du numéro choisi dans la fonction dédiée et on l'ouvre*/
  sprintf(save_name, "saves/save%d", save_state);
  save = fopen(save_name, "r+");

  /*On récupère le joueur actuel ainsi que le nombre de pièce dont l'on se servira dans la prochaine boucle for*/
  jActuel = fgetc(save);
  i = 0;
  j = fgetc(save);

  /*On vide le plateau*/
  vider_plateau(board);
  for(i = 0; i < j; i++){
    /*On récupère les coordonnées des pièces et on insère les caractéristiques des pièces à leur emplacements*/

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

  /*On réinjecte le nombre et le rang des pièces mortes*/
  morts_w[0] = fgetc(save);
  for(i = 1; i < morts_w[0]+1; i++){
    morts_w[i] = fgetc(save);
  }
  morts_b[0] = fgetc(save);
  for(i = 1; i < morts_b[0]+1; i++){
    morts_b[i] = fgetc(save);
  }

  /*On remet le temps de partie à la sauvegarde dans les struct Montre*/
  clock1->h = fgetc(save);
  clock1->m = fgetc(save);
  clock1->s = fgetc(save);
  clock2->h = fgetc(save);
  clock2->m = fgetc(save);
  clock2->s = fgetc(save);

  fclose(save);
  return jActuel;
}

/*------Fonction lisant un fichier texte et le mettant dans une string------*/


/*------Fonction d'input pour les pseudos a la fin du jeu------*/

void lect_pseudos(JLeaderboard *j1, JLeaderboard *j2){
  int i = 0;
  char* text1;
  char* text2;
  MLV_Font *font;

  MLV_create_window("Leaderboard", "Leaderboard", 800, 200);

  font = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 30);

  MLV_wait_input_box_with_font(10, 50, 800, 90, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_COLOR_BLACK, "Player 1 (Les Blancs): ", &text1, font);
  MLV_wait_input_box_with_font(10, 50, 800, 90, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_COLOR_BLACK, "Player 2 (Les Noirs): ", &text2, font);

  /*On remplace les potentiels espaces avec des '_' dans les deux textes*/
  while(text1[i] != '\0'){
    if(text1[i] == ' '){
      text1[i] = '_';
    }
    i++;
  }

  i = 0;
  while(text2[i] != '\0'){
    if(text2[i] == ' '){
      text2[i] = '_';
    }
    i++;
  }

  /*On écrit dans les struct les textes*/
  sprintf(j1->pseudo, "%s", text1);
  sprintf(j2->pseudo, "%s", text2);
  MLV_free_window();
}



int lecture_leaderboard(JLeaderboard Leaderboard[10]){
  char chaine[1000];
  FILE *lb = NULL;
  int i, n, readout;
  lb = fopen("leaderboard", "r");
  readout = fscanf(lb, "%s", chaine);
  if (readout == 0){
    return -1;
  }
  n = atoi(chaine);

  /*Récupération des scores et des pseudos*/
  for(i = 0; i < n; i++){
    readout = fscanf(lb, "%s", chaine);
    if (readout == 0){
      break;
    }
    Leaderboard[i].score = atoi(chaine);
    readout = fscanf(lb, "%s", Leaderboard[i].pseudo);
    if (readout == 0){
      break;
    }
  }

  for(i = n; i < 10; i++){
    Leaderboard[i].score = -1;
  }
  fclose(lb);
  return n;
}

/*Met à jour la place du joueur situé à la place index dans le classement*/
int update_place(JLeaderboard *lb, int index){
  JLeaderboard temp;

  /*Cas où le joueur ne serait pas premier et que sont score est supérieur à celui du dessus*/
  while(index != 0 && lb[index].score > lb[index-1].score){
    temp = lb[index-1];
    lb[index-1] = lb[index];
    lb[index] = temp;
    index--;
  }

  /*Cas où le joueur ne serait pas dernier et que sont score est inférieur à celui du dessous*/
  while(index != 9 && lb[index].score < lb[index+1].score){
    temp = lb[index+1];
    lb[index+1] = lb[index];
    lb[index] = temp;
    index++;
  }

  /*Cas où le joueur possède un score nul ou négatif*/
  if(lb[index].score <= 0){
    lb[index].score = -1;
    lb[index].pseudo[0] = '\0';
    return 1;
  }
  return 0;
}

void update_leaderboard(int scores[2]){
  JLeaderboard lb[10], j1, j2;
  int i = 0, j, nombre_joueur;
  FILE *leaderboard = NULL;

  nombre_joueur = lecture_leaderboard(lb);
  lect_pseudos(&j1, &j2);

  /*J1 Blancs*/

  while(i < 10 && lb[i].score != -1 && strcmp(lb[i].pseudo, j1.pseudo) && lb[i].score >= scores[0]){
    i++;
  }
  if(i != 10){
    if(!strcmp(lb[i].pseudo, j1.pseudo)){
      lb[i].score += scores[0];
      nombre_joueur -= update_place(lb, i);
    }
    else if(scores[0] > 0){
      if(lb[i].score != -1){
        for(j = 9; j > i; j--){
          lb[j] = lb[j-1];
        }
        j1.score = scores[0];
        lb[i] = j1;
      }
      else{
        j1.score = scores[0];
        lb[i] = j1;
        nombre_joueur++;
      }
    }
  }

  /*J2 Noirs*/

  i = 0;
  while(i < 10 && lb[i].score != -1 && strcmp(lb[i].pseudo, j2.pseudo) && lb[i].score >= scores[0]){
    i++;
  }

  if(i != 10){
    if(!strcmp(lb[i].pseudo, j2.pseudo)){
      lb[i].score += scores[1];
      nombre_joueur -= update_place(lb, i);
    }
    else if(scores[1] > 0){
      if(lb[i].score != -1){
        for(j = 9; j > i; j--){
          lb[j] = lb[j-1];
        }
        j2.score = scores[1];
        lb[i] = j2;
      }
      else{
        j2.score = scores[1];
        lb[i] = j2;
        nombre_joueur++;
      }
    }
  }

  leaderboard = fopen("leaderboard", "w");
  if(leaderboard == NULL){
    fprintf(stderr, "Accès impossible\n");
    exit(1);
  }
  fprintf(leaderboard, "%d\n", nombre_joueur);
  i = 0;
  while(i < 10 && lb[i].score > 0){
    fprintf(leaderboard, "%d\n%s\n", lb[i].score, lb[i].pseudo);
    i++;
  }
  fclose(leaderboard);
}
