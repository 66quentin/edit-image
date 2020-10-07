#ifndef FILTERS_H
#define FILTERS_H
#include "transformations.h"

struct filter_t {
	int n;
	int32_t **matrice;
	uint32_t a;
	uint32_t b;
};
typedef struct filter_t filter_t;

void free_filter(filter_t *filtre);
filter_t *fuzzy_filter(int n);
filter_t *prewitt_x_filter(pixmap_t *c, int n);
filter_t *prewitt_y_filter(pixmap_t *c, int n);
filter_t *sobel_x_filter(pixmap_t *c, int n);
filter_t *sobel_y_filter(pixmap_t *c, int n);
filter_t *discret_laplace_filter(pixmap_t *c, int n);
pixmap_t *apply_filter_pixmap(filter_t *filtre, pixmap_t *pixmap);

#endif
