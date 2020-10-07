#ifndef PIXMAP_H
#define PIXMAP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

enum type_t {P1=1, P2, P3};
typedef enum type_t pixmap_type_t;
struct pixmap_t {
	pixmap_type_t montype;
	uint32_t largeur;
	uint32_t hauteur;
	unsigned int pixel_t;
	long long int **tab;
};

union decoupage {
	long long int couleur;
	struct octets{
		int rouge:16;
		int vert:16;
		int bleu:16;
		int vide:16;
	}o;
};
union decoupage nb ;

typedef struct pixmap_t pixmap_t;
int i,j,k1,k2,r,v,b,y;
char type[10];
char testcomment[10];
char z;

pixmap_t *load_pixmap(char *nom);
void free_pixmap(pixmap_t *c);
pixmap_t *copy_pixmap(pixmap_t *c);
void *save_pixmap(pixmap_t *c,char *nom);

#endif
