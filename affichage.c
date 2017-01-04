#include "dessine.h"
#include "engine.h"

/**
 * Mettre ici son code pour dessiner dans la fenetre
 * 1er affichage + redessine si resize
 */
void draw_win()
{
	// vide la fenetre
	clear_win();

	int i,j;

	float g = (float)rand()/RAND_MAX;
	color(g,g,g);
	filled_rectangle(0,0,height_win(),width_win());

	color(1,0,0);
	int largeurBordure = getLargeurBordure();
	for(j=largeurBordure; j<=width_win()-largeurBordure; j+=getTaillePierre())
		line(j,largeurBordure, j, height_win()-largeurBordure);

	for(i=largeurBordure; i<=width_win()-largeurBordure; i+=getTaillePierre())
		line(largeurBordure,i, width_win()-largeurBordure, i);

	color(11,1,1);
	string(5,5,"Test Affichage chaine");

}


/**
 * on a cliqué a la souris:
 * bouton: 1,2,3,4,5,... : gauche, milieu, droit, molette, ...
 * x,y position
 */
void mouse_clicked(int bouton, int x, int y)
{

	int i,j;
	int largeurBordure = getLargeurBordure();
	int taillePierre = getTaillePierre();
	for(i = 0; i<getNbPierres(); i++) {
		if((x >= largeurBordure + i*taillePierre + taillePierre/2) && (x < largeurBordure + (i+1)*taillePierre + taillePierre/2)) {
			for(j = 0; j<getNbPierres(); j++) {
				if((y >= largeurBordure + j*taillePierre + taillePierre/2) &&  (y < largeurBordure + (j+1)*taillePierre + taillePierre/2)) {
					color( 1.0,0.0,1.0);
					filled_circle(largeurBordure + (i+1)*taillePierre,largeurBordure + (j+1)*taillePierre,10);
					printf("Bouton %d presse au coord. %d,%d \n",bouton,x,y);
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
	int nbPierres = 19;
	int largeurBordure = 50;
	init_go(nbPierres, taillePierre);
	init_win(taillePierre*getNbPierres()+largeurBordure*2,taillePierre*getNbPierres()+largeurBordure*2, "v0.1",0.2,0.2,0.6,largeurBordure);
	event_loop();
	return EXIT_SUCCESS;
}
