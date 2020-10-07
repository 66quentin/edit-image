projet: pixmap.o transformations.o filters.o getopt.o
	gcc -o projet pixmap.o -lm transformations.o -lm filters.o -lm getopt.o

pixmap.o : pixmap.c
	gcc -c -Wall pixmap.c

transformations.o : transformations.c
	gcc -c -Wall transformations.c

filters.o : filters.c
	gcc -c -Wall filters.c

getopt.o : getopt.c
	gcc -c -Wall getopt.c

clean :
	rm -f projet *.o projet 

a = $(shell echo "Pour plus d'informations: ./projet --help")
$(info $(a))
