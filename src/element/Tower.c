#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Appel de la structures
#include "element/Tower.h"

/************* Création d'une nouvelle liste de calque *************/
/* Initialisation de la liste de calque et allocation de mémoire pour la liste de calques	*
*  Retourne la liste de calques									*/

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

/************* Ajouter un monstre en fin de liste *************/
/* Ajoute un calque à la liste. Alloue la place mémoire pour le calque et attribue les valeurs	*
*  Prend en paramètre la liste de calque, l'opacite et le mode d'opération du calque et créer 	*
*  la nouvelle image avec une image blanche. 							*/

int addTower(LTower* p_ltower, float power, float rate, char type_tower, float range, int cost) {

	// On vérifie si notre liste a été allouée
	if (p_ltower != NULL) {
		//Création d'un nouveau calque
		Tower* new_tower = malloc(sizeof(Tower)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_tower != NULL) {

			new_tower->power = power;
			new_tower->rate = rate;
			new_tower->range = range;
			new_tower->type_tower = type_tower;
			new_tower->cost = cost;
	
			//Pointer vers le calque suivant à NULL car on rajoute à la fin de la liste	
			new_tower->p_next = NULL; 

			new_tower->id = (p_ltower->p_tail->id) + 1;

			// Relie le dernier calque de la liste au nouveau calque
			p_ltower->p_tail->p_next = new_tower; 
			// Pointe p_prev du nouveau calque sur le dernier calque de la liste
			new_tower->p_prev = p_ltower->p_tail; 
			// Pointe la fin de la liste sur le nouveau calque
			p_ltower->p_tail = new_tower; 

			// On augmente de 1 la taille de la liste
			p_ltower->length++; 
		}
		else {
			printf("Problème dans la creation du nouveau calque\n");
			return 0;
		}

	}
	else {
		printf("Cette liste de calque n'existe pas\n");
		return 0;
	}

	return 1; 
}


/************* Supprimer un calque selon sa position *************/
/* Supprime un calque selon sa position, vérifie si c'est le premier, le dernier ou un calque dans la liste puis supprime le calque 	*
*  Prend en paramètre la liste de calque et le calque à supprimer et retourne la liste de calque.					*/

LTower* removeTower(LTower* p_ltower, Tower* p_courant) {

	// On vérifie si notre liste a été allouée
	if (p_ltower != NULL) {

		if(p_courant != NULL) {

			//Vérifie s'il reste au moins un calque, si c'est le dernier calque alors ne le supprime pas
			if(p_ltower->length > 1) {

				//Si c'est le dernier calque de la liste
				if (p_courant->p_next == NULL) {
					
					//Pointe la fin de la liste sur le calque précédent
					p_ltower->p_tail = p_courant->p_prev;
					//Lien du dernier calque vers le calque suivant est NULL
					p_ltower->p_tail->p_next = NULL;
						
				}
			
				//Si c'est le premier calque de la liste
				else if (p_courant->p_prev == NULL) {
					//Pointe la tête de la liste vers le calque suivant
					p_ltower->p_head = p_courant->p_next;
					//Le lien vers du deuxième calque vers le calque précédent est NULL
			 		p_ltower->p_head->p_prev = NULL;
					p_ltower->p_head->id = 0;
						
					//Création d'un calque temporaire pour parcourir la liste de calque
					Tower *p_temp = p_ltower->p_head->p_next;
					int i = 0;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_temp != NULL) {
						p_temp->id = ++i;
						p_temp = p_temp->p_next;
					}
					//Libère espace mémoire
					free(p_temp);
				}

				else {
					//Relie le calque suivant au calque précédent du calque que l'on veut supprmer 
					p_courant->p_next->p_prev = p_courant->p_prev;
					//Relie le calque précédent au calque suivant du calque que l'on veut supprmer 
					p_courant->p_prev->p_next = p_courant->p_next;

					//Création d'un calque temporaire pour parcourir la liste de calque à partir du calque suivant du calque que l'on veut supprimer
					Tower *p_temp = p_courant->p_next;
					int i = p_courant->p_prev->id;

					// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
					while (p_temp != NULL) {
						p_temp->id = ++i;
						p_temp = p_temp->p_next;
					}

				}
				//Libère espace mémoire : supprime le calque
				free(p_courant);
				//Décrémente de un la taille de la liste
				p_ltower->length--;

			}
			else
				printf("Erreur : impossible de supprimer le calque\n");
		}
		else
			printf("Ce calque n'existe pas");
	}
	else 
		printf("Cette liste de calque n'existe pas");

	// on retourne notre nouvelle liste
	return p_ltower; 
}
