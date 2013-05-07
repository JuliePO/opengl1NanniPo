#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Appel de la structures
#include "element/Monster.h"

/************* Création d'une nouvelle liste de monstres *************/
/* Initialisation de la liste de monstres et allocation de mémoire pour la liste de monstres	*
*  Retourne la liste de monstres									*/

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
/* Ajoute un monstre à la liste. Alloue la place mémoire pour le monstre et attribue les valeurs	*
*  Prend en paramètre la liste de monstres, le type de monstre, les points de vie, la résistance	*
*  un type de tour et la vitesse de déplacement. Retourne 0 en cas d'erreur et 1 sinon.			*/

int addMonster(LMonster* p_lmonster, char* type, float pv, float resistance, char type_tower, float pace) {

	// On vérifie si notre liste a été allouée
	if (p_lmonster != NULL) {

		//Création d'un nouveau monstre
		Monster* new_monster = malloc(sizeof(Monster)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_monster != NULL) {

			new_monster->type = type;
			new_monster->pv = pv;
			new_monster->resistance = resistance;
			new_monster->type_tower = type_tower;
			new_monster->pace = pace;
	
			//Pointer vers le monstre suivant à NULL car on rajoute à la fin de la liste	
			new_monster->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (p_lmonster->p_tail == NULL) {
	
				new_monster->id = 1; 

				// Pointe la tête de la liste sur le nouveau monstre
				p_lmonster->p_head = new_monster; 

				//Point p_prev du nouveau monstre à NULL
				new_monster->p_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				new_monster->id  = (p_lmonster->p_tail->id) + 1;

				// Relie le dernier monstre de la liste au nouveau monstre
				p_lmonster->p_tail->p_next = new_monster;  

				// Relie le dernier monstre de la liste au nouveau monstre
				p_lmonster->p_tail->p_next = new_monster; 

				// Pointe p_prev du nouveau monstre sur le dernier monstre de la liste
				new_monster->p_prev = p_lmonster->p_tail; 
			}
			
			// Pointe la fin de la liste sur le nouveau monstre
			p_lmonster->p_tail = new_monster; 

			// On augmente de 1 la taille de la liste
			p_lmonster->length++; 
		}
		else {
			printf("Problème dans la creation du nouveau monstre\n");
			return 0;
		}

	}
	else {
		printf("Cette liste de monstres n'existe pas\n");
		return 0;
	}

	return 1; 
}


/************* Supprimer un monstre selon sa position *************/
/* Supprime un monstre selon sa position, vérifie si c'est le premier, le dernier ou un monstre dans la liste puis le supprime	 	*
*  Prend en paramètre la liste de monstres et le monstre à supprimer et retourne la liste de monstres.					*/

LMonster* removeMonster(LMonster* p_lmonster, Monster* p_courant) {

	// On vérifie si notre liste a été allouée
	if (p_lmonster != NULL) {

		if(p_courant != NULL) {

			//Si c'est le dernier monstre de la liste
			if (p_courant->p_next == NULL) {
			
				//Pointe la fin de la liste sur le monstre précédent
				p_lmonster->p_tail = p_courant->p_prev;
				//Lien du dernier monstre vers le monstre suivant est NULL
				p_lmonster->p_tail->p_next = NULL;
				
			}
	
			//Si c'est le premier monstre de la liste
			else if (p_courant->p_prev == NULL) {
				//Pointe la tête de la liste vers le monstre suivant
				p_lmonster->p_head = p_courant->p_next;
				//Le lien vers du deuxième monstre vers le monstre précédent est NULL
		 		p_lmonster->p_head->p_prev = NULL;
				p_lmonster->p_head->id = 1;
				
				//Création d'un monstre temporaire pour parcourir la liste de monstres
				Monster *p_tmp = p_lmonster->p_head->p_next;
				int i = 1;

				// Parcours de la liste de monstre, tant que i est inférieur à la position souhaitée
				while (p_tmp != NULL) {
					p_tmp->id = ++i;
					p_tmp = p_tmp->p_next;
				}
			}

			else {
				//Relie le monstre suivant au monstre précédent du monstre que l'on veut supprmer 
				p_courant->p_next->p_prev = p_courant->p_prev;
				//Relie le monstre précédent au monstre suivant du monstre que l'on veut supprmer 
				p_courant->p_prev->p_next = p_courant->p_next;

				//Création d'un monstre temporaire pour parcourir la liste de monstres à partir du monstre suivant du monstre que l'on veut supprimer
				Monster *p_tmp = p_courant->p_next;
				int i = p_courant->p_prev->id;

				// Parcours de la liste de monstres, tant que i est inférieur à la position souhaitée
				while (p_tmp != NULL) {
					p_tmp->id = ++i;
					p_tmp = p_tmp->p_next;
				}

			}
			//Libère espace mémoire : supprime le monstre
			free(p_courant);
			//Décrémente de un la taille de la liste
			p_lmonster->length--;

		}
		else
			printf("Ce monstre n'existe pas");
	}
	else 
		printf("Cette liste de monstres n'existe pas");

	// on retourne notre nouvelle liste
	return p_lmonster; 
}

