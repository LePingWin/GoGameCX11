#Chemin de recherche des fichiers
VPATH = src/Engine src/IHM lib/Liste lib/Tab lib/Dessine header/
#Compilateur
CC=gcc
# Recherche des .C pour la cible sans librairies
SRC=$(wildcard src/IHM/*.c src/Engine/*.c lib/Liste/*.c lib/Tab/*.c lib/Dessine/*.c)
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))
# Recherche du fichier .c contenant le main
SRCMAIN=$(wildcard src/IHM/*.c)
OBJMAIN=$(notdir $(patsubst %.c,%.o,$(SRCMAIN)))
# Recherche des fichiers.c contenant la "librairie"
LIB=$(wildcard src/Engine/*.c lib/Liste/*.c lib/Tab/*.c lib/Dessine/*.c)
LIBOBJ=$(notdir $(patsubst %.c,%.o,$(LIB)))

# Chemin d'accès à la lib dynamique
LD_LIBRARY_PATH=~/Documents/Laurent/Prog/Go/GoGameCX11/

# Nom de l'éxecutable
PROG=affichage
# Cible appelée par défaut
all: $(PROG)


# Programme sans librairie
$(PROG): $(OBJ)
	$(CC) -g -o $@ $^ -lX11
# Programme avec librairie statique
statique: $(OBJMAIN) libGo.a
	$(CC) -g -o $(PROG) $^ -L. -lGo -lX11

# Programme avec librairie dynamique
dynamique: $(OBJMAIN) $(LD_LIBRARY_PATH)libGo.so
	$(CC) -g -o $(PROG) $^ -L. -lGo -lX11


# Traitements des fichiers *.a *.so *.c
%.a: $(LIBOBJ)
	ar -rv libGo.a $@ $^

%.so: $(LIBOBJ)
	$(CC) -o  $@ -shared $^

%.o: %.c %.h
	$(CC) -g -c $< -fPIC

#Nettoyage des fichiers de pré-compilation
clean:
	rm $(PROG) *.o *.a *.so
