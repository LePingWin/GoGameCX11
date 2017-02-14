#include "dessine.h"
#include "affichage.h"
#include "../Engine/engine.h"
#include "../Engine/rules.h"
#include "../Engine/sgf.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



bool finDuGame = false;

/**
 * Mettre ici son code pour dessiner dans la fenetre
 * 1er affichage + redessine si resize
 */
void draw_win()
{
	// vide la fenetre
	clear_win();

	int i,j;

	color(0.75,0.80,0.80);
	filled_rectangle(0,0,height_win(),width_win());

	color(1,0,0);
	int largeurBordure = getLargeurBordure();
	for(j=largeurBordure; j<=width_win()-largeurBordure; j+=getTaillePierre())
		line(j,largeurBordure, j, height_win()-largeurBordure);

	for(i=largeurBordure; i<=width_win()-largeurBordure; i+=getTaillePierre())
		line(largeurBordure,i, width_win()-largeurBordure, i);

	color(1,1,1);
	color(0.54,0.27,0.27);
	filled_rectangle(10 + (getNbPierres()-1)/2*getTaillePierre()-20, getLargeurBordure()/2-10, 40, 20);
	color( 0.0,0.0,0.0);
	string(14 + (getNbPierres()-1)/2*getTaillePierre()-20, getLargeurBordure()/2+5,"Passer");

	color(0.54,0.27,0.27);
	filled_rectangle(70 + (getNbPierres()-1)/2*getTaillePierre()-20, getLargeurBordure()/2-10, 70, 20);
	color( 0.0,0.0,0.0);
	string(74 + (getNbPierres()-1)/2*getTaillePierre()-20, getLargeurBordure()/2+5,"Sauvegarder");
}

void add_dessin_pierre(int* c) {
	filled_circle(getX(*c),getY(*c),10);
}

void refreshTable() {
	draw_win();
	Player p;
	for(int i = 0; i < 2; i++) {
		p = getPlayer(i);
		if(i == 0) {
			color( 1.0,1.0,1.0);
		} else {
			color( 0.0,0.0,0.0);
		}
		for (int j = 0; j < p.nbListe; j++) {
				apply(p.pierres[j],add_dessin_pierre);
		}
	}
}



void dessin_pierre(int c) {
	Player p = getCurrentPlayer();
	if(p.type == Blanc) {
		color( 1.0,1.0,1.0);
	} else {
		color( 0.0,0.0,0.0);
	}

	filled_circle(getX(c),getY(c),10);
	printf("Nouvelle Pierre posé en : %d,%d \n", getX(c), getY(c));
}

void sauvegardePartie() {
	time_t t = time(NULL); /* t contient maintenant la date et l'heure courante */
	struct tm *info;
	info = localtime(&t);
	//char* str = ctime(&t);
	char buffer[256];
	strftime(buffer,256,"%Y%m%d_%Hh%M", info);
	char tour[5];
	sprintf(tour, "%d",getCptTours()-1);
	char* message = "_JeuGo_Tour_";
	strcat(buffer,message);
	strcat(buffer,tour);
	strcat(buffer, ".sgf");
	writeSaveGame(buffer);
}




/**
 * on a cliqué a la souris:
 * bouton: 1,2,3,4,5,... : gauche, milieu, droit, molette, ...
 * x,y position
 */
void mouse_clicked(int bouton, int x, int y)
{
	if(x >= 10 + (getNbPierres()-1)/2*getTaillePierre()-20 && x <= 10 + (getNbPierres()-1)/2*getTaillePierre()-20+40) {
		if(y >= getLargeurBordure()/2-10 && y <= getLargeurBordure()/2-10+20) {
			Player p = getOppositePlayer();
			setAPasser(p,true);
			if(checkFinDuJeu() == true) {
				finDuGame = true;
				color(0,0,0);
				string(50,50+(getNbPierres()-1)*getTaillePierre()+30,"Fin du game !!");
			}
		}
	}

	if(x >= 70 + (getNbPierres()-1)/2*getTaillePierre()-20 && x <= 70 + (getNbPierres()-1)/2*getTaillePierre()-20 + 70) {
		if(y >= getLargeurBordure()/2-10 && y <= getLargeurBordure()/2-10+20) {
			sauvegardePartie();
			color(0,0,0);
			string(50,50+(getNbPierres()-1)*getTaillePierre()+30,"Sauvegarde du game !!");
		}
	}
	if(finDuGame == false) {
		refreshTable();
		int i,j;
		int largeurBordure = getLargeurBordure();
		int taillePierre = getTaillePierre();
		for(i = -1; i<getNbPierres()-1; i++) {
			if((x >= largeurBordure + i*taillePierre + taillePierre/2) && (x < largeurBordure + (i+1)*taillePierre + taillePierre/2)) {
				for(j = -1; j<getNbPierres()-1; j++) {
					if((y >= largeurBordure + j*taillePierre + taillePierre/2) &&  (y < largeurBordure + (j+1)*taillePierre + taillePierre/2)) {
						int xp = largeurBordure + (i+1)*taillePierre;
						int yp = largeurBordure + (j+1)*taillePierre;
						Player p = getCurrentPlayer();
						int playerValue =0;
						if(p.type == Blanc) {
							playerValue = 1;
						} else {
							playerValue = 2;
						}
						if(repetition(i+1,j+1,playerValue) == 0) {
							if( intersection_est_vide(getCoord(xp,yp)) == true) {
								fill_plateau(i+1,j+1,playerValue);
								//printPlateau();
								dessin_pierre(addPierre(xp,yp));
								if(capturePion() == 1) {
									refreshTable();
								}
								incrementeCptTours();
							}
							else {
								string(50,50+(getNbPierres()-1)*getTaillePierre()+30,"La case est deja utilise!");
							}

						}
						else {
							printf("\nRepetition, be careful !!");
							string(50,50+(getNbPierres()-1)*getTaillePierre()+30,"Repetition !");
						}

					}
				}
			}
		}
		Player p = getOppositePlayer();
		setAPasser(p,false);
	}
}






/**
 * on a appuyé sur une touche
 * code: code touche x11 (XK_...)
 * c caractère correspondant si caractere
 * x_souris,y_souris position de la souris
 */
void key_pressed(KeySym code, char c, int x_souris, int y_souris)
{
	switch(code)
	{
		case XK_Down:
			printf("bas\n");
			break;
		case XK_Up:
			printf("haut\n");
			break;
		case XK_Left:
			printf("gauche\n");
			break;
		case XK_Right:
			printf("droite\n");
			break;
	//~ case XK_Return:
	//~ case XK_Shift_L:
	//~ case XK_Control_R:
	//~ ....
		default:
			break;
	}

	if (c>' ' && c<'z')
		printf("char: %c \n",c);

	printf(" avec pos souris: %d,%d \n",x_souris,y_souris);

}


int main(int argc,char* argv[])
{
	int taillePierre = 24;
	int nbPierres = 6;
	int largeurBordure = 50;


	if(argc == 3){
		if(strcmp(argv[1],"-p") ==0)
			nbPierres = atoi(argv[2]);
		if(strcmp(argv[1],"-l") ==0) {
			//loadSaveGame(argv[2]);
			nbPierres = loadNumberPierre(argv[2]);
			printf("%d\n",nbPierres );
		}

		init_go(nbPierres, taillePierre);
		init_win(taillePierre*nbPierres+largeurBordure*2,taillePierre*nbPierres+largeurBordure*2, "Jeu de Go v0.4",0.2,0.2,0.6,largeurBordure);
		refreshTable();
		if(strcmp(argv[1],"-l") ==0) {
			loadSaveGame(argv[2]);
		}

		//sendClick(1,true);
	}
	event_loop();
	return EXIT_SUCCESS;
}
