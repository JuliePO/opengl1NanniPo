#ifndef ITD_TOWER_H_
#define ITD_TOWER_H_

#include "element/Monster.h"

/************* STRUCTURE DU TOUR *************/
/* Liste doublement chainée pour pouvoir naviger dans la liste de tours	*
*  et récupérer facile n'importe quelle tour dans la liste 		*/
typedef struct struct_tower {

	//id (commence à 1)
	int id;

	//position de la tour
	int x;
	int y;

	//Type de la tour : R (rocket) L (laser), M (mitraillette) et H (hybride)
	char type_tower;

	//puissance de tir
	float power;

	//cadence 
	float rate;

	//porté de la tour
	float range;

	//cout de la tour
	int cost;

	//Pointer vers l'élément précédent
	struct struct_tower* p_prev;

	//Pointeur vers l'élément suivant
	struct struct_tower* p_next;

}Tower;

/************* STRUCTURE DE LA LISTE DE TOURS *************/
typedef struct struct_ltower {

	//Taille de la liste
	size_t length;

	//Pointeur
	Tower *p_head; //pointeur vers le premier element
	Tower *p_tail; //pointeur vers le dernier element
}LTower;

/************* Appel de fonction *************/
LTower* new_LTower(void);
int addTower(LTower*, float, float, char*, float, int);
LTower* removeTower(LTower*, Tower*);
int inSight (LMonster*, Tower*);

#endif
