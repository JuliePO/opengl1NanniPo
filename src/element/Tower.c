#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Appel de la structures
#include "element/Tower.h"
#include "element/Monster.h"

/************* Création d'une nouvelle liste de tours *************/
/* Initialisation de la liste de tours et allocation de mémoire pour la liste de tours		*
*  Retourne la liste de tours									*/

LTower* new_LTower(void) {
	
	//Alloue de la mémoire 
	LTower *p_ltower = malloc(sizeof(LTower));
	if (p_ltower != NULL) {
		p_ltower->length = 0;
		p_ltower->p_head = NULL;
		p_ltower->p_tail = NULL;
	}
	return p_ltower;
}

/************* Ajouter une tour en fin de liste *************/
/* Ajoute une tour à la liste. Alloue la place mémoire pour la tour et attribue les valeurs	*
*  Prend en paramètre la liste de tours, la puissance d'attaque, la vitesse d'attaque, le type 	*
*  le périmétre d'action et le cout. Retourne 0 en cas d'erreur et 1 sinon			*/

int addTower(LTower* p_ltower, float power, float rate, char* type_tower, float range, int cost) {

	// On vérifie si notre liste a été allouée
	if (p_ltower != NULL) {
		//Création d'une nouvelle tour
		Tower* new_tower = malloc(sizeof(Tower)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_tower != NULL) {

			new_tower->power = power;
			new_tower->rate = rate;
			new_tower->range = range;
			new_tower->type_tower = type_tower;
			new_tower->cost = cost;
			new_tower->x = 0;
			new_tower->y = 0;
	
			//Pointer vers la tour suivant à NULL car on rajoute à la fin de la liste	
			new_tower->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (p_ltower->p_tail == NULL) {
	
				new_tower->id = 1; 

				// Pointe la tête de la liste sur la nouvelle tour
				p_ltower->p_head = new_tower; 

				//Pointe p_prev de la nouvelle tour à NULL
				new_tower->p_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				new_tower->id  = (p_ltower->p_tail->id) + 1;

				// Relie la dernière tour de la liste à la nouvelle tour
				p_ltower->p_tail->p_next = new_tower;  

				// Pointe p_prev de la nouvelle tour sur la dernière tour de la liste
				new_tower->p_prev = p_ltower->p_tail; 
			}

			// Pointe la fin de la liste sur la nouvelle tour
			p_ltower->p_tail = new_tower; 

			// On augmente de 1 la taille de la liste
			p_ltower->length++; 
		}
		else {
			printf("Problème dans la creation de la nouvelle tour\n");
			return 0;
		}

	}
	else {
		printf("Cette liste de tours n'existe pas\n");
		return 0;
	}

	return 1; 
}

/************* Vérification si un monstre entre dans le périmètre d'action de la tour *************/
/* Vérifie si un monstre entre dans le périmètre d'action => vérifie l'équation :		*
*  (x - x1)² + (y - y1)² <= R² avec (x1, y1) pour centre du cercle et R son rayon	 	*
*  x et y sont les coordonées des 4 points du quadrilatère qui contient le monstre.		*
*  Prend en paramètre la liste de monstre, la tour. 						*
*  Retourne 0 s'il n'y a pas d'intersection, -1 en cas d'erreur et 1 sinon			*/

int inSight (LMonster* p_lmonster, Tower* p_courant) {

	if(p_lmonster != NULL){

		if(p_courant != NULL) {

			//Création d'un monstre temporaire pour parcourir la liste de monstres
			Monster *p_tmp = p_lmonster->p_head;

			//Parcours la liste de monstres
			while(p_tmp != NULL){
		
				float result = ((p_tmp->x - p_courant->x)*(p_tmp->x - p_courant->x)) + ((p_tmp->y - p_courant->y)*(p_tmp->y - p_courant->y)) - ((p_courant->range)*(p_courant->range));

				if(result <= 0)
					return 1;

				p_tmp = p_tmp->p_next;

			}

		}
		else {
			printf("Cette tour n'existe pas\n");
			return -1;
		}

	}
	else {
		printf("Cette liste de monstre n'existe pas\n");
		return -1;
	}

	return 0;

}


/************* Supprimer une tour selon sa position *************/
/* Supprime une tour selon sa position, vérifie si c'est le premier, le dernier ou une tour dans la liste puis la supprime 	*
*  Prend en paramètre la liste de tours et la tour à supprimer et retourne la liste de tours.					*/

LTower* removeTower(LTower* p_ltower, Tower* p_courant) {

	// On vérifie si notre liste a été allouée
	if (p_ltower != NULL) {

		if(p_courant != NULL) {

			//Si c'est la dernière tour de la liste
			if (p_courant->p_next == NULL) {
				
				//Pointe la fin de la liste sur la tour précédente
				p_ltower->p_tail = p_courant->p_prev;
				//Lien de la dernière tour vers la tour suivante est NULL
				p_ltower->p_tail->p_next = NULL;
					
			}
		
			//Si c'est la première de la liste
			else if (p_courant->p_prev == NULL) {
				//Pointe la tête de la liste vers la tour suivante
				p_ltower->p_head = p_courant->p_next;
				//Le lien vers de la deuxième tour vers la tour précédente est NULL
		 		p_ltower->p_head->p_prev = NULL;
				p_ltower->p_head->id = 1;
					
				//Création d'une tour temporaire pour parcourir la liste de tours
				Tower *p_temp = p_ltower->p_head->p_next;
				int i = 1;

				// Parcours de la liste de tours, tant que i est inférieur à la position souhaitée
				while (p_temp != NULL) {
					p_temp->id = ++i;
					p_temp = p_temp->p_next;
				}
			}

			else {
				//Relie la tour suivante à la tour précédente de la tour que l'on veut supprmer 
				p_courant->p_next->p_prev = p_courant->p_prev;
				//Relie la tour précédente à la tour suivante de la tour que l'on veut supprmer 
				p_courant->p_prev->p_next = p_courant->p_next;

				//Création d'une tour temporaire pour parcourir la liste de tours à partir de la tour suivante de la tour que l'on veut supprimer
				Tower *p_temp = p_courant->p_next;
				int i = p_courant->p_prev->id;

				// Parcours de la liste de tours, tant que i est inférieur à la position souhaitée
				while (p_temp != NULL) {
					p_temp->id = ++i;
					p_temp = p_temp->p_next;
				}

			}
			//Libère espace mémoire : supprime la tour
			free(p_courant);
			//Décrémente de un la taille de la liste
			p_ltower->length--;

		}
		else
			printf("Cette tour n'existe pas");
	}
	else 
		printf("Cette liste de tours n'existe pas");

	// on retourne notre nouvelle liste
	return p_ltower; 
}
