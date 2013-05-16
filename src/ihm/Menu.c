#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Appel de la structures
#include "element/Monster.h"
#include "element/Tower.h"
#include "element/Shot.h"
#include "ihm/Menu.h"

/*********************** Clique sur le menu : achat de tour ***********************/
/* Achat d'une tour losqu'on clique sur le menu puis affiche la tour. 	*/

int clickMenuTour(LTower* p_ltower, int x, int y) {

	if(x <= 180 && x >= 20 && y <= 130 && y >= 80) {

		addTower(p_ltower, 3.0, 10.0, "c", 50., 10.0, x, y);
		return 1;
	}

	return 0;

}
