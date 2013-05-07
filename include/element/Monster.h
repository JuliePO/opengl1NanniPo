#ifndef LDR_MONSTER_H_
#define LDR_MONSTER_H_

/************* STRUCTURE DU MONSTRE *************/
/* Liste doublement chainée pour pouvoir naviger dans la liste de monstres	*
*  et récupérer facile n'importe quel monstre dans la liste 			*/

typedef struct struct_monster {

	//id (commence à 1)
	int id;

	//type de monstre
	char* type;

	//point de vie
	float pv;

	//résistance
	float resistance;

	//résistance plus élevé pour un type de tour
	char type_tower;

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
int addMonster(LMonster*, char*, float, float, char, float);
LMonster* removeMonster(LMonster*, Monster*);

#endif
