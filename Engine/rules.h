#ifndef rules
#define rules

#include "../ListLib/lst_double.h"
#include "../Tab1DLib/tab1.h"

typedef enum PlayerType{
Blanc,Noir
} PlayerType;

typedef struct Player{
	char* nom;
	PlayerType type;
	//Tableaux de listes
	Liste** pierres;
	int nbListe;
	bool aPasser;
}Player;

typedef struct Adjacent{
	int* adjs;
	int nbAdj;
}Adjacent;

//Int sur 32bits donc x prend 16 bits et y 16 bits
int getX(int c);

int getY(int c);

int getCoord(int x,int y);


#endif
