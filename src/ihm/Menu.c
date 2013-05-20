#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include "element/Monster.h"
#include "element/Tower.h"
//#include "element/Shot.h"
#include "ihm/Menu.h"
#include "ihm/Interface.h"

/*********************** Clique sur le menu : achat de tour ***********************/
/* Achat d'une tour losqu'on clique sur le menu puis affiche la tour. 	*/

int clickMenuTour(LTower* p_ltower, Interface* interface, float x, float y) {

	if(x <= 180 && x >= 20 && y <= 130 && y >= 80) {

		if((interface->money) >= 50) {
			addTower(p_ltower, 2.0, 10.0, "c", 50., 10.0, x, y);
			updateMoney(interface, 50.);
			return 1;
		}
	}

	return 0;

}


/*********************** Clique sur le menu : avance rapide ***********************/
/* Avance rapide : retourne 2 si on a cliqué sur le bouton avance rapide sinon retourne 0 	*/
int clickAvanceRapide(float x, float y, int play) {
	
	//Si clique sur avance rapide	
	if(x <= 720 && x >= 690 && y <= 45 && y >= 15)
		return 2;
	//sinon
	else {
		//Si c'est en avance rapide
		if(play == 2) {
			//Si clique sur play
			if(x <= 755 && x >= 725 && y <= 45 && y >= 15) 
				return 0;
			else
				return 2;
		}
	}

	return 0;
}

/*********************** Clique sur le menu : fermer ***********************/
/* fermer : retourne 0 si on a cliqué sur le bouton avance rapide sinon retourne 1 	*/
int clickExit(float x, float y) {
	
	if(x <= 790 && x >= 760 && y <= 45 && y >= 15)
		return 0;

	return 1;

}
