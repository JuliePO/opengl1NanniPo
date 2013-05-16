#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Appel de la structures
#include "element/Tower.h"
#include "element/Monster.h"
#include "element/Shot.h"
#include "geometry/Intersection.h"

/************* Création d'une nouvelle liste de missiles *************/
/* Initialisation de la liste de missiles et allocation de mémoire pour la liste de missiles		*
*  Retourne la liste de missiles									*/

LShot* new_LShot(float power) {
	
	//Alloue de la mémoire 
	LShot *p_lshot = (LShot*)malloc(sizeof(LShot));
	if (p_lshot != NULL) {
		p_lshot->power = power;
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

int addShot(LShot* p_lshot, Monster* target, int x, int y) {

	// On vérifie si notre liste a été allouée
	if(p_lshot != NULL) {

		//On vérifie que le monstre a été alloué
		if(target != NULL) {

			//Création d'un nouveau missile
			Shot* new_shot = (Shot*)malloc(sizeof(Shot)); 
		
			// On vérifie si le malloc n'a pas échoué
			if (new_shot) {

				new_shot->x = x;
				new_shot->y = y;

				new_shot->target = target;
	
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
			printf("Ce monstre n'existe pas\n");
			return 0;
		}
	}
	else {
		printf("Cette liste de missiles n'existe pas\n");
		return 0;
	}

	return 1; 
}

/************* Bouger les missiles en direction de l'ennemi *************/
/* Change la position des missiles pour qu'ils bouge vers l'ennemi. Prend en paramètre la liste de  	*
*  missiles. Retourne 0 en cas d'erreur et 1 sinon.						 	*/

int moveShot(LShot* p_lshot) {

	//Vérifie que la liste est allouée
	if(p_lshot != NULL) {

		//Créer un missile temporaire pour parcourir la liste de missiles
		Shot *p_tmp = p_lshot->p_head;

		//Parcours la liste de missiles
		while(p_tmp != NULL){

			Point2D point_target;
			Point2D point_shot;

			point_target.x = p_tmp->target->x;
			point_target.y = p_tmp->target->y;

			//printf("Monstre %d %d\n", p_tmp->target->x, p_tmp->target->y);

			point_shot.x = p_tmp->x;
			point_shot.y = p_tmp->y;

			//printf("Missile %d %d\n", p_tmp->x, p_tmp->y);

			Vector2D vector = Vector(point_shot, point_target);

			//printf("Vecteur : %f %f\n", vector.x, vector.y);

			vector = Normalize(vector);

			//printf("Vecteur normalisé : %d %d\n", vector.x, vector.y);

			Point2D result = PointPlusVector(point_shot, vector);

			p_tmp->x = result.x;
			p_tmp->y = result.y;

			p_tmp = p_tmp->p_next;
		}

	}
	else {
		printf("La liste de missiles n'existe pas ou est vide\n");
		return 0;
	}

	return 1;
}

/************* Collision entre le missile et l'ennemie *************/
/* Vérifie si le missile entre en collision avec le missile. Si oui supprime le missile et   	*
*  déduit les points de vie du monstre. Prend en paramètre la liste de monstre et le monstre.   *
*  Retourne 0 en cas d'erreur et 1 sinon.							*/

int collisionMissile(LShot* p_lshot, LMonster* p_lmonster) {

	//On vérifie si notre liste a été allouée
	if(p_lshot != NULL) {

		//Créer un missile temporaire pour supprimer le shot
		int testShot = 0;
		Monster *p_monsterSupp = NULL;
		Shot *p_tmpSupp = NULL;
			
		//Créer un pointeur missile temporaire pour parcourir la liste de missiles
		Shot *p_tmp = p_lshot->p_head;

		//Parcours la liste de missiles
		while(p_tmp != NULL){

			//Vérifie s'il y a une intersection pour les quatres coté du quads du monstre
			Point2D point1, point2, pointC1, pointC2;
			
			point1.x = p_tmp->target->x + 20; point1.y = p_tmp->target->y + 20;
			point2.y = p_tmp->target->x - 20; point2.y = p_tmp->target->y - 20;

			pointC1.x = p_tmp->x + 5; pointC1.y = p_tmp->y + 5;
			pointC2.x = p_tmp->x - 5; pointC2.y = p_tmp->y - 5;
				

			//Vérifie s'il y a une intersection
			if(intersectionCarres(point1, point2, pointC1, pointC2) == 1) {

				//retire des points de vie
				p_tmp->target->pv -= p_lshot->power;

				if(p_tmp->target->pv <= 0){
					
					p_tmp->target->pv = 0;
					Monster* new_monster = new_Monster(-2, -2); 
					p_monsterSupp = p_tmp->target;
					p_tmp->target = new_monster;

					//Créer un pointeur missile temporaire pour parcourir la liste de missiles
					Shot *p_temp = p_lshot->p_head;

					//Parcours la liste de missiles
					while(p_temp != NULL){

						if(p_temp->target == p_monsterSupp)
							p_temp->target = new_monster;

						p_temp = p_temp->p_next;

					}
					//retire le monstre de la liste de monstre
					p_lmonster = removeMonster(p_lmonster, p_monsterSupp);
					
				}

				//testShot = 1;
				//Mets dans la varaible temporaire pour le supprimer
				p_tmpSupp = p_tmp;
			
			}

			if(strcmp(p_tmp->target->type, "v") == 0) {

				if(p_tmp->x < 180 || p_tmp->y < 40) {
					p_tmpSupp = p_tmp;
					testShot = 1;
				}
			}
	
			p_tmp = p_tmp->p_next;

			if(testShot == 1) {
				testShot = 0;
				p_lshot = removeShot(p_lshot, p_tmpSupp);//Retire le missile de la liste
			}

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
				if(p_lshot->p_tail != NULL) {
					//Lien de le dernier missile vers le missile suivant est NULL
					p_lshot->p_tail->p_next = NULL;
				}
					
			}
		
			//Si c'est le premier de la liste
			else if (p_courant->p_prev == NULL) {
				//Pointe la tête de la liste vers le missile suivant
				p_lshot->p_head = p_courant->p_next;
				if(p_lshot->p_head != NULL) {
					//Le lien vers de le deuxième misiile vers le missile précédent est NULL
			 		p_lshot->p_head->p_prev = NULL;
				}
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
			printf("Ce missile n'existe pas\n");
	}
	else 
		printf("Cette liste de missiles n'existe pas\n");

	// on retourne notre nouvelle liste
	return p_lshot; 
}
