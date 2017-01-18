// A COMPILER avce -lX11

#include <stdlib.h>
#include <stdio.h>
#include "rules.h"

/**
 * Nombre de pierres
 */
int getNbPierres();

/**
 * taille des pierres
 */
int getTaillePierre();

/**
 * tour actuel
 */
int getCptTours();
/**
 * incrémente le tour actuel de 1
 */
void incrementeCptTours();
/**
 * vérifie qu'il n'y a pas de pierre sur l'intersection
 */
bool intersection_est_vide(int coord);
/**
 * player a qui le tour
 */
Player getCurrentPlayer();
/**
 * Récupère un tableau des pierres adjacentes possibles
 */
void getAdjacent(int xp, int yp, int* tab);
  /**
   * regarde si une pierre adjacente est deja dans une liste du joueur courant
   */
Adjacent isAnyPierreAdjacent(int* tab, Player p);
/**
 * regarde si une pierre adjacente est deja dans une liste de tous les joueurs 
 */
Adjacent isAnyPierreAdjacentInEveryTable(int* tab);
/**
 * merge deux chaines lorsque qu'une nouvelle pierre est adjacente à une ou plusieurs pierres de listes différentes
 */
Player mergeChaines(Adjacent tab, Player p, int c);
/**
 * supprime un élément du tableau de pierre
 */
Player supr_elem(Player p, int position );

/**
 * ajouter une pierre dans la bonne liste
 */
int addPierre(int xp, int yp);
/**
 * initialise les joueurs
 */
Player init_player(char* nom, PlayerType playerType);
/**
 * initialisation jeu de go
 * p: pierre
 */
void init_go(int p, int tp);
