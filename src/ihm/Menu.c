#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "element/Monster.h"
#include "element/Tower.h"
#include "element/Shot.h"
#include "ihm/Interface.h"
#include "file/FileTower.h"
#include "ihm/Menu.h"

/*********************** Clique sur le menuPrincipale  ***********************/
/* action clique menu Principale. Prend en paramètre la position et un pointeur vers nbMenu. Retourne 0 en cas d'erreur et 1 sinon	*/

void clickMenuPrincipale(float x, float y, int* nbMenu, int* nbMap) {

	if(*nbMenu == 0) {
		//map 1
		if(x <= 514 && x >= 365 && y <= 483 && y >= 162) {
			*nbMap = 1;
			*nbMenu = 1;
		}
		//map 2
		else if(x <= 756 && x >= 434 && y <= 483 && y >= 162) {
			*nbMap = 2;
			*nbMenu = 1;
		}
	}
	else if(*nbMenu == 1) {

		//bouton play
		if(x <= 514 && x >= 272 && y <= 352 && y >= 296)
			*nbMenu = 3;
		//bouton aide
		else if(x <= 514 && x >= 272 && y <= 421 && y >= 364)
			*nbMenu = 2;
		//bouton changer de menu
		else if(x <= 514 && x >= 272 && y <= 490 && y >= 432)
			*nbMenu = 2;
	}
	else if(*nbMenu == 2) {
	
		//bouton menu
		if(x <= 310 && x >= 68 && y <= 627 && y >= 570)
			*nbMenu = 1;
		//bouton play
		else if(x <= 732 && x >= 490 && y <= 627 && y >= 570)
			*nbMenu = 3;		
		
	}

}

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
			type = "M";

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

/*********************** Clique sur le menu : supprimer tour ***********************/
/* supprimer tour lorsqu'on clique sur le bouton supprimer. Prend en paramètre un pointeur vers la liste de tour, un pointeur	*
*  vers la liste de shot, la tour courant, la position et un pointeur vers propriete. Retourne 0 en cas d'erreur sinon 1. 	*/

int clickTourDelete(LTower* p_ltower, LShot* p_lshot, Tower* p_courant, Interface* interface, float x, float y, int* propriete) {

	if(p_ltower != NULL) {

		if(p_courant != NULL) {

			if(*propriete == 1) {

				if(x <= 190 && x >= 10 && y <= 540 && y >= 490) {

					Shot* p_tmp = p_lshot->p_head;
					while(p_tmp != NULL) {

						if(p_tmp->tower == p_courant)
							p_tmp->tower = NULL;

						p_tmp = p_tmp->p_next;

					}
					interface->money += p_courant->cost;
					p_ltower = removeTower(p_ltower, p_courant);
					*propriete = 0;
				}
			}

		}
		else {
			fprintf(stderr, "Erreur la tour courante\n");
			return 0;
		}

	}
	else {
		fprintf(stderr, "Erreur avec la liste de tours\n");
		return 0;
	}

	return 1;

}

/*********************** Clique sur le menu : monter de lvl une tour ***********************/
/* monter de lvl une tour lorsqu'on clique sur le bouton upgrate. Prend en paramètre 			*
*  la tour courant, la position et un pointeur vers propriete. Retourne 0 en cas d'erreur sinon 1. 	*/

int clickTourUpgrate(Tower* p_courant, Interface* interface, float x, float y, int* propriete) {

	if(interface != NULL) {

		if(p_courant != NULL) {

			if(*propriete == 1) {

				if(x <= 190 && x >= 10 && y <= 595 && y >= 545) {
					upgrateTower(p_courant, interface);
					*propriete = 1;
				}
			}

		}
		else {
			fprintf(stderr, "Erreur la tour courante\n");
			return 0;
		}

	}
	else {
		fprintf(stderr, "Erreur avec l'interface\n");
		return 0;
	}

	return 1;

}

/*********************** Clique sur le menu : pause/play/avanceRapide ***********************/
/* Pause : retourne 2 si on a cliqué sur le bouton avance rapide, 0 sur play ou 1 sur pause sinon retourne 0 	*/
int clickTime(float x, float y, int play) {
	
	//si c'est play
	if(play == 0) {
		//Si clique sur pause	
		if(x <= 720 && x >= 690 && y <= 45 && y >= 15)
			return 1;
		//Si clique sur avance rapide
		else if(x <= 685 && x >= 655 && y <= 45 && y >= 15)
			return 2;

	}
	//si c'est en pause
	else if(play == 1) {

		//Si clique sur play
		if(x <= 720 && x >= 690 && y <= 45 && y >= 15) 
			return 0;
		//Si clique sur avance rapide
		else if(x <= 685 && x >= 655 && y <= 45 && y >= 15)
			return 2;
		else
			return 1;
	}
	//sinon avance rapide
	else {
		//Si clique sur play
		if(x <= 720 && x >= 690 && y <= 45 && y >= 15) 
			return 0;
		else
			return 2;
	}

	return 0;
}

/*********************** Clique sur le menu : fermer ***********************/
/* fermer : retourne 0 si on a cliqué sur le bouton avance rapide sinon retourne 1 	*/
int clickExit(float x, float y, int aide) {
	
	if(aide == 0) {
		if(x <= 790 && x >= 760 && y <= 45 && y >= 15)
			return 0;
	}

	return 1;

}

/*********************** Clique sur le menu : aide ***********************/
/* aide : retourne 1 si on a cliqué sur le bouton avance rapide sinon retourne 0 	*/
int clickAide(float x, float y, int aide) {
	
	if(aide == 0) {
		if(x <= 755 && x >= 725 && y <= 45 && y >= 15)
			return 1;
	}
	else {
		if(x <= 790 && x >= 760 && y <= 45 && y >= 15)
			return 0;
	}

	return 0;

}

/*********************** Clique : pour afficher les propriétés d'une tour ***********************/
/* click retour une tour pour afficher ces propriétés. Prend en paramètre la liste de tours,  la 	*
*  position du clique et un pointeur int qui permet de savoir si on affiche ou non des propriétés.	*
*  Retourne NULL s'il y a une erreur, ou si on n'a pas cliquer sur une tour. Sinon retourne la tour.	*/

Tower* clickTower(LTower* p_ltower, float x, float y, int* propriete) {
	
	//Vérifie que la liste de tours existe
	if(p_ltower != NULL) {

		//Tour temporaire pour parcourir la liste de tour
		Tower* p_tmp = p_ltower->p_head;
		
		while(p_tmp != NULL) {

			//Si on a cliqué sur une tour
			if(x <= (p_tmp->x + 20) && x >= (p_tmp->x - 20) && y <= (p_tmp->y + 20) && y >= (p_tmp->y - 20)) {
				*propriete = 1;
				return p_tmp;	
			}

			p_tmp = p_tmp->p_next;

		}
	}
	else {
		fprintf(stderr, "Erreur : cette liste de tour n'existe pas\n");
		return NULL;
	}

	return NULL;

}

/*********************** Clique : pour afficher les propriétés d'un monstre ***********************/
/* click retour un monstre pour afficher ces propriétés. Prend en paramètre la liste de monstres,  la 	*
*  position du clique et un pointeur int qui permet de savoir si on affiche ou non des propriétés.	*
*  Retourne NULL s'il y a une erreur, ou si on n'a pas cliquer sur une tour. Sinon retourne la tour.	*/

Monster* clickMonster(LMonster* p_lmonster, float x, float y, int* propriete) {
	
	//Vérifie que la liste de monstres existe
	if(p_lmonster != NULL) {

		//Tour temporaire pour parcourir la liste de tour
		Monster* p_tmp = p_lmonster->p_head;
		
		while(p_tmp != NULL) {

			//Si on a cliqué sur une tour
			if(x <= (p_tmp->x + 20) && x >= (p_tmp->x - 20) && y <= (p_tmp->y + 20) && y >= (p_tmp->y - 20)) {
				*propriete = 2;
				return p_tmp;	
			}

			p_tmp = p_tmp->p_next;

		}
	}
	else {
		fprintf(stderr, "Erreur : cette liste de monstre n'existe pas\n");
		return NULL;
	}

	return NULL;

}

/*********************** Supprime tous ***********************/
/* Supprime tous. Prend en paramètre 	*/

void freeAll () {
	
}
