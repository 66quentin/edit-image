#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#define X_AXIS 0
#define Y_AXIS 1
#define XY_AXIS 2
#include "pixmap.h"

void *reverse_pixmap(pixmap_t *c,int axe);
void *tranform_to_gray_pixmap(pixmap_t *cc,long double a, long double b, long double c);
void *binarize_pixmap(pixmap_t *c,float ratio, int sens);
void *eclairer_pixmap(pixmap_t *c,float coef,int couleur);
void *contraster_pixmap(pixmap_t *c,float coef,int couleur);

#endif
