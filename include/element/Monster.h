#ifndef ITD_MONSTER_H_
#define ITD_MONSTER_H_

#include "ihm/Node.h"

/************* STRUCTURE DU MONSTRE *************/
/* Liste doublement chainée pour pouvoir naviger dans la liste de monstres	*
*  et récupérer facile n'importe quel monstre dans la liste 			*/

typedef struct struct_monster {

	//position du monstre
	float x;
	float y;
	float e; //erreur : calcul dans le cas où il n'avance pas tout droit

	//nombre pour savoir dans quelle sens il avance pour les sprites
	/* 1 = haut 	*
	*  2 = droite 	*
	*  3 = bas	*
	*  4 = gauche	*/
	int sens;
	//un chiffre pour l'animation du monstre
	int animation;

	//Noeud précédent (carte)
	Node* node_prev;

	//Noeud suivant (carte)
	Node* node_next;

	//type de monstre
	char* type;

	//point de vie
	float pv;
	float pvMax;

	//résistance
	float resistance;

	//Nombre de point gagner à chaque fois q'un monstre meurt
	int points;

	//Le gain (monnaie)
	int gain;

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

/************* Prototypes des fonctions *************/
//Initialisation de la liste de monstre
LMonster* new_LMonster(void);
//Ajouter un monstre en fin de liste
int addMonster(LMonster* , char* , float , float , char* , float , int, int, Node*);
//Fait bouger le monstre
int moveMonster(LMonster* , Node*);
//Calcule l'erreur de déplacement
void calculErreur(Monster*);
//Supprime le monstre
LMonster* removeMonster(LMonster*, Monster*);

#endif
