#ifndef rules
#define rules

#include "./ListLib/lst_double.h"

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

typedef struct Pierre{
	int x;
	int y;
} Pierre;

typedef struct Player{
	char* nom;
	PlayerType type;
	Pierre* pierres
}Player;



#endif
