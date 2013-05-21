#ifndef ITD_INTERFACE_H_
#define ITD_INTERFACE_H_

#include "element/Monster.h"

/************* STRUCTURE DE L'INTERFACE *************/
typedef struct struct_interface {
	
	//argent
	int money;

	//score
	int score;

	//niveau
	int lvl;

	//nb de monstre
	int nbMonster;

	//points de vie
	int life;

}Interface;

/************* Prtotypes des fonctions *************/
//Initialisation de l'interface
Interface* newInterface (void);
//Mise à jour de l'agent, score et nb de monstre
int updateInterface(Interface*, Monster*);
//Mise à jour lors d'un changement de niveau
int updateLvl(Interface*);
//Mise à jour de l'argent
int updateMoney(Interface*, int);
//Mise à jour du nombre de vie
int udapteLife(Interface*);
//Supprime l'interface
void freeInterface (Interface*);

#endif
