#ifndef LDR_TOWER_H_
#define LDR_TOWER_H_

typedef struct struct_tower {

	//id
	int id;

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

//liste de tour
typedef struct struct_ltower {

	//Taille de la liste
	size_t length;

	//Pointeur
	Tower *p_head; //pointeur vers le premier element
	Tower *p_tail; //pointeur vers le dernier element
}LTower;

#endif
