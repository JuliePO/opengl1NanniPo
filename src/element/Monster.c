#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Appel de la structures
#include "element/Monster.h"
#include "ihm/Node.h"

/************* Création d'une nouvelle liste de monstres *************/
/* Initialisation de la liste de monstres et allocation de mémoire pour la liste de monstres	*
*  Retourne le pointeur sur la liste de monstres						*/

LMonster* new_LMonster(void) {
	
	//Alloue de la mémoire 
	LMonster *p_lmonster = malloc(sizeof(LMonster));
	if (p_lmonster) {
		p_lmonster->length = 0;
		p_lmonster->p_head = NULL;
		p_lmonster->p_tail = NULL;
	}
	else
		return NULL;

	return p_lmonster;
}

/************* Création d'une monstre avec les coordonnées *************/
/* Initialisation du monstre et allocation de mémoire pour la liste de monstres				*
*  Retourne le pointeur sur le monstre									*/
Monster* new_Monster(int x, int y) {

	//Alloue mémoire
	Monster *p_monster = (Monster*)malloc(sizeof(Monster));
	if(p_monster){
		p_monster->x = x;
		p_monster->y = y;
		
		p_monster->type = "v";
		p_monster->pvMax = 0;
		p_monster->pv = 0;
		p_monster->resistance = 0;
		p_monster->type_tower = "v";
		p_monster->pace = 0;
		p_monster->node_prev = NULL;
		p_monster->node_next = NULL;
	}
	else
		return NULL;

	return p_monster;

}

/************* Ajouter un monstre en fin de liste *************/
/* Ajoute un monstre à la liste. Alloue la place mémoire pour le monstre et attribue les valeurs	*
*  Prend en paramètre la liste de monstres, le type de monstre, les points de vie, la résistance	*
*  un type de tour et la vitesse de déplacement. Retourne 0 en cas d'erreur et 1 sinon.			*/

int addMonster(LMonster* p_lmonster, char* type, float pvMax, float resistance, char* type_tower, float pace, LNode* p_lnode) {

	// On vérifie si notre liste a été allouée
	if (p_lmonster != NULL) {

		//Création d'un nouveau monstre
		Monster* new_monster = (Monster*)malloc(sizeof(Monster)); 
		
		// On vérifie si le malloc n'a pas échoué
		if (new_monster) {

			new_monster->type = type;
			new_monster->pvMax = pvMax;
			new_monster->pv = pvMax;
			new_monster->resistance = resistance;
			new_monster->type_tower = type_tower;
			new_monster->pace = pace;
			new_monster->x = p_lnode->p_head->x;
			new_monster->y = p_lnode->p_head->y;
			new_monster->node_prev = p_lnode->p_head;
			new_monster->node_next = p_lnode->p_head->p_next;

			if(new_monster->node_prev->x == new_monster->node_next->x || new_monster->node_prev->y == new_monster->node_next->y)
				new_monster->e = 0;
			else {

				int dx = (new_monster->node_next->x) - (new_monster->node_prev->x);
				int dy = (new_monster->node_next->y) - (new_monster->node_prev->y);	

				if(dx > 0) {

					if(dy > 0) {

						if(dx >= dy)
							new_monster->e = (new_monster->node_next->x) - (new_monster->node_prev->x);
						else
							new_monster->e = (new_monster->node_next->y) - (new_monster->node_prev->y);
					}
					else {

						if(dx >= -dy)
							new_monster->e = (new_monster->node_next->x) - (new_monster->node_prev->x);
						else
							new_monster->e = (new_monster->node_next->y) - (new_monster->node_prev->y);

					}

				}
				else {
					if(dy > 0) {

						if(-dx >= dy)
							new_monster->e = (new_monster->node_next->x) - (new_monster->node_prev->x);
						else
							new_monster->e = (new_monster->node_next->y) - (new_monster->node_prev->y);

					}
					else {

						if(dx <= dy)
							new_monster->e = (new_monster->node_next->x) - (new_monster->node_prev->x);
						else
							new_monster->e = (new_monster->node_next->y) - (new_monster->node_prev->y);

					}
					
				}		

			}
	
			//Pointer vers le monstre suivant à NULL car on rajoute à la fin de la liste	
			new_monster->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (p_lmonster->p_tail == NULL) {
	
				new_monster->id = 1; 

				// Pointe la tête de la liste sur le nouveau monstre
				p_lmonster->p_head = new_monster; 

				//Pointe p_prev du nouveau monstre à NULL
				new_monster->p_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				new_monster->id  = (p_lmonster->p_tail->id) + 1;

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

/************* Deplacer les monstres *************/
/* Deplace les monstre : Vérifie s'il se déplace à l'horizontal, vertical ou autrement puis le déplace. Prend en paramètre la liste de	*
*  monstres et le monstre à supprimer et retourne la liste de monstres.	Retourne 0 en cas d'erreur et 1 sinon et 2 s'il est arrivé à 	*
*  la fin. 																*/
int moveMonster(LMonster* p_lmonster, Node* p_tail){

	// On vérifie si notre liste a été allouée
	if (p_lmonster != NULL) {	

		//Création d'un monstre temporaire pour parcourir la liste de monstres
		Monster *p_tmp = p_lmonster->p_head;

		//Parcours la liste de monstres
		while(p_tmp != NULL){

			//S'il avance selon l'axe des y
			if(p_tmp->node_prev->x == p_tmp->node_next->x) {
			
				//S'il va vers le haut
				if(p_tmp->node_prev->y < p_tmp->node_next->y)
					(p_tmp->y)++; //Fait avancer le monstre vers le haut
				//Sinon il avance vers le bas
				else
					(p_tmp->y)--; //Fait avancer le monstre vers le haut
			}
			//S'il avance selon l'axe des x
			else if(p_tmp->node_prev->y == p_tmp->node_next->y) {

				//S'il va vers la droite
				if(p_tmp->node_prev->x < p_tmp->node_next->x)
					(p_tmp->x)++; //Fait avancer le monstre vers le haut
				//Sinon il avance vers la gauche
				else
					(p_tmp->x)--; //Fait avancer le monstre vers le haut

			}
			//S'il avance sur l'axe des x et des y
			else {

				int dx, dy;
				dx = ((p_tmp->node_next->x) - (p_tmp->node_prev->x))*2;
				dy = ((p_tmp->node_next->y) - (p_tmp->node_prev->y))*2;
				

				if(dx > 0) {

					if(dy > 0) {
						//Si la longueur entre les deux points et plus grande que la hauteur entre les deux points
						if(dx >= dy) {

							(p_tmp->x)++;
							p_tmp->e -= dy;
						
							if(p_tmp->e <= 0) {
								(p_tmp->y)++;
								p_tmp->e += dx;
							}

						}
						//Si la hauteur entre les deux points et plus grande que la longueur entre les deux points
						else {
							(p_tmp->y)++;
							p_tmp->e -= dx;

							if(p_tmp->e <= 0) {
								(p_tmp->x)++;
								p_tmp->e += dy;
							}

						}
					}
					else {
				
						if(dx >= -dy){
							(p_tmp->x)++;
							p_tmp->e += dy;

							if(p_tmp->e <= 0) {
								(p_tmp->y)--;
								p_tmp->e += dx;
							}

						}
						else {
							(p_tmp->y)--;
							p_tmp->e += dx;

							if(p_tmp->e > 0) {
								(p_tmp->x)++;
								p_tmp->e += dy;
							}
						}

					}
				}
				// dx < 0
				else {

					if(dy > 0) {

						if(-dx >= dy) {

							(p_tmp->x)--;
							p_tmp->e += dy;

							if(p_tmp->e >= 0) {
								(p_tmp->y)++;
								p_tmp->e += dx;
							}

						}
						else {
							(p_tmp->y)++;
							p_tmp->e += dx;

							if(p_tmp->e <= 0) {
								(p_tmp->x)--;
								p_tmp->e += dy;
							}

						}
					}
					else {


						if(dx <= dy) {

							(p_tmp->x)--;
							p_tmp->e -= dy;

							if(p_tmp->e >= 0) {
								(p_tmp->y)--;
								p_tmp->e += dx;
							}

						}
						else {
							(p_tmp->y)--;
							p_tmp->e -= dy;

							if(p_tmp->e >= 0) {
								(p_tmp->x)--;
								p_tmp->e += dy;
							}

						}

					}

				}

			}

			//S'il est arrivé au noeud suivant change les noeuds précédent et suivant
			if(p_tmp->x == p_tmp->node_next->x && p_tmp->y == p_tmp->node_next->y) {

				p_tmp->node_prev = p_tmp->node_next;
				p_tmp->node_next = p_tmp->node_next->p_next;

				if(p_tmp->node_prev->x == p_tmp->node_next->x || p_tmp->node_prev->y == p_tmp->node_next->y)
					p_tmp->e = 0;
				else {

					int dx = (p_tmp->node_next->x) - (p_tmp->node_prev->x);
					int dy = (p_tmp->node_next->y) - (p_tmp->node_prev->y);	

					if(dx > 0) {

						if(dy > 0) {

							if(dx >= dy)
								p_tmp->e = (p_tmp->node_next->x) - (p_tmp->node_prev->x);
							else
								p_tmp->e = (p_tmp->node_next->y) - (p_tmp->node_prev->y);
						}
						else {

							if(dx >= -dy)
								p_tmp->e = (p_tmp->node_next->x) - (p_tmp->node_prev->x);
							else
								p_tmp->e = (p_tmp->node_next->y) - (p_tmp->node_prev->y);

						}

					}
					else {
						if(dy > 0) {

							if(-dx >= dy)
								p_tmp->e = (p_tmp->node_next->x) - (p_tmp->node_prev->x);
							else
								p_tmp->e = (p_tmp->node_next->y) - (p_tmp->node_prev->y);

						}
						else {

							if(dx <= dy)
								p_tmp->e = (p_tmp->node_next->x) - (p_tmp->node_prev->x);
							else
								p_tmp->e = (p_tmp->node_next->y) - (p_tmp->node_prev->y);

						}
				
					}		

				}

			}

			if(verificationEnd(p_tmp, p_tail) == 2)
				return 2;

			p_tmp = p_tmp->p_next;

		}

	}
	else {
		printf("Cette liste de monstres n'existe pas");
		return 0;
	}
	return 1;
}

/************* Vérification si le monstre arrive au point d'arrivé *************/
/* Vérifie si le monstre est arrivé : vérifie si les coordonnées du monstre correspond au point 	*
*  d'arrivé. Prend en paramètre un monstre et la liste de noeud. Retourne 2 s'il est arrivé, 0 sinon.	*/

int verificationEnd(Monster* monster, Node* p_tail) {
	
	if(monster != NULL) {

		if(p_tail != NULL) {

			if(monster->x == p_tail->x && monster->y == p_tail->y)
				return 2;

		}
		else {
			printf("Erreur : il y a un problème avec le dernier noeud\n");
			return 0;
		}

	}
	else {
		printf("Erreur : il y a un problème avec le monstre\n");
		return 0;
	}

	return 0;
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
			
				if(p_lmonster->p_tail) {
					//Lien du dernier monstre vers le monstre suivant est NULL
					p_lmonster->p_tail->p_next = NULL;
				}
				
			}
	
			//Si c'est le premier monstre de la liste
			else if (p_courant->p_prev == NULL) {
				//Pointe la tête de la liste vers le monstre suivant
				p_lmonster->p_head = p_courant->p_next;

				if(p_lmonster->p_head != NULL) {
					//Le lien vers du deuxième monstre vers le monstre précédent est NULL
			 		p_lmonster->p_head->p_prev = NULL;
				}
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
		else {
			printf("Ce monstre n'existe pas");
			return NULL;
		}
	}
	else {
		printf("Cette liste de monstres n'existe pas");
		return NULL;
	}

	// on retourne notre nouvelle liste
	return p_lmonster; 
}

