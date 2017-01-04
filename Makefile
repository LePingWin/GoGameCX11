all: affichage

clean:
	rm affichage dessine.o libdessine.a engine.o

affichage: IHM/affichage.c IHM/dessine.h IHM/libdessine.a Engine/engine.o Engine/engine.h
	cd IHM; gcc -g affichage.c ../Engine/engine.o -o affichage  -L. -ldessine -lX11

IHM/libdessine.a: IHM/dessine.c IHM/dessine.h
	cd IHM; gcc -g -c dessine.c
	cd IHM; ar -r libdessine.a dessine.o

Engine/engine.o: Engine/engine.c Engine/engine.h
	cd Engine; gcc -g -c engine.c 
