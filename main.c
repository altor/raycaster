#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>

#include "camera.h"
#include "carte.h"
#include "mur.h"
#include "config.h"
#include "util.h"
#include "affichage.h"





int main()
{
  int continuer;

  SDL_Event event;
  SDL_Surface * ecran = NULL;

  carte * map;
  camera *joueur;
  mur *info_mur[L_ECRAN];
  int grille [N_LIGNE][N_LIGNE] = {{4,4,4,4,2},
				   {1,0,0,0,2},
				   {1,0,0,0,2},
				   {1,0,0,0,2},
				   {1,3,3,3,3}};

  map = carte_new(N_LIGNE,N_LIGNE,grille);
  joueur = camera_new(1.57, 300, 200, 10);

  ecran = init_sdl(); 
  rafraichir(map, joueur, info_mur, L_ECRAN, ecran);

  continuer = 1;
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT: continuer = 0; break;
    case SDL_KEYDOWN :
      switch(event.key.keysym.sym){
      case SDLK_LEFT :
	camera_set_angle(joueur, purifier_angle(camera_get_angle(joueur) + 0.1));
	rafraichir(map, joueur, info_mur, L_ECRAN, ecran);
	break;
      case SDLK_RIGHT :
	camera_set_angle(joueur, purifier_angle(camera_get_angle(joueur) - 0.1));
	rafraichir(map, joueur, info_mur, L_ECRAN, ecran);
	break;
      default : break;
      }
    default : break;
    }
  }
  exit(EXIT_SUCCESS);
}
