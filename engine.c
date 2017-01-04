#include "engine.h"
#include <string.h>

//attributs
int taille_pierre;
int nb_pierres;


//accesseur
int getNbPierres() {
	return nb_pierres;
}

int getTaillePierre() {
  return taille_pierre;
}


//méthode d'initialisation
void init_go(int p, int tp) {
	nb_pierres = p;
  taille_pierre = tp;
}
