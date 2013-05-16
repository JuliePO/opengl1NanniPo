#ifndef ITD_MENU_H_
#define ITD_MENU_H_

/************ Structure du menu **************/
/* Liste chainée pour pouvoir naviger dans la liste de menu	*
*  et récupérer facile n'importe quelle menu dans la liste 	*/
typedef struct struct_menu {

	//id (commence à 1)
	int id;

	//position de l'une des extremité
	int x1;
	int y1;

	//position de l'extremité opposée
	int x2;
	int y2;

	//Tour acheté
	//Tour* tour;

	//Pointeur vers l'élément suivant
	struct struct_menu* p_next;

}Menu;

/*typedef struct struct_lshot {

	//puissance de tir
	float power;

	//Taille de la liste
	size_t length;

	//Pointeur
	Shot *p_head; //pointeur vers le premier element
	Shot *p_tail; //pointeur vers le dernier element
}LShot;*/


/************* Appel de fonction *************/
int clickMenuTour(LTower*, int, int);

#endif
