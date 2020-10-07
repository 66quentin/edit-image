#include "filters.h"

void free_filter(filter_t *filtre) {
	if(filtre!=NULL){
		for(int i = 0; i < (*filtre).n; i++){
    			free((*filtre).matrice[i]);
		}
		free((*filtre).matrice);
		free(filtre);
	}
}

filter_t *fuzzy_filter(int n){
	filter_t *fuzzy=NULL;
	if(n>=3 && n%2!=0){
		fuzzy=(filter_t*)malloc(sizeof(filter_t));
		(*fuzzy).n=n;
		(*fuzzy).matrice=(int32_t**)malloc((*fuzzy).n*sizeof(int32_t*));
		for(i = 0; i < (*fuzzy).n; i++)
			(*fuzzy).matrice[i] = malloc((*fuzzy).n * sizeof(int32_t));
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				(*fuzzy).matrice[i][j]=1;
		}
		(*fuzzy).a=n*n;
		(*fuzzy).b=0;
	}else{
		printf("La taille de la matrice doit être impaire et supérieure à 3\n");
	}		
	return fuzzy;
}

filter_t *prewitt_x_filter(pixmap_t *c, int n){
	filter_t *prewitt_x=NULL;
	prewitt_x=(filter_t*)malloc(sizeof(filter_t));
	(*prewitt_x).n=n;
	(*prewitt_x).matrice=(int32_t**)malloc((*prewitt_x).n*sizeof(int32_t*));
	for(i = 0; i < (*prewitt_x).n; i++)
		(*prewitt_x).matrice[i] = malloc((*prewitt_x).n * sizeof(int32_t));
	for(i=0;i<n;i++){
		(*prewitt_x).matrice[i][0]=-1;	
		(*prewitt_x).matrice[i][1]=0;
		(*prewitt_x).matrice[i][2]=1;
	}
	(*prewitt_x).a=6;
	(*prewitt_x).b=ceil((*c).pixel_t/2);			
	return prewitt_x;
}

filter_t *prewitt_y_filter(pixmap_t *c, int n){
	filter_t *prewitt_y=NULL;
	prewitt_y=(filter_t*)malloc(sizeof(filter_t));
	(*prewitt_y).n=n;
	(*prewitt_y).matrice=(int32_t**)malloc((*prewitt_y).n*sizeof(int32_t*));
	for(i = 0; i < (*prewitt_y).n; i++)
		(*prewitt_y).matrice[i] = malloc((*prewitt_y).n * sizeof(int32_t));
	for(i=0;i<n;i++){
		(*prewitt_y).matrice[0][i]=-1;	
		(*prewitt_y).matrice[1][i]=0;
		(*prewitt_y).matrice[2][i]=1;
	}
	(*prewitt_y).a=6;
	(*prewitt_y).b=ceil((*c).pixel_t/2);			
	return prewitt_y;
}

filter_t *sobel_x_filter(pixmap_t *c, int n){
	filter_t *sobel_x=NULL;
	sobel_x=(filter_t*)malloc(sizeof(filter_t));
	(*sobel_x).n=n;
	(*sobel_x).matrice=(int32_t**)malloc((*sobel_x).n*sizeof(int32_t*));
	for(i = 0; i < (*sobel_x).n; i++)
		(*sobel_x).matrice[i] = malloc((*sobel_x).n * sizeof(int32_t));
	for(i=0;i<n;i++){
		(*sobel_x).matrice[i][0]=-1;	
		(*sobel_x).matrice[i][1]=0;
		(*sobel_x).matrice[i][2]=1;
	}
	(*sobel_x).a=8;
	(*sobel_x).b=ceil((*c).pixel_t/2);			
	return sobel_x;
}

filter_t *sobel_y_filter(pixmap_t *c, int n){
	filter_t *sobel_y=NULL;
	sobel_y=(filter_t*)malloc(sizeof(filter_t));
	(*sobel_y).n=n;
	(*sobel_y).matrice=(int32_t**)malloc((*sobel_y).n*sizeof(int32_t*));
	for(i = 0; i < (*sobel_y).n; i++)
		(*sobel_y).matrice[i] = malloc((*sobel_y).n * sizeof(int32_t));
	for(i=0;i<n;i++){
		(*sobel_y).matrice[0][i]=-1;	
		(*sobel_y).matrice[1][i]=0;
		(*sobel_y).matrice[2][i]=1;
	}
	(*sobel_y).a=8;
	(*sobel_y).b=ceil((*c).pixel_t/2);			
	return sobel_y;
}

filter_t *discret_laplace_filter(pixmap_t *c, int n){
	filter_t *laplace=NULL;
	laplace=(filter_t*)malloc(sizeof(filter_t));
	(*laplace).n=n;
	(*laplace).matrice=(int32_t**)malloc((*laplace).n*sizeof(int32_t*));
	for(i = 0; i < (*laplace).n; i++)
		(*laplace).matrice[i] = malloc((*laplace).n * sizeof(int32_t));
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if((j+i)%2==0)
				(*laplace).matrice[i][j]=0;
			if((j+i)%2==1)
				(*laplace).matrice[i][j]=1;
		}
	}
	(*laplace).matrice[1][1]=-4;
	(*laplace).a=1;
	(*laplace).b=ceil((*c).pixel_t/2);			
	return laplace;
}

pixmap_t *apply_filter_pixmap(filter_t *filtre, pixmap_t *pixmap){
	pixmap_t *p=NULL;
	int k=floor((*filtre).n/2);
	p=(pixmap_t*)malloc(sizeof(pixmap_t));
	*p=*pixmap;
	if(p != NULL && filtre!= NULL){
		(*p).tab=(long long int**)malloc((*p).largeur*sizeof(long long int*));
		for(i = 0; i < (*p).largeur; i++)
			(*p).tab[i] = malloc((*p).hauteur * sizeof(long long int));
		for(i=k;i<(*p).largeur-k;i++){
			for(j=k;j<(*p).hauteur-k;j++){//Application de la formule
				r=0;
				v=0;
				b=0;
				for(k1=-k;k1<=k;k1++){
					for(k2=-k;k2<=k;k2++){
						if((*p).montype==1 ||(*p).montype==2)
							(*p).tab[i][j]=(*p).tab[i][j]+(*pixmap).tab[i+k1][j+k2]*(*filtre).matrice[k+k1][k+k2];
						if((*p).montype==3){
							nb.couleur=(*pixmap).tab[i+k1][j+k2];
							r=r+nb.o.rouge*(*filtre).matrice[k+k1][k+k2];
							v=v+nb.o.vert*(*filtre).matrice[k+k1][k+k2];
							b=v+nb.o.bleu*(*filtre).matrice[k+k1][k+k2];
						}
					}
				}
				if((*p).montype==1||(*p).montype==2){
					(*p).tab[i][j]=(*p).tab[i][j]/(*filtre).a+(*filtre).b;
					if((*p).tab[i][j]<0)
						(*p).tab[i][j]=0;
				}
				if((*p).montype==3){
					r=r/(int)(*filtre).a+(*filtre).b;
					v=v/(int)(*filtre).a+(*filtre).b;
					b=b/(int)(*filtre).a+(*filtre).b;
					if(r<0)
						r=0;
					if(v<0)
						v=0;
					if(b<0)
						b=0;
				
					nb.o.rouge=r;
					nb.o.vert=v;
					nb.o.bleu=b;
					(*p).tab[i][j]=nb.couleur;
				}
		
			}
		}
		for(i=0;i<(*p).largeur;i++){
			for(j=0;j<(*p).hauteur;j++){
				if((*p).montype==3){
					nb.couleur=(*p).tab[i][j];
					if(nb.o.rouge<0)
						nb.o.rouge=0;
					if(nb.o.vert<0)
						nb.o.vert=0;
					if(nb.o.bleu<0)
						nb.o.bleu=0;
					(*p).tab[i][j]=nb.couleur;
				}else{
					if((*p).tab[i][j]<0)
						(*p).tab[i][j]=0;
				}
			}
		}
	}else{
		printf("Il y a une erreur dans l'image ou le filtre \n");
	}
	return p;
}
