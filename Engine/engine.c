#include "engine.h"
#include <string.h>

//attributs
int taille_pierre;
int nb_pierres;
int cpt_tours;
Player P1;
Player P2;

//accesseur
int getNbPierres() {
	return nb_pierres;
}

int getTaillePierre() {
  return taille_pierre;
}

int getCptTours() {
	return cpt_tours;
}

void incrementeCptTours() {
	cpt_tours++;
}

bool intersection_est_vide(int coord) {
	Noeud* n1;
	Noeud* n2;
	for (int i = 0; i < P1.nbListe; i++) {
			n1 = trouve_premier(P1.pierres[i], coord);
			if(n1 != NULL)
				return false;
	}
	for (int i = 0; i < P2.nbListe; i++) {
			n2 = trouve_premier(P2.pierres[i], coord);
			if(n2 != NULL)
				return false;
	}
	return true;
}

Player* getCurrentPlayer() {
	int tour = getCptTours();
	if( tour % 2 == 0) {
		return &P1; // si 0, retourn player Blanc
	}
	return &P2; // si 1, return player Noir
}

void getAdjacent(int xp, int yp, int* tab) {
	tab[0] = getCoord(xp, yp - 24);
	tab[1] = getCoord(xp, yp + 24);
	tab[2] = getCoord(xp-24, yp);
	tab[3] = getCoord(xp+24, yp);
}

int isAnyPierreAdjacent(int* tab, Player* p) {
	Noeud* n1;
	for (int i = 0; i < p->nbListe; i++) {
		for(int j = 0; j < 4; j++) {
				n1 = trouve_premier(p->pierres[i], tab[j]);
				if(n1 != NULL) {
					return i;
				}
		}
	}
	return -1;
}

int addPierre(int xp, int yp) {
	Player* p = getCurrentPlayer();
	int tab[4];
	getAdjacent(xp,yp, tab);
	int coord = getCoord(xp, yp);

	if(p->nbListe != 0) {
		int anyAdjacent = isAnyPierreAdjacent(tab,p);
		if(anyAdjacent != -1) {
			push_front(p->pierres[anyAdjacent], coord);
		}else {
			p->pierres[p->nbListe] = liste_vide();
			push_front(p->pierres[p->nbListe], coord);
			p->nbListe++;
		}
	} else {
		p->pierres[p->nbListe] = liste_vide();
		push_front(p->pierres[p->nbListe], coord);
		p->nbListe++;
	}

	for(int i =0; i < p->nbListe; i++) {
		printf("\n");
		print(p->pierres[i]);
		printf("\n");
	}
	return coord;
}

Player init_player(char* nom, PlayerType playerType) {
	Player p;
	p.nom = nom;
	p.type = playerType;
	Liste* tabList[getNbPierres()*getNbPierres()];
	p.pierres = tabList;
	p.nbListe = 0;
	return p;
}

//méthode d'initialisation
void init_go(int p, int tp) {
	nb_pierres = p;
  taille_pierre = tp;
	PlayerType blanc = Blanc;
	PlayerType noir = Noir;
	P1 = init_player("P1", blanc);
	P2 = init_player("P2", noir);
	cpt_tours = 1;
}
