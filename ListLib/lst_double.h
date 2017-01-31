#ifndef lst_double
#define lst_double
#include <stdlib.h>
#include <stdio.h>


typedef int bool;
#define true 1
#define false 0

typedef struct SNoeud
{
	int value;
	struct SNoeud* next;
	struct SNoeud* prec;
} Noeud;
typedef struct SListe
{
	Noeud* tete;
	Noeud* queue;
	int nbNoeud;

}Liste;

bool est_vide(Liste* l);

Liste* liste_vide();

Noeud* push_front(Liste* l, int v);

void pop_front(Liste* l);

int front_val(Liste* l);

Noeud* push_back(Liste* l, int v);


void pop_back(Liste* l);

int back_val(Liste* l);

void print(Liste* l);

Noeud* trouve_premier(Liste* l, int v);

Noeud* trouve_dernier(Liste* l, int v);

void retire(Liste* l, Noeud* n);

Noeud* insert_after(Liste* l,Noeud* c, int v);

bool equals(Liste* l1, Liste* l2);

void applyCompteur(Liste* l,int* cpt,void (*fonction)(int*,int*));

void apply(Liste* l,void (*fonction)(int*));

#endif
