all: affichage

clean:
	rm affichage dessine.o libdessine.a

affichage: affichage.c dessine.h libdessine.a engine.h engine.o
	gcc -g affichage.c engine.o -o affichage  -L. -ldessine -lX11

libdessine.a: dessine.c dessine.h
	gcc -g -c dessine.c
	ar -r libdessine.a dessine.o

engine.o: engine.c engine.h
	gcc -g -c engine.c
