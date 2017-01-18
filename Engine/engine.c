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

	for (int i = 0; i < P1.nbListe; i++) {
			Noeud* n1 = trouve_premier(P1.pierres[i], coord);
			if(n1 != NULL) {
				return false;
			}
	}
	for (int i = 0; i < P2.nbListe; i++) {
			Noeud* n2 = trouve_premier(P2.pierres[i], coord);
			if(n2 != NULL) {
					return false;
			}

	}

	return true;
}

Player getCurrentPlayer() {
	int tour = getCptTours();
	if( tour % 2 == 0) {
		return P1; // si 0, retourn player Blanc
	}
	return P2; // si 1, return player Noir
}

void getAdjacent(int xp, int yp, int* tab) {
	tab[0] = getCoord(xp, yp - 24);
	tab[1] = getCoord(xp, yp + 24);
	tab[2] = getCoord(xp-24, yp);
	tab[3] = getCoord(xp+24, yp);
}

Adjacent isAnyPierreAdjacent(int* tab, Player p) {
	Noeud* n1;
	Adjacent adj;
	adj.adjs = malloc(sizeof(int)*4);
	adj.nbAdj = 0;
	for (int i = 0; i < p.nbListe; i++) {
		for(int j = 0; j < 4; j++) {
				n1 = trouve_premier(p.pierres[i], tab[j]);
				if(n1 != NULL) {
					adj.adjs[adj.nbAdj] = i;
					adj.nbAdj++;
				}
		}
	}
	return adj;
}

Player mergeChaines(Adjacent tab, Player p) {
	Liste* grosseListe = liste_vide();
	for(int i = 0; i < tab.nbAdj;i++) {
		Liste* l = p.pierres[tab.adjs[i]];
		while(est_vide(l == false) {
			push_front(l, front_val(l));
			pop_front(l);
		}
	}
}

int addPierre(int xp, int yp) {
	Player p = getCurrentPlayer();
	int tab[4];
	getAdjacent(xp,yp, tab);
	int coord = getCoord(xp, yp);

	Adjacent anyAdjacent = isAnyPierreAdjacent(tab,p);
	if(anyAdjacent.nbAdj == 1)  {
		push_front(p.pierres[anyAdjacent.adjs[0]], coord);
	} else if(anyAdjacent.nbAdj > 1) {

	} else {
		p.pierres[p.nbListe] = liste_vide();
		push_front(p.pierres[p.nbListe], coord);
		p.nbListe++;
	}
	printf("Player %s     ", p.nom);
	for(int i =0; i < p.nbListe; i++) {
		print(p.pierres[i]);
		printf("\n");
	}
	printf("\n");

	if(p.type == Blanc) {
		P1 = p;
	} else {
		P2 = p;
	}
	free(anyAdjacent.adjs);
	return coord;
}

Player init_player(char* nom, PlayerType playerType) {
	Player p;
	p.nom = nom;
	p.type = playerType;
	p.pierres = malloc(sizeof(Liste*) * getNbPierres() * getNbPierres());
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
