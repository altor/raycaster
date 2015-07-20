/*
 * fonction utilitaire
 * purifier_angle permet de s'assurer que l'angle passé en argument conserve sa valeur entre 0 et 360 degrés
*/

#include <math.h>

double purifier_angle(double angle)
{
  if(angle < 0)
    return angle + 2 * acos(-1);
  if(angle > 2 * acos(-1))
    return angle - 2 * acos(-1);
  return angle;
}
