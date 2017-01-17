#include "engine.h"
#include <string.h>
#include "rules.h"

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
	Player p1;
	p1.nom = "P1";
	PlayerType pt = Blanc;
	p1.type = pt;
	p1.pierres = malloc(sizeof(Liste*));
}
