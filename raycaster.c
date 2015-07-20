/*
 * Implementation de la fonction raycaster
 * Cette fonction envoie des rayons pour détecter les murs visible par la caméra.
 * Elle récupère la distance entre la caméra et le mur détecté, l'identifiant de la texture à appliquer et la portion de texture à appliquer.
 * La distance entre la caméra et le mur est ensuite transformée en taille du mur à afficher.
 * Toutes ces informations sont stockés dans le tableau info_mur passé en argument.
 * Ce tableau serra utilisé ensuite pour afficher l'écran
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "carte.h"
#include "mur.h"
#include "coordonnee.h"
#include "camera.h"
#include "config.h"
#include "util.h"

int limite(coordonnee * pt)
{
  return coordonnee_get_x(pt) < MAX_X && coordonnee_get_y(pt) < MAX_Y;
}

int egal_angle(double a, double b) {
  return fabs(a-b) <= (ANGLE_RAYON/2);
}

double distance_point(coordonnee * p1, coordonnee * p2)
{
  return sqrt(pow(fabs(coordonnee_get_x(p2)-coordonnee_get_x(p1)),2) + pow(fabs(coordonnee_get_y(p2)-coordonnee_get_y(p1)),2));
}

double gen_portion_texture(coordonnee * point, int boolean)
{
  if(boolean)
    return ((int)coordonnee_get_x(point) + 100) % 100;
  return ((int)coordonnee_get_y(point) + 100) % 100;
  
}


mur * trouver_mur(coordonnee * depart, double d_x, double d_y, carte * map, int boolean)
{
  int i, j;
  coordonnee * point;
  double val_distance_point, val_portion_texture;
  point = coordonnee_cp(depart);
  while(limite(point)){

    i = coordonnee_get_x(point) / 100;
    j = coordonnee_get_y(point) / 100;

    if(carte_get_info(map,i,j) != 0){
      val_distance_point = distance_point(depart, point);
      val_portion_texture = gen_portion_texture(point, boolean);
      coordonnee_free(point);
      return mur_new(carte_get_info(map,i,j), val_distance_point, val_portion_texture);
    }
    if(carte_get_info(map,i-1,j) != 0){
      val_distance_point = distance_point(depart, point);
      val_portion_texture = gen_portion_texture(point, boolean);
      coordonnee_free(point);
      return mur_new(carte_get_info(map,i-1,j), val_distance_point, val_portion_texture);
    }
    if(carte_get_info(map,i,j-1) != 0){
      val_distance_point = distance_point(depart, point);
      val_portion_texture = gen_portion_texture(point, boolean);
      coordonnee_free(point);
      return mur_new(carte_get_info(map,i,j-1), val_distance_point, val_portion_texture);
    }
    if(carte_get_info(map,i-1,j-1) != 0){
      val_distance_point = distance_point(depart, point);
      val_portion_texture = gen_portion_texture(point, boolean);
      coordonnee_free(point);
      return mur_new(carte_get_info(map,i-1,j-1), val_distance_point, val_portion_texture);}
    
    //on avance à la prochaine intersection
    coordonnee_set_x(point, coordonnee_get_x(point) + d_x);
    coordonnee_set_y(point, coordonnee_get_y(point) + d_y);
  }
  coordonnee_set_x(point, MAX_X);
  coordonnee_set_y(point, MAX_Y);
  val_distance_point = distance_point(depart, point);
  coordonnee_free(point);
  return  mur_new(-1, val_distance_point, 0);
}


mur * distance_mur(double d_x, double d_y, coordonnee * depart, carte * map, double angle)
{
  mur * retour_x, * retour_y;

  //rayon parallèle à l'axe des abscisses
  if(d_y == 0 && fabs(d_x) == 100)
    return trouver_mur(depart, d_x, 0, map, 0);
  //rayon parallèle a l'axe des ordonnées
  if(d_x == 0 && fabs(d_y) == 100)
    return trouver_mur(depart, 0, 100, map, 1);
  
  if(d_x == 0)
    retour_x = mur_new(-1, MAX_X * MAX_Y, 0);
  
  else{
    //angle dans la moitié sud
    //    if(!egal_angle(angle, acos(-1)) && angle > acos(-1))
    if(sin(angle) < 0)
      retour_x = trouver_mur(depart, d_x, -100, map, 0);

    // angle dans la moitié nord
    else
      retour_x = trouver_mur(depart, d_x, 100, map, 0);
  }

  
  if(d_y == 0)
    retour_y = mur_new(-1, MAX_X * MAX_Y, 0);
  else{
    //angle dans la moitié ouest
    //if((!egal_angle(angle,asin(1)) && angle > asin(1)) && (!egal_angle(angle,3*asin(1)) && angle < 3*asin(1)))
    //    if(angle > asin(1) && angle < 3*asin(1))
    if(cos(angle) < 0)
      retour_y = trouver_mur(depart, -100, d_y, map, 1);
    //angle dans la moitié est
    else
      retour_y = trouver_mur(depart,100, d_y, map, 1);
  }
  //on renvoi la distance la plus courte

  if(mur_get_taille(retour_x) > mur_get_taille(retour_y))
    return retour_y;
  return retour_x;
}

double d_croisement(coordonnee * depart, double angle, int iter_i, int (*pf) (double, int), int bool)
{
  int max1, max2, i;
  double retour, c1, c2, translation_1, translation_2;

  retour = 0;
  if(bool){
    c1 = coordonnee_get_x(depart);
    c2 = coordonnee_get_y(depart);
    max1 = MAX_X + 1;
    max2 = MAX_Y + 1;
    i = coordonnee_get_x(depart) / 100 + iter_i;
    translation_1 = cos(angle);
    translation_2 = sin(angle);
    }
  else{

    c1 = coordonnee_get_y(depart);
    c2 = coordonnee_get_x(depart);
    max1 = MAX_Y + 1;
    max2 = MAX_X + 1;
    i = coordonnee_get_y(depart) / 100 + iter_i;
    translation_1 = sin(angle);
    translation_2 = cos(angle);

    

  }

  while((c1 < max1 && c1 > -1 )&& (c2 < max2 && c2 > -1) ){
    if(pf(c2, i)){
      if(!retour)
	{
	  retour = c1;
	  i += iter_i;
	}
      else {
	return fabs(c1 - retour);
      }
    }
    c1 += translation_1;
    c2 += translation_2;
  }
  return 0;
}

int compare_sup(double point, int i)
{
  return point / 100 >= i;
}
int compare_inf(double point, int i)
{
  return point / 100 <= i;
}

mur * rayon(coordonnee * depart, double angle, carte * map)
{
  int iter_i, iter_j;
  double d_x, d_y;
  int (*pf_i) (double, int);
  int (*pf_j) (double, int);

  // on cherche d'abord l'intervalle entre les points d'intersections et la grille
  //cas particulier (rayon parallèle à un axe)
  if(egal_angle(angle ,acos(-1)))
    {
      d_x = -100;
      d_y = 0;

    }
  else if( egal_angle(angle, acos(1)))
    {
      d_x = 100;
      d_y = 0;
    }
  else if(egal_angle(angle, asin(1)) )
    {
      d_x = 0;
      d_y = 100;
    }
  else if(egal_angle(angle, 3*asin(1)))
    {
      d_x = 0;
      d_y = -100;
    }
  else{

    if(sin(angle) < 0){
      pf_i = &compare_inf;
      iter_i = -1;
    }
    else{
      iter_i = 1;
      pf_i = &compare_sup;
    }
    if(cos(angle) < 0){
      pf_j = &compare_inf;
      iter_j = -1;
    }
    else{
      pf_j = &compare_sup;
      iter_j = 1;
    }
    
    /*
     * On envoi un rayon selon un certain angle 
     * Le rayon coupe la grille selon ses axes verticaux et horizontaux
     * On cherche la distance entre chaque croisement du rayon et d'un axe de la grille (vertical ou horizontal)
     */
    d_x = d_croisement(depart, angle, iter_i, pf_i, 1);
    d_y = d_croisement(depart, angle, iter_j, pf_j, 0);

  }

  return distance_mur(d_x, d_y, depart, map, angle);
}


void raycaster(carte * map, camera * joueur, mur * info_mur[L_ECRAN], int taille)
{
  int i;
  double angle_correction, angle_courant, angle_joueur;

  angle_joueur = camera_get_angle(joueur);
  angle_courant = purifier_angle(angle_joueur + FOV/2);
  for(i = 0; i < taille; i++){
    angle_correction = purifier_angle(fabs(angle_joueur - angle_courant));
    info_mur[i] = rayon(camera_get_position(joueur), angle_courant, map);//récupération des infos concernant le mur à afficher (distance, type)
    mur_set_taille(info_mur[i], mur_get_taille(info_mur[i]) * cos(angle_correction)); //correction optique
    mur_set_taille(info_mur[i], H_MUR / mur_get_taille(info_mur[i]) * D_ECRAN_OBS); //calcul de la taille du mur
    angle_courant = purifier_angle(angle_courant - ANGLE_RAYON); //calcul de l'angle du nouveau rayon à tracer
  }
}

