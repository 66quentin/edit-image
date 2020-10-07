#ifndef GETOPT_H
#define GETOPT_H
#include "filters.h"
#include <unistd.h>
#include <getopt.h>

void enregistrer(pixmap_t *a, char *nom, int ccc);
int s=-1, d=-1;
extern char *optarg;
extern int optind;
char *source, *destination;
int ch;
struct opt {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	int h;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int o;
	int p;
	int q;
	int r;
	int s;
	int t;
	int u;
	int v;
	int w;
	int x;
} opt;
static struct option long_options[] ={
	{"input", required_argument, NULL, 'a'},
	{"outup", required_argument, NULL, 'b'},
	{"save-temps", no_argument,0, 'c'},
	{"help", no_argument,0, 'd'},
	{"reverse_x", no_argument,0, 'e'},
	{"reverse_y", no_argument,0,  'f'},
	{"reverse_xy", no_argument,0, 'g'},
	{"gray", required_argument,0, 'h'},
	{"binarise", required_argument,0, 'i'},
	{"binarise_inverse", required_argument,0, 'j'},
	{"brightness_r", required_argument,0, 'k'},
	{"brightness_g", required_argument,0, 'l'},
	{"brightness_b", required_argument,0, 'm'},
	{"brightness_a", required_argument,0, 'n'},
	{"contrast_r", required_argument,0, 'o'},
	{"contrast_g", required_argument,0, 'p'},
	{"contrast_b", required_argument,0,  'q'},
	{"contrast_a", required_argument,0, 'r'},
	{"fuzzy", required_argument,0, 's'},
	{"prewitt_x", no_argument,0, 't'},
	{"prewitt_y", no_argument,0, 'u'},
	{"sobel_x", no_argument,0, 'v'},
	{"sobel_y", no_argument,0, 'w'},
	{"laplace", no_argument,0, 'x'},
	{NULL, 0, NULL, 0}
};
int arg1=-1,arg2=-1,arg3=-1,arg4=-1,arg5=-1,arg6=-1,arg7=-1,arg8=-1,arg9=-1, arg10=-1,jj,ii;
float aa,bb,cc,arg11=-1, arg12=-1;

#endif
