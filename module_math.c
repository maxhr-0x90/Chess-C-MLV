#include "assets.h"

/*Fonction signe*/
int sgn(int i){
  if (i > 0) {
    return 1;
  } else if (i < 0) {
    return -1;
  } else {
    return 0;
  }
}

/*Rotation du vecteur dans le sens direct (NB: y orienté vers le bas)*/
/*NB: mat_rot contient cos(a), sin(a) où a, l'angle*/
Coord rotation(Coord vect, float mat_rot[]){
  int tmp_x_coord = vect.x;
  vect.x = (int)(tmp_x_coord*mat_rot[0] - vect.y*mat_rot[1]);
  vect.y = (int)(tmp_x_coord*mat_rot[1] + vect.y*mat_rot[0]);

  return vect;
}

/*Rotation du vecteur selon 4 préconfiguations utiles aux échecs*/
Coord rot_mode(Coord vect, char mode){
  float mat_rot[2];
  switch (mode) {
    case 90 : /*Rotation 90°*/
      mat_rot[0] = 0.0f;
      mat_rot[1] = 1.0f;
      vect = rotation(vect, mat_rot);
      break;
    case 45 : /*Rotation 45° + modication du module en entier relatif unitaire*/
      mat_rot[0] = 1.0f;
      mat_rot[1] = 1.0f;
      vect = rotation(vect, mat_rot);
      vect.x = sgn(vect.x);
      vect.y = sgn(vect.y);
      break;
    case 'C' : /*Roation cavalier grand angle*/
      mat_rot[0] = 0.6f;
      mat_rot[1] = 0.8f;
      vect = rotation(vect, mat_rot);
      break;
    case 'c' : /*Roation cavalier petit angle*/
      mat_rot[0] = 0.8f;
      mat_rot[1] = 0.6f; 
      vect = rotation(vect, mat_rot);
      break;
  }

  return vect;
}
