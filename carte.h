#include <stdlib.h>

#ifndef CARTE_H
#define CARTE_H
typedef struct carte carte;

carte * carte_new(int l_abscisse, int l_ordonnee, int init[l_ordonnee][l_abscisse]);
void carte_free(carte * p);
int  carte_get_info(carte * p, int i, int j);
int carte_get_l_abssice(carte * p);
int carte_get_l_ordonee(carte * p);
#endif
