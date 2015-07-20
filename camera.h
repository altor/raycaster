#include "coordonee.h"
#ifndef CAMERA_H
#define CAMERA_H

typedef struct camera camera;

camera * camera_new(double angle, double x, double y, int hauteur);
void camera_free(camera * p);
double camera_get_angle(camera * p);
coordonnee * camera_get_position(camera * p);
int camera_get_hauteur(camera * p);
void camera_set_position(camera * p, double x, double y);
void camera_set_angle(camera * p, double val);
void camera_set_hauteur(camera * p, int val);

#endif



