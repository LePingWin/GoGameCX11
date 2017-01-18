all: affichage

clean:
	rm affichage dessine.o libdessine.a engine.o

IHM/libdessine.a: IHM/dessine.c IHM/dessine.h
	cd IHM; gcc -g -c dessine.c
	cd IHM; ar -r libdessine.a dessine.o

Engine/engine.o: Engine/engine.c Engine/engine.h
	cd Engine; gcc -g -c engine.c

Engine/rules.o: Engine/rules.c Engine/rules.h
	cd Engine; gcc -g -c rules.c

ListLib/lst_double.o:  ListLib/lst_double.c ListLib/lst_double.h
	cd ListLib; gcc -g -c lst_double.c

Tab1DLib/tab1.o:  Tab1DLib/tab1.c Tab1DLib/tab1.h
	cd Tab1DLib; gcc -g -c tab1.c

affichage:  IHM/libdessine.a Tab1DLib/tab1.o Engine/engine.o Engine/engine.h Engine/rules.o Engine/rules.h ListLib/lst_double.o ListLib/lst_double.h IHM/affichage.c IHM/dessine.h
	cd IHM; gcc -g affichage.c ../Tab1DLib/tab1.o ../ListLib/lst_double.o ../Engine/rules.o ../Engine/engine.o -o affichage  -L. -ldessine -lX11
