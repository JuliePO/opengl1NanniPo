#ifndef ITD_SHOT_H_
#define ITD_SHOT_H_

#include "element/Monster.h"
#include "element/Tower.h"

/************* STRUCTURE DU SHOT *************/
/* Liste doublement chainée pour pouvoir naviger dans la liste de tours	*
*  et récupérer facile n'importe quelle tour dans la liste 		*/
typedef struct struct_shot {

	//id (commence à 1)
	int id;

	//position du missile
	int x;
	int y;

	//Ennemie visé
	Monster* target;

	//Tour qui a envoyé le missile
	Tower* tower;

	//Pointer vers l'élément précédent
	struct struct_shot* p_prev;

	//Pointeur vers l'élément suivant
	struct struct_shot* p_next;

}Shot;

/************* STRUCTURE DE LA LISTE DE TOURS *************/
typedef struct struct_lshot {

	//Taille de la liste
	size_t length;

	//Pointeur
	Shot *p_head; //pointeur vers le premier element
	Shot *p_tail; //pointeur vers le dernier element
}LShot;

/************* Appel de fonction *************/
LShot* new_LShot(void);
int addShot(LShot*, Monster*, Tower*);
LShot* removeShot(LShot*, Shot*);

#endif
