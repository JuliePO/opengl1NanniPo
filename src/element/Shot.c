#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Appel de la structures
#include "element/Tower.h"
#include "element/Monster.h"
#include "element/Shot.h"

/************* Création d'une nouvelle liste de missiles *************/
/* Initialisation de la liste de missiles et allocation de mémoire pour la liste de missiles		*
*  Retourne la liste de missiles									*/

LShot* new_LShot(void) {
	
	//Alloue de la mémoire 
	LShot *p_lshot = malloc(sizeof(LShot));
	if (p_lshot != NULL) {
		p_lshot->length = 0;
		p_lshot->p_head = NULL;
		p_lshot->p_tail = NULL;
	}
	return p_lshot;
}

/************* Ajouter un missile en fin de liste *************/
/* Ajoute un missile à la liste. Alloue la place mémoire pour le missile et attribue les valeurs	*
*  Prend en paramètre la liste de missiles, le monstre visé, la tour qui envoie le missile. 		*
*  Retourne 0 en cas d'erreur et 1 sinon								*/

int addShot(LShot* p_lshot, Monster* target, Tower* tower) {

	// On vérifie si notre liste a été allouée
	if (p_lshot != NULL) {
		//Création d'un nouveau missile
		Shot* new_shot = malloc(sizeof(Shot)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_shot != NULL) {

			new_shot->x = tower->x;
			new_shot->y = tower->y;

			new_shot->target = target;
			new_shot->tower = tower;

	
			//Pointer vers le missile suivant à NULL car on rajoute à la fin de la liste	
			new_shot->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (p_lshot->p_tail == NULL) {
	
				new_shot->id = 1; 

				// Pointe la tête de la liste sur le nouveau missile
				p_lshot->p_head = new_shot; 

				//Pointe p_prev de le nouveau missile à NULL
				new_shot->p_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				new_shot->id  = (p_lshot->p_tail->id) + 1;

				// Relie le dernier missile de la liste au nouveau missile
				p_lshot->p_tail->p_next = new_shot;  

				// Pointe p_prev du nouveau missile sur le dernier missile de la liste
				new_shot->p_prev = p_lshot->p_tail; 
			}

			// Pointe la fin de la liste sur le nouveau missile
			p_lshot->p_tail = new_shot; 

			// On augmente de 1 la taille de la liste
			p_lshot->length++; 
		}
		else {
			printf("Problème dans la creation du nouveau missile\n");
			return 0;
		}

	}
	else {
		printf("Cette liste de missiles n'existe pas\n");
		return 0;
	}

	return 1; 
}


/************* Supprimer un missile selon sa position *************/
/* Supprime une missile selon sa position, vérifie si c'est le premier, le dernier ou un missile dans la liste puis le supprime *
*  Prend en paramètre la liste de missiles et le missile à supprimer et retourne la liste de missiles.				*/

LShot* removeShot(LShot* p_lshot, Shot* p_courant) {

	// On vérifie si notre liste a été allouée
	if (p_lshot != NULL) {

		if(p_courant != NULL) {

			//Si c'est le dernier missile de la liste
			if (p_courant->p_next == NULL) {
				
				//Pointe la fin de la liste sur le missile précédent
				p_lshot->p_tail = p_courant->p_prev;
				//Lien de le dernier missile vers le missile suivant est NULL
				p_lshot->p_tail->p_next = NULL;
					
			}
		
			//Si c'est le premier de la liste
			else if (p_courant->p_prev == NULL) {
				//Pointe la tête de la liste vers le missile suivant
				p_lshot->p_head = p_courant->p_next;
				//Le lien vers de le deuxième misiile vers le missile précédent est NULL
		 		p_lshot->p_head->p_prev = NULL;
				p_lshot->p_head->id = 1;
					
				//Création d'un missile temporaire pour parcourir la liste de missiles
				Shot *p_temp = p_lshot->p_head->p_next;
				int i = 1;

				// Parcours de la liste de missiles, tant que i est inférieur à la position souhaitée
				while (p_temp != NULL) {
					p_temp->id = ++i;
					p_temp = p_temp->p_next;
				}
			}

			else {
				//Relie le missile suivant au missile précédent du missile que l'on veut supprmer 
				p_courant->p_next->p_prev = p_courant->p_prev;
				//Relie le missile précédent au missile suivant du missile que l'on veut supprmer 
				p_courant->p_prev->p_next = p_courant->p_next;

				//Création d'un missile temporaire pour parcourir la liste de missiles à partir du missile suivant du missile que l'on veut supprimer
				Shot *p_temp = p_courant->p_next;
				int i = p_courant->p_prev->id;

				// Parcours de la liste de missiles, tant que i est inférieur à la position souhaitée
				while (p_temp != NULL) {
					p_temp->id = ++i;
					p_temp = p_temp->p_next;
				}

			}
			//Libère espace mémoire : supprime le missile
			free(p_courant);
			//Décrémente de un la taille de la liste
			p_lshot->length--;

		}
		else
			printf("Ce missile n'existe pas");
	}
	else 
		printf("Cette liste de missiles n'existe pas");

	// on retourne notre nouvelle liste
	return p_lshot; 
}
