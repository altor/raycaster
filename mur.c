/* Structure utilisée pour stocker des informations sur un mur quand un rayon l'a détectée.
 * -id :  contient l'identifiant de la texture à appliquer lors de l'affichage
 * -taille : contient la taille de la portion de mur à afficher
 * -portion_texture : contient la coordonnée x de la texture à appliquer sur la portion de mur détectée.
*/

#include <stdlib.h>
#include "mur.h"

struct mur{
  int id;
  double taille;
  double portion_texture;
};

mur * mur_new(int id, double taille, double portion_texture)
{
  mur * p;

  p = malloc(sizeof(mur));
  p->id = id;
  p->taille = taille;
  p->portion_texture = portion_texture;

  return p;
}
void mur_free(mur * p)
{
  free(p);
}

int mur_get_id(mur * p)
{
  return p->id;
}
double mur_get_taille(mur * p)
{
  return p->taille;
}

double mur_get_portion_texture(mur * p)
{
  return p->portion_texture;
}
void mur_set_id(mur * p, int val)
{
  p->id = val;  
}
void mur_set_taille(mur * p, double val)
{
  p->taille = val;  
}
void mur_set_portion_texture(mur * p, double val)
{
  p->portion_texture = val;  
}
