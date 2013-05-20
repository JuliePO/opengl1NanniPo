#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ihm/Interface.h"
#include "element/Monster.h"

/************* Initialisation de l'interface *************/
/* Alloue de la mémoire pour l'interface et initialise les valeurs.	*
*  Retourne le pointeur vers l'interface.				*/
Interface* newInterface (void) {

	//Alloue la memoire
	Interface* interface = malloc(sizeof(Interface));

	//Vérifie que l'interface a été alloué
	if(interface != NULL) {
		interface->money = 200;
		interface->score = 0;
		interface->lvl = 0;
		interface->nbMonster = 0;
		interface->life = 3;
	}
	else {
		fprintf(stderr, "Erreur lors de l'allocation mémoire de l'interface\n");
		return NULL;
	}
	
	return interface;
}

/************* Mise à jour de l'argent, du score et du nombre de monstres *************/
/* Met à jours les valeurs de money, score et nbMonster. Prend en paramètre un pointeur		*
*  vers l'interface et un pointeur vers le monstre tué.Retourne le pointeur vers l'interface.	*	
*  Retourne 0 en cas d'erreur et 1 sinon. 							*/

int updateInterface(Interface* interface, Monster* monster) {

	//Si l'interface a été alloué
	if(interface != NULL) {

		//Si le monstre a été alloué
		if(monster != NULL) {
		
			interface->money += monster->gain;
			interface->score += monster->points;
			interface->nbMonster ++;

		}
		else {
			fprintf(stderr, "Erreur avec le monstre\n");
			return 0;
		}

	}
	else {
		fprintf(stderr, "Erreur avec l'interface\n");
		return 0;
	}	

	return 1;

}

/************* Mise à jour lors d'un changement de niveau  *************/
/* Met à jour le niveau, le score, l'argents. Prend en paramètre un pointeur 	*
*  vers l'interface. Retourne 0 en cas d'erreur et 1 sinon.			*/

int updateLvl(Interface* interface) {
	
	//Si l'interface a été alloué
	if(interface != NULL) {
	
		interface->lvl ++;
		interface->money += (interface->lvl) * 20;
		interface->score += (interface->lvl) * 20;

		//Augmente la vie tous les 5 niveaux
		if((interface->lvl) % 5 == 0)
			interface->life ++;
		
	}
	else {
		fprintf(stderr, "Erreur avec l'interface\n");
		return 0;
	}
	
	return 1;
}

/************* Mise à jour de l'argent  ***********/
/* Met à jour de l'argent. Prend en paramètre un pointeur vers l'interface	*
*  et le prix d'une tour. Retourne 0 en cas d'erreur et 1 sinon.		*/

int updateMoney(Interface* interface, int price) {

	//Si l'interface a été alloué
	if(interface != NULL) {
	
		interface->money -= price;
		
	}
	else {
		fprintf(stderr, "Erreur avec l'interface\n");
		return 0;
	}
	
	return 1;
}

/************* Mise à jour du nombre de vie  ***********/
/* Met à jour du nombre de vie. Prend en paramètre un pointeur 	*
*  vers l'interface. Retourne 0 en cas d'erreur et 1 sinon.	*/

int udapteLife(Interface* interface) {

	//Si l'interface a été alloué
	if(interface != NULL) {
	
		interface->life --;
		
	}
	else {
		fprintf(stderr, "Erreur avec l'interface\n");
		return 0;
	}
	
	return 1;
}
