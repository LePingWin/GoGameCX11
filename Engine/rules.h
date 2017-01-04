#ifndef rules
#define rules

#include "./ListLib/lst_double.h"

typedef struct Coord{
	int x;
	int y;
} Coord;

typedef enum boolean{
True,False
} boolean;

typedef enum PlayerType{
Blanc,Noir
} PlayerType;

typedef struct Player{
	char* nom;
	PlayerType typeJoueur;
}Player;

#endif
