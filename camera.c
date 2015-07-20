/* structure contenant les informations relative à la caméra
 * -angle : contient l'orientation de la caméra par rapport à l'axe des ordonnées
 * -position : contient les coordonnées (x,y) de la caméra
 * -hauteur : contient la coordonné Z de la caméra
*/

#include <stdlib.h>
#include "camera.h"
#include "coordonnee.h"



struct camera{
  double angle;
  coordonnee * position;
  int hauteur;
};


camera * camera_new(double angle, double x, double y, int hauteur)
{
  camera * retour = malloc(sizeof(camera));
  retour->angle = angle;
  retour->position = coordonnee_new(x,y);
  retour->hauteur = hauteur;
  return retour;
  
}
void camera_free(camera * p)
{
  free(p->position);
  free(p);
}

double camera_get_angle(camera * p)
{
  return p->angle;
}
coordonnee * camera_get_position(camera * p)
{
  return p->position;
}
int camera_get_hauteur(camera * p)
{
  return p->hauteur;
}
void camera_set_position(camera * p, double x, double y)
{
  coordonnee_set_x(p->position, x);
  coordonnee_set_y(p->position, y);
}
void camera_set_angle(camera * p, double val)
{
  p->angle = val;
}
void camera_set_hauteur(camera * p, int val)
{
  p->hauteur = val;
}
