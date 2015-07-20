#ifndef COORDONNEE_H
#define COORDONNEE_H

typedef struct coordonnee coordonnee;

coordonnee * coordonnee_new(double x, double y);
coordonnee * coordonnee_cp(coordonnee * p);
void coordonnee_free(coordonnee * p);
double coordonnee_get_x(coordonnee * p);
double coordonnee_get_y(coordonnee * p);
void coordonnee_set_x(coordonnee * p, double val);
void coordonnee_set_y(coordonnee * p, double val);


#endif
