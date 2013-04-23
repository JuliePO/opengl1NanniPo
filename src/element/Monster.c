#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Appel de la structures
#include "element/Monster.h"

/************* Création d'une nouvelle liste de calque *************/
/* Initialisation de la liste de calque et allocation de mémoire pour la liste de calques	*
*  Retourne la liste de calques									*/

LMonster* new_LMonster(void) {
	
	//Alloue de la mémoire 
	LMonster *p_lmonster = malloc(sizeof(LMonster));
	if (p_lmonster != NULL) {
		p_lmonster->length = 0;
		p_lmonster->p_head = NULL;
		p_lmonster->p_tail = NULL;
	}
	return p_lmonster;
}

/************* Ajouter un monstre en fin de liste *************/
/* Ajoute un calque à la liste. Alloue la place mémoire pour le calque et attribue les valeurs	*
*  Prend en paramètre la liste de calque, l'opacite et le mode d'opération du calque et créer 	*
*  la nouvelle image avec une image blanche. 							*/

int addMonster(LMonster* p_lmonster, char* type, float pv, float resistance, char type_tower, float pace) {

	// On vérifie si notre liste a été allouée
	if (p_lmonster != NULL) {
		//Création d'un nouveau calque
		Monster* new_monster = malloc(sizeof(Monster)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_monster != NULL) {

			new_monster->type = type;
			new_monster->pv = pv;
			new_monster->resistance = resistance;
			new_monster->type_tower = type_tower;
			new_monster->pace = pace;
	
			//Pointer vers le calque suivant à NULL car on rajoute à la fin de la liste	
			new_monster->p_next = NULL; 

			new_monster->id = (p_lmonster->p_tail->id) + 1;

			// Relie le dernier calque de la liste au nouveau calque
			p_lmonster->p_tail->p_next = new_monster; 
			// Pointe p_prev du nouveau calque sur le dernier calque de la liste
			new_monster->p_prev = p_lmonster->p_tail; 
			// Pointe la fin de la liste sur le nouveau calque
			p_lmonster->p_tail = new_monster; 

			// On augmente de 1 la taille de la liste
			p_lmonster->length++; 
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

LMonster* removeMonster(LMonster* p_lmonster, Monster* p_courant) {

	// On vérifie si notre liste a été allouée
	if (p_lmonster != NULL) {

		if(p_courant != NULL) {

			//Vérifie s'il reste au moins un calque, si c'est le dernier calque alors ne le supprime pas
			if(p_lmonster->length > 1) {

				//Si c'est le dernier calque de la liste
				if (p_courant->p_next == NULL) {
					
					//Pointe la fin de la liste sur le calque précédent
					p_lmonster->p_tail = p_courant->p_prev;
					//Lien du dernier calque vers le calque suivant est NULL
					p_lmonster->p_tail->p_next = NULL;
						
				}
			
				//Si c'est le premier calque de la liste
				else if (p_courant->p_prev == NULL) {
					//Pointe la tête de la liste vers le calque suivant
					p_lmonster->p_head = p_courant->p_next;
					//Le lien vers du deuxième calque vers le calque précédent est NULL
			 		p_lmonster->p_head->p_prev = NULL;
					p_lmonster->p_head->id = 0;
						
					//Création d'un calque temporaire pour parcourir la liste de calque
					Monster *p_temp = p_lmonster->p_head->p_next;
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
					Monster *p_temp = p_courant->p_next;
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
				p_lmonster->length--;

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
	return p_lmonster; 
}

