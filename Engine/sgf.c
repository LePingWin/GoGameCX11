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
char getLetterFromCoords(int c){
	if(c<26){
		return alphabetTable[c];
	}
}
// Récupère le nombre de pierre de la partie
int loadSize(char* coords){
	int sz = 6;
	if(coords[0] == 'S' && coords[1] == 'Z'){
		char* p = strtok(coords,"[");
		p = strtok(NULL,"[");
		char str[10];
		str[0]= p[0];
		str[1]=p[1];
		sz = atoi(str);
	}
	return sz;
}

// Récupère les coordonnées des pierres du joueur
void loadStonesCoordinates(char* coords){

	if(coords[0] == 'A'){
		char* p = strtok(coords,"[");
		p = strtok(NULL,"[");
		 while (p != NULL)
			{
				int xp = getLargeurBordure() + getCoordsFromLetter(p[0])*getTaillePierre();
				int yp = getLargeurBordure() + getCoordsFromLetter(p[1])*getTaillePierre();
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

int loadNumberPierre(const char* path) {
	FILE *file = fopen ( path, "r" );
	int number = 6;
	if ( file != NULL )
	{
		 char line [ 128 ]; /* or other suitable maximum line size */

		 while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
		 {
				number = loadSize(line);
				if(number != 6){
					fclose ( file );
					return number;
				}
				printf("NB PEIRRE %d\n",number );
		 }
		 fclose ( file );
	}
	else
	{
		 perror ( path );
	}

return number;
}

//permet d'ajouter un char à un char*
char* ajout_char(char *chaine, size_t n, char c)
{
	size_t len = strlen(chaine);
	/* vérifie qu'il y a assez de place */
	if (len + 1 >= n) return NULL;
	chaine[len] = c;
	chaine[len + 1] = '\0';
	return chaine;
}

//Récupère la chaîne des pions à écrire pour un joueur
char* getPlayerCoordinatesAsString(Player p, char* str){
	int* plateau = getPlateau();
	strcpy(str,"A");
	if(p.type == 0){
		strcat(str,"W");
	}else{
		strcat(str,"B");
	}
	for(int i = 0; i < getNbPierres(); i++) {
			for(int j = 0; j < getNbPierres(); j++) {
				int tmp = plateau[i*getNbPierres() + j];
				if(tmp == p.type+1){
					char tmpX = getLetterFromCoords(j);
					char tmpY = getLetterFromCoords(i);
					strcat(str,"[");
					ajout_char(str, 50, tmpX);
					ajout_char(str, 50, tmpY);

					printf("tmpX %c, tmpY %c",tmpX,tmpY);
					strcat(str,"]");
				}
		}
	}
	strcat(str,"\n");
	return str;
}

//Ecris les lignes dans le fichierfclose ( file );
void writeSaveGame(const char* path){
	FILE *file = fopen ( path, "w" );
	char str[50];
	char res[50];
	char num[50] = "SZ[";
	char size[50];
	//strcat(num,"SZ[");
	sprintf(size, "%d",getNbPierres());
	strcat(num,size);
	strcat(num,"]\n");
	fprintf(file,"%s",num);
	fprintf(file,"%s", getPlayerCoordinatesAsString(getPlayer(0),str));
	fprintf(file,"%s", getPlayerCoordinatesAsString(getPlayer(1),res));

	fclose(file);

}
