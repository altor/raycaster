/* Structure contenant la carte de la pièce à explorer
 * -grille :  un tableau à 2 dimension contenant les identifiant des textures des mur ou 0 si il n'y a pas de mur
 * -l_ordonnee et l_abscisse* représente la taille de la grille
*/
#include "carte.h"


struct carte{
  int ** grille;
  int l_abssice;
  int l_ordonnee;
};

carte * carte_new(int l_abssice, int l_ordonnee, int init[l_ordonnee][l_abssice])
{
  int i,j;
  carte * map;

  map = malloc(sizeof(carte));
  map->l_abssice = l_abssice;
  map->l_ordonnee = l_ordonnee;
  map->grille = malloc(l_ordonnee * sizeof(int*));
  for(i = 0; i < l_ordonnee; i++){
    map->grille[i] = malloc(l_abssice * sizeof(int));
    for(j = 0; j < l_abssice; j++)
      map->grille[i][j] = init[i][j];
  }
  return map;
}

void carte_free(carte * p)
{
  int i;

  for(i = 0; i < p->l_ordonnee; i++)
    free(p->grille[i]);
  free(p->grille);
  free(p);
}

int  carte_get_info(carte * p, int i, int j)
{
  int ordonnee = (p->l_ordonnee) - 1 - j;
  return p->grille[ordonnee][i];
}
int carte_get_l_abssice(carte * p)
{
  return p->l_abssice;
}
int carte_get_l_ordonnee(carte * p)
{
  return p->l_ordonnee;
}
