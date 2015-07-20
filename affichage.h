#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "config.h"
void rafraichir(carte * map, camera * joueur, mur * info_mur[L_ECRAN], int taille_ecran, SDL_Surface * ecran);
SDL_Surface * init_sdl();

#endif
