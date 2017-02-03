#include "dessine.h"
#include "../Engine/engine.h"
#include "../Engine/rules.h"


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
	string(5,5,"Test Affichage chaine");
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






/**
 * on a cliqué a la souris:
 * bouton: 1,2,3,4,5,... : gauche, milieu, droit, molette, ...
 * x,y position
 */
void mouse_clicked(int bouton, int x, int y)
{
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


int main()
{
	int taillePierre = 24;
	int nbPierres = 6;
	int largeurBordure = 50;
	init_go(nbPierres, taillePierre);
	init_win(taillePierre*nbPierres+largeurBordure*2,taillePierre*nbPierres+largeurBordure*2, "v0.1",0.2,0.2,0.6,largeurBordure);
	event_loop();
	return EXIT_SUCCESS;
}
