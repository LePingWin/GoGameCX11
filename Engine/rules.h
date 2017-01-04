#ifndef rules
#define rules

#include "../ListLib/lst_double.h"

typedef struct Pierre{
	int x;
	int y;
} Pierre;

typedef enum boolean{
True,False
} boolean;

typedef enum PlayerType{
Blanc,Noir
} PlayerType;

typedef struct Player{
	char* nom;
	PlayerType type;
	//Tableaux de listes
	Liste* pierres;
}Player;

//Int sur 32bits donc x prend 16 bits et y 16 bits
int getX(int c);

int getY(int c);

int getCoord(int x,int y);


#endif
