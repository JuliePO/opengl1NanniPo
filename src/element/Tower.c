#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "element/Tower.h"
#include "element/Monster.h"
#include "geometry/Intersection.h"

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
	else {
		fprintf(stderr, "Erreur lors de l'allocation memoire de la liste de tours\n");
		return NULL;
	}
	return p_ltower;
}

/************* Ajouter une tour en fin de liste *************/
/* Ajoute une tour à la liste. Alloue la place mémoire pour la tour et attribue les valeurs	*
*  Prend en paramètre la liste de tours, la puissance d'attaque, la vitesse d'attaque, le type 	*
*  le périmétre d'action et le cout. Retourne 0 en cas d'erreur et 1 sinon			*/

int addTower(LTower* p_ltower, float power, float rate, char* type_tower, float range, int cost, float x, float y) {

	// On vérifie si notre liste a été allouée
	if (p_ltower != NULL) {
		//Création d'une nouvelle tour
		Tower* new_tower = malloc(sizeof(Tower)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_tower !=  NULL) {

			new_tower->rate = rate;
			new_tower->range = range;
			new_tower->type_tower = type_tower;
			new_tower->cost = cost;
			new_tower->power = power;
			new_tower->x = x;
			new_tower->y = y;
	
			//Pointer vers la tour suivant à NULL car on rajoute à la fin de la liste	
			new_tower->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (p_ltower->p_tail == NULL) {

				// Pointe la tête de la liste sur la nouvelle tour
				p_ltower->p_head = new_tower; 

				//Pointe p_prev de la nouvelle tour à NULL
				new_tower->p_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				// Pointe p_prev de la nouvelle tour sur la dernière tour de la liste
				new_tower->p_prev = p_ltower->p_tail; 

				// Relie la dernière tour de la liste à la nouvelle tour
				p_ltower->p_tail->p_next = new_tower;  
			}

			// Pointe la fin de la liste sur la nouvelle tour
			p_ltower->p_tail = new_tower; 

			// On augmente de 1 la taille de la liste
			p_ltower->length++; 
		}
		else {
			fprintf(stderr, "Problème dans la creation de la nouvelle tour\n");
			return 0;
		}

	}
	else {
		fprintf(stderr, "Cette liste de tours n'existe pas\n");
		return 0;
	}

	return 1; 
}

/************* Vérification si un monstre entre dans le périmètre d'action de la tour *************/
/* Vérifie si un monstre entre dans le périmètre d'action => vérifie l'équation :		*
*  (x - x1)² + (y - y1)² <= R² avec (x1, y1) pour centre du cercle et R son rayon	 	*
*  x et y sont les coordonées des 4 points du quadrilatère qui contient le monstre.		*
*  Prend en paramètre la liste de monstre, la tour. Retourne NULL s'il n'y a pas d'intersection,*
*  ou en cas d'erreur et retourne le pointeur monstre sinon					*/

Monster* inSight (LMonster* p_lmonster, Tower* p_courant) {

	if(p_lmonster != NULL){

		if(p_courant != NULL) {

			Monster *p_proche = NULL;

			//Variables pour savoir qui est le plus proche
			Point2D pointIntersection, pointProche, point1, point2;
			Vector2D vectorIntersection, vectorProche;
			float normeIntersection, normeProche = -1;

			//Création d'un monstre temporaire pour parcourir la liste de monstres
			Monster *p_tmp = p_lmonster->p_head;

			//Parcours la liste de monstres
			while(p_tmp != NULL){

				Point2D point;
				point.x = p_courant->x; point.y = p_courant->y; //centre

				point1.x = p_tmp->x + 20; point1.y = p_tmp->y + 20;
				point2.x = p_tmp->x - 20; point2.y = p_tmp->y - 20;

				//Vérifie s'il y a une intersection
				if(intersectionCarreDisque (point1, point2, p_courant->range, point) == 1) {

					pointIntersection.x = p_tmp->x; pointIntersection.y = p_tmp->y;
					vectorIntersection = Vector(point, pointIntersection);
					normeIntersection = Norm(vectorIntersection);
				
					//S'il n'y a pas de point d'intersection avant
					if(normeProche == -1) {
						vectorProche = Vector(point, pointProche);
						normeProche = Norm(vectorProche);
						p_proche = p_tmp;
					}
					//Si la distance du nouveau point d'intersection est plus proche que celle stocker
					if(normeIntersection < normeProche) {
						vectorProche = vectorIntersection;
						normeProche = normeIntersection;
						p_proche = p_tmp;
					}

				}


				p_tmp = p_tmp->p_next;

			}

			//retourne le pointeur vers le monstre le plus proche
			return p_proche;

		}
		else {
			fprintf(stderr, "Cette tour n'existe pas\n");
			return NULL;
		}

	}
	else {
		fprintf(stderr, "Cette liste de monstre n'existe pas\n");
		return NULL;
	}

	return NULL;

}

/****************** Vérifier si la tour est sur un zone constructible ***********************/
/* Vérifie si la tour est sur une zone constructible : Vérifie si les coordonnées de chaque 	*
*  extremité fait partie de la liste de point. Prend en paramètre la liste de pixel et les deux	*
*  extremités (deux points). Retourne 1 si c'est valide, sinon 0.		*/

int verificationConstruct(LNode* l_node, Point2D point1, Point2D point2) {

	if(l_node != NULL) {

		int i, test = 0;
		Point2D point;

		for(i = 0; i < 4; i++) {

			//Vérifie avec les quatres points du quad
			switch(i) {
				case 0 : 
					point.x = point1.x; point.y = point1.y;
					break;
				case 1 : 
					point.x = point1.x; point.y = point2.y;
					break;
				case 2 :
					point.x = point2.x; point.y = point2.y;
					break;
				case 3 :
					point.x = point2.x; point.y = point1.y;
					break;
			}

			//Créer un pointeur temporaire node pour parcourir la liste de noeud
			Node* p_tmp = l_node->p_head;

			while(p_tmp != NULL){

				if(point.x == p_tmp->x && point.y == p_tmp->y)
					test++;

				p_tmp = p_tmp->p_next;
			}

		}

		//Si les 4 extremité sont dans la zone constructible
		if(test < 4)
			return 0;

	}
	else {
		fprintf(stderr, "Il y a un probleme avec la liste de points constructible\n");
		return 0;
	}

	return 1;

}

/****************** Faire bouger la tour ***********************/
/* Fait bouger la tour en fonction des positions passé en paramètre. Passe en paramètre la liste de tours, 	*
*  la tour que l'on souhaite bouger, la nouvelle position : x et y. Retourne 0 en cas d'erreur et & sinon	*/
int moveTower(LTower* p_ltower, Tower* p_courant, LNode* l_node, float x, float y) {

	if(p_ltower != NULL) {

		if(p_courant != NULL) {

			p_courant->x = x;
			p_courant->y = y;
		
			Point2D point1, point2;
			point1.x = x + 20; point1.y = y + 20;
			point2.x = x - 20; point2.y = y - 20;

			if(verificationConstruct(l_node, point1, point2) == 1) {

				//Si ce n'est pas le premier de la liste
				if(p_courant->p_prev != NULL){

					Point2D point3, point4;
					//Créer un pointeur tour temporaire pour parcourir la liste
					Tower* p_tmp = p_ltower->p_head;

					//Parcour de la liste
					while(p_tmp->p_next != NULL) {

						point3.x = (p_tmp->x) + 20; point3.y = (p_tmp->y) + 20;
						point4.x = (p_tmp->x) - 20; point4.y = (p_tmp->y) - 20;

						//Vérifie qu'il ne se trouve pas sur une autre tour (pas d'intersection)
						if(intersectionCarres (point1, point2, point3, point4) == 0)
							return 1;
						else
							return 0;
					}
				}
				//Sinon pas besoin de faire la vérification pour les collisions de quads
				else
					return 1;		
			}
		}
		else {
			fprintf(stderr, "Cette tour n'existe pas\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Erreur : il y a un problème avec la liste de tours\n");
		return 0;
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

				if(p_ltower->p_tail != NULL) {
					//Lien de la dernière tour vers la tour suivante est NULL
					p_ltower->p_tail->p_next = NULL;
				}
				else
					p_ltower->p_head = NULL;
					
			}
		
			//Si c'est la première de la liste
			else if (p_courant->p_prev == NULL) {
				//Pointe la tête de la liste vers la tour suivante
				p_ltower->p_head = p_courant->p_next;

				if(p_ltower->p_head != NULL) {
					//Le lien vers de la deuxième tour vers la tour précédente est NULL
			 		p_ltower->p_head->p_prev = NULL;
				}
				else
					p_ltower->p_tail = NULL;
			}

			else {
				//Relie la tour suivante à la tour précédente de la tour que l'on veut supprmer 
				p_courant->p_next->p_prev = p_courant->p_prev;
				//Relie la tour précédente à la tour suivante de la tour que l'on veut supprmer 
				p_courant->p_prev->p_next = p_courant->p_next;

			}
			//Libère espace mémoire : supprime la tour
			free(p_courant);
			//Décrémente de un la taille de la liste
			p_ltower->length--;

		}
		else
			fprintf(stderr, "Cette tour n'existe pas");
	}
	else 
		fprintf(stderr, "Cette liste de tours n'existe pas");

	// on retourne notre nouvelle liste
	return p_ltower; 
}

