#include "pixmap.h"

//Ouverture d'image
pixmap_t *load_pixmap(char *nom){
	pixmap_t *p=NULL;
	p=(pixmap_t*)malloc(sizeof(pixmap_t));
	FILE* img = fopen(nom, "r");
	if(img != NULL && p != NULL){

		fscanf(img,"%s %s",type,testcomment);
		//-48 pour obtenir le chiffre en caractère et non en ASCII
		(*p).montype=type[1]-48;

		if((*p).montype==1){
			//Si la ligne commence par un # alors on ignore
			if(strcmp(testcomment,"#")==0){
				//%*[^\n]\n pour sauter la ligne de commentaire
				fscanf(img,"%*[^\n]\n %d %d", &(*p).largeur, &(*p).hauteur);
			}else{
				fscanf(img,"%d",  &(*p).hauteur);
				(*p).largeur=atoi(testcomment);
			}
		}
		if((*p).montype==2 || (*p).montype==3){
			if(strcmp(testcomment,"#")==0){
				fscanf(img,"%*[^\n]\n %d %d %d",&(*p).largeur, &(*p).hauteur, &(*p).pixel_t);
			}else{
				fscanf(img,"%d %d", &(*p).hauteur, &(*p).pixel_t);
				(*p).largeur=atoi(testcomment);
			}
		}
		(*p).tab=(long long int**)malloc((*p).largeur*sizeof(long long int *));
		for(i = 0; i < (*p).largeur; i++)
			(*p).tab[i] = malloc((*p).hauteur * sizeof(long long int));
		if((*p).montype==3){
			for(i=0;i<(*p).largeur;i++){
				for(j=0;j<(*p).hauteur;j++){
					fscanf(img,"%d", &r);
					fscanf(img,"%d", &v);
					fscanf(img,"%d", &b);
					nb.o.rouge=r;
					nb.o.vert=v;
					nb.o.bleu=b;
					(*p).tab[i][j]=nb.couleur;
				}
			}
		}else if( (*p).montype==1){
			for(i=0;i<(*p).largeur;i++){
				for(j=0;j<(*p).hauteur;j++){
					fscanf(img,"%c", &z);
					(*p).tab[i][j] = (int)z-48;
				}
			}
		}else if((*p).montype==2){
			for(i=0;i<(*p).largeur;i++){
				for(j=0;j<(*p).hauteur;j++)
					fscanf(img,"%lld", &(*p).tab[i][j] );
			}
		}
		
			
	}else{
		printf("Erreur lors de l'ouverture de l'image ou de l'allocation de la mémoire\n");
	}
	fclose(img);
	return p;
}


//Libérer la mémoire
void free_pixmap(pixmap_t *c) {
	for(int i = 0; i < (*c).largeur; i++){
    		free((*c).tab[i]);
	}
	free((*c).tab);
	free(c);
}


//Copier une image
pixmap_t *copy_pixmap(pixmap_t *c) {
	pixmap_t *copy=NULL;
	copy=(pixmap_t*)malloc(sizeof(pixmap_t));
	*copy=*c;
	if(copy != NULL){
		(*copy).tab=(long long int**)malloc((*copy).largeur*sizeof(long long int *));
		for(i = 0; i < (*copy).largeur; i++)
			(*copy).tab[i] = malloc((*copy).hauteur * sizeof(long long int));
		for(i=0;i<(*copy).largeur;i++){
			for(j=0;j<(*copy).hauteur;j++)
				(*copy).tab[i][j]=(*c).tab[i][j];
		}
	}else{
		printf("Erreur pour allouer de la mémoire lors de la copie de l'image");
	}
	return copy;
}


//Enregistrer une image
void *save_pixmap(pixmap_t *c,char *nom){
	if((nom[strlen(nom)-2]=='p' && (*c).montype==3) || (nom[strlen(nom)-2]=='b' && (*c).montype==1) || (nom[strlen(nom)-2]=='g' && (*c).montype==2)){
		FILE* img = fopen(nom, "w");
		if((*c).montype==3 || (*c).montype==2)
			fprintf(img,"P%d\n%d %d\n%d\n", (*c).montype, (*c).largeur, (*c).hauteur, (*c).pixel_t);
		if((*c).montype==1){
			fprintf(img,"P%d\n%d %d\n", (*c).montype, (*c).largeur, (*c).hauteur);
			for(i=0;i<(*c).largeur;i++){
				for(j=0;j<(*c).hauteur;j++){
					if((*c).tab[i][j]!=-38){
						fprintf(img,"%lld", (*c).tab[i][j]);
						y++;
						if(y%70==0 && y!=0)
							fprintf(img,"\n");
						}
				}
			}
		}
		if((*c).montype==3){
			for(i=0;i<(*c).largeur;i++){
				for(j=0;j<(*c).hauteur;j++){
					nb.couleur=(*c).tab[i][j];
					fprintf(img,"%d\n", nb.o.rouge);
					fprintf(img,"%d\n", nb.o.vert);
					fprintf(img,"%d\n", nb.o.bleu);
				}
			}
		}else if((*c).montype==2){
			for(i=0;i<(*c).largeur;i++){
				for(j=0;j<(*c).hauteur;j++)
					fprintf(img,"%lld\n", (*c).tab[i][j]);
			}
		}
		fclose(img);
	}else{
		printf("Mauvais format d'image pour l'enregistrement:format P%d pour extension .p%cm\n",(*c).montype,nom[strlen(nom)-2]);
	}
	return 0;
}

