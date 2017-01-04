all: affichage

clean:
	rm affichage dessine.o libdessine.a engine.o

affichage: IHM/affichage.c IHM/dessine.h IHM/libdessine.a Engine/engine.o Engine/engine.h ListLib/lst_double.o ListLib/lst_double.h
	gcc -g IHM/affichage.c Engine/engine.o ListLib/lst_double.o -o IHM/affichage  -L./IHM -ldessine -lX11

libdessine.a: IHM/dessine.c IHM/dessine.h
	gcc -g -c IHM/dessine.c
	ar -r IHM/libdessine.a IHM/dessine.o

Engine/engine.o: Engine/engine.c Engine/engine.h
	gcc -g -c Engine/engine.c

lst_double.o:  ListLib/lst_double.c ListLib/lst_double.h
	gcc -g -c ListLib/lst_double.c
