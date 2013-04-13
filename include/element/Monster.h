#ifndef LDR_MONSTER___
#define LDR_MONSTER___

typedef struct struct_monster {

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

}Monster;

//liste de monstre
typedef struct struct_lmonster {

	//Taille de la liste
	size_t length;

	//Pointeur
	Monster *p_head; //pointeur vers le premier element
	Monster *p_tail; //pointeur vers le dernier element
}LMonster;

#endif
