#ifndef ITD_MONSTER_H_
#define ITD_MONSTER_H_

#include "ihm/Node.h"

/************* STRUCTURE DU MONSTRE *************/
/* Liste doublement chainée pour pouvoir naviger dans la liste de monstres	*
*  et récupérer facile n'importe quel monstre dans la liste 			*/

typedef struct struct_monster {

	//id (commence à 1)
	int id;

	//position du monstre
	int x;
	int y;
	int e; //erreur : calcul dans le cas où il n'avance pas tout droit

	//Noeud précédent
	Node* node_prev;

	//Noeud suivant
	Node* node_next;

	//type de monstre
	char* type;

	//point de vie
	float pv;
	float pvMax;

	//résistance
	float resistance;

	//résistance plus élevé pour un type de tour
	char* type_tower;

	//vitesse de déplacement
	float pace;

	//Pointer vers l'élément précédent
	struct struct_monster* p_prev;

	//Pointeur vers l'élément suivant
	struct struct_monster* p_next;

}Monster;

/************* STRUCTURE DE LA LISTE DE MONSTRES *************/
typedef struct struct_lmonster {

	//Taille de la liste
	size_t length;

	//Pointeur
	Monster *p_head; //pointeur vers le premier element
	Monster *p_tail; //pointeur vers le dernier element
}LMonster;

/************* Appel de fonction *************/
LMonster* new_LMonster(void);
Monster* new_Monster(int, int);
int addMonster(LMonster*, char*, float, float, char*, float, LNode*);
int moveMonster(LMonster*, Node*);
int verificationEnd(Monster*, Node*);
LMonster* removeMonster(LMonster*, Monster*);

#endif
