#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getCoordsPlayerStones(char player, char* coords){

	if(coords[0] == 'A' && coords[1] == player){
		char* p = strtok(coords,"[");
		p = strtok(NULL,"[");
		 while (p != NULL)
			{
				printf("%c%c\n",p[0],p[1]);
				//Fonction qui lit les coordonnées et recrée une liste de liste
				p = strtok (NULL, "[");

			}
	}
	return;
}

FILE* readSGF(const char* path){
	FILE *fp;

	fp=fopen(path, "r");

	char c[1000];
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // reads text until newline
    fscanf(fp,"%[^\n]", c);
    //Récupère le tableau du joueur Blanc
	getCoordsPlayerStones('W',c);

	// reads text until newline
    fscanf(fp,"%[^\n]", c);
    //Récupère le tableau du joueur Noir
	getCoordsPlayerStones('B',c);

return fp;
}




int main(){
	//Lis le fichier
	readSGF("/home/user-cnam/Documents/Laurent/Prog/Go/GoGameCX11/test.sgf");
}
