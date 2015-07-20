/* structure représentant les coordonnées d'un point dans le plan. */

#include <stdlib.h>
#include "coordonnee.h"


struct coordonnee{
  double x;
  double y;
};

coordonnee * coordonnee_new(double x, double y)
{
  coordonnee * str;
  
  str = malloc(sizeof(coordonnee));
  str->x = x;
  str->y = y;
  
  return str;
}

coordonnee * coordonnee_cp(coordonnee * p){
  coordonnee * nv;

  nv = malloc(sizeof(coordonnee));
  nv->x = p->x;
  nv->y = p->y;
  return nv;
}


void coordonnee_free(coordonnee * p)
{
  free(p);
}

double coordonnee_get_x(coordonnee * p)
{
  return p->x;
}
double coordonnee_get_y(coordonnee * p)
{
  return p->y;
}
void coordonnee_set_x(coordonnee * p, double val)
{
  p->x = val;
}
void coordonnee_set_y(coordonnee * p, double val)
{
  p->y = val;
}
