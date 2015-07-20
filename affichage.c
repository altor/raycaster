/*regroupe toute les fonctions d'affichages
 * init_sdl initialise la SDL et renvoi un écran d'affichage
 * raffraichir affiche les mur à l'écran
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#include "mur.h"
#include "config.h"
#include "camera.h"
#include "carte.h"
#include "raycaster.h"

void positioner_mur(mur * info_mur[L_ECRAN], SDL_Surface * ecran)
{
  int i;
  SDL_Surface * mur;
  SDL_Rect position;
  SDL_PixelFormat * format;

  format = ecran->format;
  position.x = 0;
  position.y = 0;

  mur = SDL_CreateRGBSurface(SDL_HWSURFACE, L_ECRAN, H_ECRAN, 32, 0, 0, 0, 0);
  SDL_FillRect(mur, NULL, SDL_MapRGB(format, 0, 0, 0));
  SDL_BlitSurface(mur, NULL, ecran,&position);
  SDL_FreeSurface(mur);
  for(i = 0 ; i < L_ECRAN ; i++)
    {
      mur = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, mur_get_taille(info_mur[i]), 32, 0, 0, 0, 0);
      switch(mur_get_id(info_mur[i])){
      case 1:
	SDL_FillRect(mur, NULL, SDL_MapRGB(format,0xFF, 0x00, 0x00));
	break;
      case 2:
	SDL_FillRect(mur, NULL, SDL_MapRGB(format,0x0, 0xFF, 0x00));
	break;
      case 3:
	SDL_FillRect(mur, NULL, SDL_MapRGB(format,0x00, 0x0, 0xFF));
	break;
      case 4:
	SDL_FillRect(mur, NULL, SDL_MapRGB(format,0x66, 0x66, 0x66));
	break;
      default:
	SDL_FillRect(mur, NULL, SDL_MapRGB(format,0xFF, 0xFF, 0xFF));
	break;
      }
      
      position.y = (H_ECRAN - mur_get_taille(info_mur[i])) / 2;
      SDL_BlitSurface(mur, NULL, ecran, &position);
      position.x += 1;
      
    }
  SDL_FreeSurface(mur);
  
}

SDL_Surface * init_sdl()
{
  SDL_Surface * ecran;

  if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
      exit(EXIT_FAILURE); // On quitte le programme
    }
  if((ecran = SDL_SetVideoMode(L_ECRAN, H_ECRAN, 32, SDL_HWSURFACE)) == NULL){
    fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return ecran;
}

void rafraichir(carte * map, camera * joueur, mur * info_mur[L_ECRAN], int taille_ecran, SDL_Surface * ecran)
{
  raycaster(map, joueur, info_mur,taille_ecran);
  positioner_mur(info_mur, ecran);
  SDL_Flip(ecran);
}


