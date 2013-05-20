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
#include "file/FileTower.h"

/*********************** Clique sur le menu : achat de tour ***********************/
/* Achat d'une tour losqu'on clique sur le menu puis affiche la tour. 	*/

int clickMenuTour(LTower* p_ltower, LFileTower* p_lfileTower, Interface* interface, float x, float y) {

	//Vérifie si les elements ont été alloué
	if(p_ltower != NULL && p_lfileTower != NULL && interface != NULL) {

		char* type = "None";

		//Vérifie qu'on clique sur le bon bouton : tour hybride
		if(x <= 190 && x >= 10 && y <= 120 && y >= 70)
			type = "H";

		// Tour rocket
		else if(x <= 190 && x >= 10 && y <= 175 && y >= 125)
			type = "L";

		//Si le niveau est suppérieur à 3
		if(interface->lvl >= 3) {
			if(x <= 190 && x >= 10 && y <= 230 && y >= 180)
				type = "L";
		}

		//Si le niveau est suppérieur à 5
		if(interface->lvl >= 5) {
			if(x <= 190 && x >= 10 && y <= 285 && y >= 235)
				type = "R";
		}


		//Vérifie qu'il y a un type, sinon pas de clique sur l'un des boutons
		if(strcmp("None", type) != 0) {

			//Pointeur temporaire pour parcourir la liste
			FileTower* tmp = p_lfileTower->p_head;
	
			//Parcours la liste
			while(tmp != NULL) {
				//Si c'est l'hybride 
				if(strcmp(type, tmp->type_tower) == 0)
					break;

				tmp = tmp->p_next;
			}

			//S'il le joueur a assez d'argent
			if((interface->money) >= tmp->cost) {
				//Ajoute une tour
				addTower(p_ltower, tmp->power, tmp->rate, tmp->type_tower, tmp->range, tmp->cost, x, y);
				//Met a jour l'agent
				updateMoney(interface, tmp->cost);
				return 1;
			}
		}
		
	}
	else {
		fprintf(stderr, "Erreur : liste de tour, liste de fileTour ou interface non alloué\n");
		return 0;
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
