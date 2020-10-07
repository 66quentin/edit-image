#include "getopt.h"

void enregistrer(pixmap_t *a, char *nom, int ccc){
	if(ccc==jj)
		save_pixmap(a,nom);
}

int main (int argc, char ** argv) {
	ii=0; // Correspond à l'odre des options
	while ((ch = getopt_long(argc, argv, "a:b:cdefgh:i:j:k:l:m:n:o:p:q:r:s:tuvwx", long_options, 0)) != -1){
		ii++;
		switch (ch){
			case 'a':
             			source=optarg;
				s=1;
             			break;
			case 'b':
             			destination=optarg;
				d=1;
             			break;
			case 'c':
             			opt.c=ii;
             			break;
			case 'd':
             			opt.d=1;
             			break;
			case 'e':
             			opt.e=ii;
             			break;
			case 'f':
             			opt.f=ii;
             			break;
			case 'g':
             			opt.g=ii;
             			break;
			case 'h':
             			opt.h=ii;
				arg1=atoi(optarg);
             			break;
			case 'i':
             			opt.i=ii;
				arg11=atof(optarg);
             			break;
			case 'j':
             			opt.j=ii;
				arg12=atof(optarg);
             			break;
			case 'k':
             			opt.k=ii;
				arg2=atoi(optarg);
             			break;
			case 'l':
             			opt.l=ii;
				arg3=atoi(optarg);
             			break;
			case 'm':
             			opt.m=ii;
				arg4=atoi(optarg);
             			break;
			case 'n':
             			opt.n=ii;
				arg5=atoi(optarg);
             			break;
			case 'o':
             			opt.o=ii;
				arg6=atoi(optarg);
             			break;
			case 'p':
             			opt.p=ii;
				arg7=atoi(optarg);
             			break;
			case 'q':
             			opt.q=ii;
				arg8=atoi(optarg);
             			break;
			case 'r':
             			opt.r=ii;
				arg9=atoi(optarg);
             			break;
			case 's':
             			opt.s=ii;
				arg10=atoi(optarg);
             			break;
			case 't':
             			opt.t=ii;
             			break;
			case 'u':
             			opt.u=ii;
             			break;
			case 'v':
             			opt.v=ii;
             			break;
			case 'w':
             			opt.w=ii;
             			break;
			case 'x':
             			opt.x=ii;
             			break;
   		}
	}

	//Option --help
	if(opt.d==1){
		printf("Ecrire ./projet --input [source] --outup [destination] OPTIONS\nAvec les options suivantes:\n");
		printf("--save-temps: sauvegarde le résultat de différents filtres successifs\n");
		printf("--reverse_x: Renverse l'image horizontalement\n");
		printf("--reverse_y: Renverse l'image verticalement\n");
		printf("--reverse_xy: Renverse l'image horizontalement et verticalement\n");
		printf("--gray [ARG]: Convertir l'image en niveau de gris. Argument de la forme aaabbbccc avec aaa+bbb+ccc=1000 (image devient P2)\n");
		printf("--binarise [ARG]: Convertit l'image en noir et blanc. Il faut rentrer le ratio de binarisation, ex:0.5 (image devient P1)\n");
		printf("--binarise_inverse [ARG]: Convertir l'image en noir et blanc et inverse les couleurs. Il faut entrer le ratio (image devient P1)\n");
		printf("--brightness_X [ARG]: Augmente la luminosité. Avec X=r(red) ou g(green) ou b(blue) ou a(all)\n");
		printf("--contrast_X [ARG]: Contraste les couleurs. Avec X=r(red) ou g(green) ou b(blue) ou a(all)\n");
		printf("--fuzzy [ARG]: Floute l'image avec pour argument la taille de la matrice carrée du filtre (impaire>=3)\n");
		printf("--prewitt_x: Applique le filtre prewitt horizontalement\n");
		printf("--prewitt_y: Applique le filtre prewitt verticalement\n");
		printf("--sobel_x: Applique le filtre sobel horizontalement\n");
		printf("--sobel_y: Applique le filtre sobel verticalement\n");
		printf("--laplace: Applique le filtre laplace\n");
		printf("/!\\L'extension de l'image doit correspondre à son format\n");
	}
	if (s==1 && d==1){
		pixmap_t * pix=load_pixmap(source);

		for(jj=1; jj<=ii;jj++){ //Boucle pour éxecuter les options dans l'ordre
			if(opt.e==jj){
				pixmap_t * opte=reverse_pixmap(pix,X_AXIS);
				pix=opte;
			}
			if(opt.f==jj){
				pixmap_t * optf=reverse_pixmap(pix,Y_AXIS);
				pix=optf;
			}
			if(opt.g==jj){
				pixmap_t * optg=reverse_pixmap(pix,XY_AXIS);
				pix=optg;
			}
			if(opt.h==jj){
				aa=(arg1-arg1%(int)pow(10,6))/(float)pow(10,9);
				bb=(arg1%(int)pow(10,6)-arg1%(int)pow(10,3))/(float)pow(10,6);
				cc=(arg1%(int)pow(10,3))/(float)pow(10,3);
				pixmap_t * opth=tranform_to_gray_pixmap(pix,aa,bb,cc);
				pix=opth;
			}
			if(opt.i==jj){
				pixmap_t * opti=binarize_pixmap(pix,arg11,1);
				pix=opti;
			}
			if(opt.j==jj){
				pixmap_t * optj=binarize_pixmap(pix,arg12,0);
				pix=optj;
			}
			if(opt.k==jj){
				pixmap_t * optk=eclairer_pixmap(pix,arg2,'r');
				pix=optk;
			}
			if(opt.l==jj){
				pixmap_t * optl=eclairer_pixmap(pix,arg3,'g');
				pix=optl;
			}
			if(opt.m==jj){
				pixmap_t * optm=eclairer_pixmap(pix,arg4,'b');
				pix=optm;
			}
			if(opt.n==jj){
				pixmap_t * optn=eclairer_pixmap(pix,arg5,'a');
				pix=optn;
			}
			if(opt.o==jj){
				pixmap_t * opto=contraster_pixmap(pix,arg6,'r');
				pix=opto;
			}
			if(opt.p==jj){
				pixmap_t * optp=contraster_pixmap(pix,arg7,'g');
				pix=optp;
			}
			if(opt.q==jj){
				pixmap_t * optq=contraster_pixmap(pix,arg8,'b');
				pix=optq;
			}
			if(opt.r==jj){
				pixmap_t * optr=contraster_pixmap(pix,arg9,'a');
				pix=optr;
			}
			if(opt.s==jj){
				filter_t * fuzzy=fuzzy_filter(arg10);
				pixmap_t * opts=apply_filter_pixmap(fuzzy,pix);
				pix=opts;
				enregistrer(pix,"fuzzy.ppm" ,opt.c);
				free_filter(fuzzy);
			}
			if(opt.t==jj){
				filter_t * prewitt_x=prewitt_x_filter(pix,3);
				pixmap_t * optt=apply_filter_pixmap(prewitt_x,pix);
				pix=optt;
				enregistrer(pix,"prewitt_x.ppm" ,opt.c);
				free_filter(prewitt_x);
			}
			if(opt.u==jj){
				filter_t * prewitt_y=prewitt_y_filter(pix,3);
				pixmap_t * optu=apply_filter_pixmap(prewitt_y,pix);
				pix=optu;
				enregistrer(pix,"prewitt_y.ppm" ,opt.c);
				free_filter(prewitt_y);
			}
			if(opt.v==jj){
				filter_t * sobel_x=sobel_x_filter(pix,3);
				pixmap_t * optv=apply_filter_pixmap(sobel_x,pix);
				pix=optv;
				enregistrer(pix,"sobel_x.ppm" ,opt.c);
				free_filter(sobel_x);
			}
			if(opt.w==jj){
				filter_t * sobel_y=sobel_y_filter(pix,3);
				pixmap_t * optw=apply_filter_pixmap(sobel_y,pix);
				pix=optw;
				enregistrer(pix,"sobel_y.ppm" ,opt.c);
				free_filter(sobel_y);
			}
			if(opt.x==jj){
				filter_t * laplace=discret_laplace_filter(pix,3);
				pixmap_t * optx=apply_filter_pixmap(laplace,pix);
				pix=optx;
				enregistrer(pix,"laplace.ppm" ,opt.c);
				free_filter(laplace);
			}
	
		}
		save_pixmap(pix,destination);
		free_pixmap(pix);
	}else if((s==-1 || d==-1) && opt.d !=1){
			printf("Il manque le fichier source ou destination (--input ou --outup)\n");
			printf("./projet --help pour plus d'informations\n");
	}
	return 0;
}
