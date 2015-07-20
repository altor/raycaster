#ifndef MUR_H
#define MUR_H

typedef struct mur mur;

mur * mur_new(int id, double taille, double portion_texture);
void mur_free(mur * p);
int mur_get_id(mur * p);
double mur_get_taille(mur * p);
double mur_get_portion_texture(mur * p);
void mur_set_id(mur * p, int val);
void mur_set_taille(mur * p, double val);
void mur_set_portion_texture(mur * p, double val);



#endif
