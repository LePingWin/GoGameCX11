#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

char alphabetTable[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','o','p','q','r','s','t','u','v','w','x','y','z'};

//Récupère la coordonnée associée à la lettre
int getCoordsFromLetter(char letter){
	for (size_t i = 0; i < 26; ++i)
	{
		if(alphabetTable[i] == letter){
			return i;
		}
	}
	return -1;
}

//Récupère la lettre associée à la coordonnée
char* getLetterFromCoords(int c){
	if(c<26){
		return &alphabetTable[c];
	}
}

// Récupère les coordonnées des pierres du joueur
void loadStonesCoordinates(char* coords){
	
	if(coords[0] == 'A'){
		char* p = strtok(coords,"[");
		p = strtok(NULL,"[");
		 while (p != NULL)
			{
				int xp = getCoordsFromLetter(p[0])*getNbPierres();
				int yp = getCoordsFromLetter(p[1])*getNbPierres();
				//Ajoute les pierres aux joueurs
				if(coords[1] == 'W'){
					addPierreToPlayer(xp,yp,getPlayer(0));
				}else{
					addPierreToPlayer(xp,yp,getPlayer(1));
				}
				p = strtok (NULL, "[");

			}
	}
	return;
}

//Initialise la lecture des coordonnées
void loadSaveGame(const char* path){
   FILE *file = fopen ( path, "r" );
   if ( file != NULL )
   {
      char line [ 128 ]; /* or other suitable maximum line size */
 
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
         loadStonesCoordinates(line);
      }
      fclose ( file );
   }
   else
   {
      perror ( path ); 
   }

return;
}

//Récupère la chaîne des pions à écrire pour un joueur
char* getPlayerCoordinatesAsString(Player p){
	int* plateau = getPlateau();
	char* res = "A";
	if(p.type == 0){
		strcat(res,"W");
	}else{
		strcat(res,"B");
	}
	for(int i = 0; i < getNbPierres(); i++) {
			for(int j = 0; j < getNbPierres(); j++) {
				int tmp = plateau[i*getNbPierres() + j];
				if(tmp == p.type+1){
					char* tmpX = getLetterFromCoords(i);
					char* tmpY = getLetterFromCoords(j);
					strcat(res,"[");
					strcat(res,tmpX);
					strcat(res, tmpY);
					strcat(res,"]");
				}
		}
	}
	//strcat(res,"\n");
	return res;
}

//Ecris les lignes dans le fichier
void writeSaveGame(const char* path){
	FILE *file = fopen ( path, "w" );

	fprintf(file,"%s", getPlayerCoordinatesAsString(getPlayer(0)));
	fprintf(file,"%s", getPlayerCoordinatesAsString(getPlayer(1)));

	fclose(file);

}
