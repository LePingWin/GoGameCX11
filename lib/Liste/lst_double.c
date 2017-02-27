#include <stdio.h>
#include <stdlib.h>
#include "lst_double.h"

bool est_vide(Liste* l){
	if(l->nbNoeud == 0){
		return true;
	}
	return false;
}

Liste* liste_vide(){
	Liste* l1 = malloc(sizeof(Liste*));
	l1->tete = NULL;
	l1->queue = NULL;
	l1->nbNoeud = 0;
	return l1;
}

Noeud* push_front(Liste* l, int v){
	Noeud* n1 = malloc(sizeof(Noeud));
	n1->value = v;
	n1->prec = NULL;
	n1->next = l->tete;

	if(est_vide(l) == 1){
		l->queue = n1;
	}else{
		l->tete->prec = n1;
	}
	l->tete = n1;
	l->nbNoeud++;
	return n1;
}

void pop_front(Liste* l){
	if(est_vide(l) == 1){
		return;
	}
	Noeud* tmp = l->tete;
	if(l->tete != NULL){
		l->tete = l->tete->next;
		free(tmp);
		l->nbNoeud--;
	}
}

int front_val(Liste* l){
	if(est_vide(l) == 1){
		return 0;
	}
	return l->tete->value;
}

Noeud* push_back(Liste* l, int v){
	Noeud* nr = malloc(sizeof(Noeud));
	nr->value = v;
	nr->next = NULL;
	nr->prec = l->queue;

	if(est_vide(l) == 1){
		l->tete = nr;
	}else{
		l->queue->next = nr;
	}
	l->queue = nr;
	l->nbNoeud++;
	return nr;
}


void pop_back(Liste* l){
	if(est_vide(l) == 1){
		return;
	}
	Noeud* nr = l->queue;
	if(nr != NULL){
		l->queue = l->queue->prec;
		free(nr);
	}else if(nr == l->tete){
		pop_front(l);
	}
	l->nbNoeud--;
	return;
}

int back_val(Liste* l){
	return l->queue->value;
}

void print(Liste* l){
	if(est_vide(l) == 1){
		printf("\n%s\n","Liste Vide");
		return;
	}
	Noeud* na = l->tete;
	printf("%d",na->value);
	while(na->next != NULL){
		printf(", ");
		na = na->next;
		printf("%d",na->value);
	}
}

Noeud* trouve_premier(Liste* l, int v){
	if(est_vide(l)){
		return NULL;
	}
	Noeud* na = l->tete;
	while(na != NULL){
		if(na->value == v){
			return na;
		}
		na = na->next;
	}
	return NULL;
}

Noeud* trouve_dernier(Liste* l, int v){
	if(est_vide(l)){
		return NULL;
	}
	Noeud* na = l->queue;
	while(na != NULL){
		if(na->value == v){
			return na;
		}
		na = na->prec;
	}
	return NULL;
}

void retire(Liste* l, Noeud* n){
	if(est_vide(l) == 1){
		return;
	}
	Noeud* na = l->tete;
	//Si le noeud est la tête
	if(na == n){
		//Si le noeud est l'unique noeud
		if(l->nbNoeud == 1){
			l->tete = NULL;
			l->queue = NULL;
		}else{
			l->tete = na->next;
		}
		l->nbNoeud--;
		free(n);
		return;
	}
	while(na != NULL){
		//Si le noeud suivant est celui qu'on veut retirer
		if(na->next == n){
			na->next = n->next;
			na->prec = n->prec;
			l->nbNoeud--;
			free(n);
			return;
		}
		na = na->next;
	}
	return;
}

Noeud* insert_after(Liste* l,Noeud* c, int v){
	Noeud* n = malloc(sizeof(Noeud));
	n->value = v;
	if(c->next != NULL){
		n->next = c->next;
	}else{
		n->next = NULL;
	}
	if(c->prec != NULL){
		n->prec = c->prec;
	}else{
		n->prec = NULL;
	}
	c->next = n;
	l->nbNoeud++;
	return n;
}

bool equals(Liste* l1, Liste* l2) {
	Noeud* na = l1->tete;
	Noeud* nb = l2->tete;
	while(na != NULL){
		if(na->value != nb->value) {
			return false;
		}
		na = na->next;
		nb = nb->next;
	}
	return true;
}

void apply(Liste* l,void (*fonction)(int*)){
	Noeud* na = l->tete;
	while(na != NULL){
		fonction(&na->value);
		na = na->next;
	}
}

void applyCompteur(Liste* l,int* cpt,void (*fonction)(int*,int*)){
	Noeud* na = l->tete;
	while(na != NULL){
		fonction(&na->value,cpt);
		na = na->next;
	}
}

void foisdeux(int* v){
	*v*=2;
}
