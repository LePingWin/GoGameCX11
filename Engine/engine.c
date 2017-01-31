#include "engine.h"
#include <string.h>

//attributs
int taille_pierre;
int nb_pierres;
int cpt_tours;
Player P1;
Player P2;
int* plateauT_1;
int* plateau;
int* tourSuiv;

//accesseur
int getNbPierres() {
	return nb_pierres+1;
}

int getTaillePierre() {
  return taille_pierre;
}

int getCptTours() {
	return cpt_tours;
}

void incrementeCptTours() {
	int size = getNbPierres()*getNbPierres();
	plateauT_1 = copyPlateau(plateau,size);
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

Player getOppositePlayer() {
	int tour = getCptTours();
	if( tour % 2 == 0) {
		return P2; // si 1, retourn player Blanc
	}
	return P1; // si 0, return player Noir
}


Player getPlayer(int player) {
	if(player == 0) {
		return P1;
	}
	return P2;
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

Adjacent isAnyPierreAdjacentInEveryTable(int* tab) {
	Noeud* n1;
	Adjacent adj;
	adj.adjs = malloc(sizeof(int)*4);
	adj.nbAdj = 0;
	Player p;
	for(int i = 0; i < 2; i++) {
		if(i == 0) {
			p = P1;
		} else {
			p = P2;
		}
		for (int i = 0; i < p.nbListe; i++) {
			for(int j = 0; j < 4; j++) {
					n1 = trouve_premier(p.pierres[i], tab[j]);
					if(n1 != NULL) {
						adj.adjs[adj.nbAdj] = i;
						adj.nbAdj++;
					}
			}
		}
	}
	return adj;
}

Player mergeChaines(Adjacent tab, Player p, int c) {
	Liste* grosseListe = liste_vide();
	for(int i = 0; i < tab.nbAdj;i++) {
		Liste* l = p.pierres[tab.adjs[i]];
		while(est_vide(l) == false) {
			push_front(grosseListe, front_val(l));
			pop_front(l);
		}
	}
	p.pierres[p.nbListe] = grosseListe;
	p.nbListe++;
	push_front(p.pierres[p.nbListe-1], c);
	for (int i = 0; i < tab.nbAdj; i++) {
		//printf("nb tour %d", tab.adjs[i]);
		p = supr_elem(p,tab.adjs[i]);
	}

	return p;
}

Player supr_elem(Player p, int position ) {
	removePierreInPlateau(p.pierres[position]);
	swap_elt(p.pierres,position,p.nbListe-1);
	//printf("suppr element %d", p.nbListe-1);

	//free(p.pierres[p.nbListe-1]);
	p.nbListe--;
	return p;
}

void removePierreInPlateau(Liste* l) {

	while(est_vide(l) == false) {
	  int coord = front_val(l);
		int x = getX(coord);
		int y = getY(coord);
		bool stop = false;
		int cpt = 0;
		int resX = -1;
		int resY = -1;
		//printf("hello");
		//ajuster les coordonées
		pop_front(l);
		while(resX == -1 || resY == -1) {
			if((x - 50 - cpt*getTaillePierre()) == 0) {
				resX = cpt;
				//printf("resX = %d", resX);
			}
			if((y - 50 - cpt*getTaillePierre()) == 0) {
				resY = cpt;
				//printf("resY = %d", resY);
			}
			cpt++;
		}
		plateau[resY*getNbPierres() + resX] = 0;
	}

}

void getCptDegre(int* val,int* cpt){
	int tab[4];
	getAdjacent(getX(*val),getY(*val), tab);
	Adjacent adj = isAnyPierreAdjacentInEveryTable(tab);
	*cpt += 4-adj.nbAdj;
}

int getDegreLiberte(Liste* l) {
	Liste* copyListe = liste_vide();
	int cpt = 0;
	applyCompteur(l,&cpt,getCptDegre);
	return cpt;
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
		p = mergeChaines(anyAdjacent,p,coord);
	} else {
		p.pierres[p.nbListe] = liste_vide();
		push_front(p.pierres[p.nbListe], coord);
		p.nbListe++;
	}
	//printf("Player %s     ", p.nom);
	for(int i =0; i < p.nbListe; i++) {
		print(p.pierres[i]);
		printf("Nb degre de liberte %d", getDegreLiberte(p.pierres[i]));
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


bool capturePion() {
	Player p = getOppositePlayer();

	bool refresh = false;
	for(int j = 0; j < p.nbListe; j++) {
		if(getDegreLiberte(p.pierres[j]) == 0) {
			print(p.pierres[j]);
			p = supr_elem(p,j);
			refresh = true;
		}
	}
	if(p.type == Blanc) {
		printf("blanc");
		P1 = p;
	} else {
		P2 = p;
	}
	return refresh;
}

void fill_plateau(int x, int y, int playerValue) {
	plateau[y*getNbPierres() + x] = playerValue;
}

void printPlateau() {
	for(int i = 0; i < getNbPierres(); i++) {
			for(int j = 0; j < getNbPierres(); j++) {
				printf("[%d]",plateau[i*getNbPierres() + j]);
		}
		printf("\n");
	}
}


bool repetition(int x, int y,int playerValue) {
	int size = getNbPierres()*getNbPierres();

	//Copie des plateaux à t-1 et t+1
	tourSuiv = copyPlateau(plateau,size);
	tourSuiv[y*getNbPierres() + x] = playerValue;
		//Parcours des deux tableaux
		for (int i = 0; i < size; i++) {
			if(tourSuiv[i] == playerValue){
				if(tourSuiv[i] != plateauT_1[i]){
					return false;
				}
			}
		}
		return true;
}

//copie les plateaux
int* copyPlateau(int* const src, size_t len) {
	int* p = malloc(len*sizeof(int));
	memcpy(p, src,len*sizeof(int));
	return p;
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
	plateau = calloc(getNbPierres()*getNbPierres(),sizeof(int));
	plateauT_1 = copyPlateau(plateau,getNbPierres()*getNbPierres());
	P1 = init_player("P1", blanc);
	P2 = init_player("P2", noir);
	cpt_tours = 1;
}
