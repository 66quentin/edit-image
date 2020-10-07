#include "transformations.h"

void *reverse_pixmap(pixmap_t *c,int axe){
	pixmap_t *reverse=NULL;
	reverse=(pixmap_t*)malloc(sizeof(pixmap_t));
	*reverse=*c;
	if(reverse != NULL){
		(*reverse).tab=(long long int**)malloc((*reverse).largeur*sizeof(long long int*));
		for(i = 0; i < (*reverse).largeur; i++)
			(*reverse).tab[i] = malloc((*reverse).hauteur * sizeof(long long int));
		for(i=0;i<(*reverse).largeur;i++){
			for(j=0;j<(*reverse).hauteur;j++){
				if(axe==0)
					(*reverse).tab[i][(*c).hauteur-1-j]=(*c).tab[i][j];
				if(axe==1)
					(*reverse).tab[(*c).largeur-1-i][j]=(*c).tab[i][j];
				if(axe==2)
					(*reverse).tab[(*c).largeur-1-i][(*c).hauteur-1-j]=(*c).tab[i][j];
			}
		}
	}else{
		printf("Erreur pour allouer de la mémoire lors de la copie de l'image\n");
	}
	return reverse;
}

void *tranform_to_gray_pixmap(pixmap_t *cc,long double a, long double b, long double c){
	int rouge, vert,bleu;
	pixmap_t *gray=NULL;
	gray=(pixmap_t*)malloc(sizeof(pixmap_t));
	*gray=*cc;
	if((*cc).montype==3){
		printf("%d\n",(*cc).montype);
		if(gray != NULL){
			(*gray).tab=(long long int**)malloc((*gray).largeur*sizeof(long long int*));
			for(i = 0; i < (*gray).largeur; i++)
				(*gray).tab[i] = malloc((*gray).hauteur * sizeof(long long int));
			for(i=0;i<(*gray).largeur;i++){
				for(j=0;j<(*gray).hauteur;j++){
					nb.couleur=(*cc).tab[i][j];
					rouge=a*nb.o.rouge;
					vert=b*nb.o.vert;
					bleu=c*nb.o.bleu;
					(*gray).tab[i][j]=rouge+vert+bleu;
				}
			}
			(*gray).montype=2;
		}else{
			printf("Erreur pour allouer de la mémoire lors de la copie de l'image\n");
		}
	}else{
		printf("Mauvais format pour transformer en gris (image PPM attendue)\n");
	}
	return gray;

}

void *binarize_pixmap(pixmap_t *c,float ratio, int sens){
	pixmap_t *binarize=NULL;
	binarize=(pixmap_t*)malloc(sizeof(pixmap_t));
	*binarize=*c;
	if((*binarize).montype!=1){
		if(binarize != NULL){
			(*binarize).tab=(long long int**)malloc((*binarize).largeur*sizeof(long long int*));
			for(i = 0; i < (*binarize).largeur; i++)
				(*binarize).tab[i] = malloc((*binarize).hauteur * sizeof(long long int));
			for(i=0;i<(*binarize).largeur;i++){
				for(j=0;j<(*binarize).hauteur;j++){
					if((*binarize).montype==2){
						if((float)(*c).tab[i][j]/(float)(*c).pixel_t<ratio){
							(*binarize).tab[i][j]=sens;
						}else{
							(*binarize).tab[i][j]=1-sens;
						}
					}
					if((*binarize).montype==3){
						nb.couleur=(*c).tab[i][j];
						if((nb.o.bleu*nb.o.vert*nb.o.rouge)/pow((*c).pixel_t,3)<ratio){
							(*binarize).tab[i][j]=sens;
						}else{
							(*binarize).tab[i][j]=1-sens;
						}
					}		
				}
			}
			(*binarize).montype=1;
		}else{
			printf("Erreur pour allouer de la mémoire lors de la copie de l'image\n");
		}
	}else{
		printf("Erreur pour binariser: image PPM ou PGM attendue.\n");
	}
	return binarize;
}

void *eclairer_pixmap(pixmap_t *c,float coef,int couleur){
	int erreur=0;
	pixmap_t *clair=NULL;
	clair=(pixmap_t*)malloc(sizeof(pixmap_t));
	*clair=*c;
	if(clair != NULL){
		(*clair).tab=(long long int**)malloc((*clair).largeur*sizeof(long long int *));
		for(i = 0; i < (*clair).largeur; i++)
			(*clair).tab[i] = malloc((*clair).hauteur * sizeof(long long int));
		for(i=0;i<(*clair).largeur;i++){
			for(j=0;j<(*clair).hauteur;j++){
				if((*clair).montype==2){
					(*clair).tab[i][j]=(*c).tab[i][j]*coef;
				}else if((*clair).montype==3){
					nb.couleur=(*c).tab[i][j];
					if(couleur=='r')
						nb.o.rouge=nb.o.rouge*coef;
					if(couleur=='g')
						nb.o.vert=nb.o.vert*coef;
					if(couleur=='b')
						nb.o.bleu=nb.o.bleu*coef;
					if(couleur=='a'){
						nb.o.rouge=nb.o.rouge*coef;
						nb.o.vert=nb.o.vert*coef;
						nb.o.bleu=nb.o.bleu*coef;
					}
					if(nb.o.rouge>(*clair).pixel_t)
						nb.o.rouge=(*clair).pixel_t;
					if(nb.o.vert>(*clair).pixel_t)
						nb.o.vert=(*clair).pixel_t;
					if(nb.o.bleu>(*clair).pixel_t)
						nb.o.bleu=(*clair).pixel_t;
					(*clair).tab[i][j]=nb.couleur;
				}else{
					erreur=1;
				}
			}
		}
		if(erreur==1)
			printf("Mauvais format pour éclairer la luminosité de l'image\n");
	}else{
		printf("Erreur pour allouer de la mémoire lors de la copie de l'image\n");
	}
	return clair;
}

void *contraster_pixmap(pixmap_t *c,float add,int couleur){
	int erreur=0;
	pixmap_t *contraste=NULL;
	contraste=(pixmap_t*)malloc(sizeof(pixmap_t));
	*contraste=*c;
	if(contraste != NULL){
		(*contraste).tab=(long long int**)malloc((*contraste).largeur*sizeof(long long int *));
		for(i = 0; i < (*contraste).largeur; i++)
			(*contraste).tab[i] = malloc((*contraste).hauteur * sizeof(long long int));
		for(i=0;i<(*contraste).largeur;i++){
			for(j=0;j<(*contraste).hauteur;j++){
				if((*contraste).montype==2){
					(*contraste).tab[i][j]=(*c).tab[i][j]+add;
				}else if((*contraste).montype==3){
					nb.couleur=(*c).tab[i][j];
					if(couleur=='r')
						nb.o.rouge=nb.o.rouge+add;
					if(couleur=='g')
						nb.o.vert=nb.o.vert+add;
					if(couleur=='b')
						nb.o.bleu=nb.o.bleu+add;
					if(couleur=='a'){
						nb.o.rouge=nb.o.rouge+add;
						nb.o.vert=nb.o.vert+add;
						nb.o.bleu=nb.o.bleu+add;
					}
					if(nb.o.rouge>(*contraste).pixel_t)
						nb.o.rouge=(*contraste).pixel_t;
					if(nb.o.vert>(*contraste).pixel_t)
						nb.o.vert=(*contraste).pixel_t;
					if(nb.o.bleu>(*contraste).pixel_t)
						nb.o.bleu=(*contraste).pixel_t;
					(*contraste).tab[i][j]=nb.couleur;
				}else{
					erreur=1;
				}

			}
		}		if(erreur==1)
		if(erreur==1)
			printf("Mauvais format pour éclairer la luminosité de l'image\n");
	}else{
		printf("Erreur pour allouer de la mémoire lors de la copie de l'image\n");
	}
	return contraste;
}

