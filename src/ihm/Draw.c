#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Appel de la structures
#include "element/Monster.h"
#include "element/Tower.h"
#include "element/Shot.h"
#include "ihm/Node.h"
#include "ihm/Draw.h"

#define pi 3.14

/*********************** Dessiner la map ***********************/
/* Dessine la map. Prend en paramètre une texture.	*/

int drawMap (GLuint* texture) {

	if(texture != NULL) {

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *texture);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(800, 660);

			glTexCoord2f(1, 0);
			glVertex2f(800, 60);

			glTexCoord2f(0, 0);
			glVertex2f(200, 60);

			glTexCoord2f(0, 1);
			glVertex2f(200, 660);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);
	}
	else {
		printf("Erreur la texture de la map n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner le menu ***********************/
/* Dessine le menu. Prend en paramètre la texture pour le menu. Retourne 0 en cas d'erreur 1 sinon.	*/

int drawMenu (GLuint* menu1, GLuint* menu2, GLuint* menuNone, GLuint* fondMenu, GLuint* spriteButton, int play) {
	if(menu1 != NULL && menu2 != NULL) {

		
		/** Bouton fermer **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(0.2, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(790, 45);

			glTexCoord2f(0.2, 0);
			glVertex2f(790, 15);

			glTexCoord2f(0, 0);
			glVertex2f(760, 15);

			glTexCoord2f(0, 1);
			glVertex2f(760, 45);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);


		if(play == 0) {

			/** Bouton pause **/

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.6, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(755, 45);

				glTexCoord2f(0.6, 0);
				glVertex2f(755, 15);

				glTexCoord2f(0.4, 0);
				glVertex2f(725, 15);

				glTexCoord2f(0.4, 1);
				glVertex2f(725, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}
		else {

			/** Bouton play **/

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.4, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(755, 45);

				glTexCoord2f(0.4, 0);
				glVertex2f(755, 15);

				glTexCoord2f(0.2, 0);
				glVertex2f(725, 15);

				glTexCoord2f(0.2, 1);
				glVertex2f(725, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}

		/** Bouton avance rapide **/
		if(play == 2) {
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(720, 45);

				glTexCoord2f(1, 0);
				glVertex2f(720, 15);

				glTexCoord2f(0.8, 0);
				glVertex2f(690, 15);

				glTexCoord2f(0.8, 1);
				glVertex2f(690, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);
		}
		else {
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.8, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(720, 45);

				glTexCoord2f(0.8, 0);
				glVertex2f(720, 15);

				glTexCoord2f(0.6, 0);
				glVertex2f(690, 15);

				glTexCoord2f(0.6, 1);
				glVertex2f(690, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);
		}

		/** Fond du menu de gauche **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D); 
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *fondMenu);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(200, 660);

			glTexCoord2f(1, 0);
			glVertex2f(200, 60);

			glTexCoord2f(0, 0);
			glVertex2f(0, 60);

			glTexCoord2f(0, 1);
			glVertex2f(0, 660);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *menu2);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(190, 120);

			glTexCoord2f(1, 0);
			glVertex2f(190, 70);

			glTexCoord2f(0, 0);
			glVertex2f(10, 70);

			glTexCoord2f(0, 1);
			glVertex2f(10, 120);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);


		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *menu1);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(190, 175);

			glTexCoord2f(1, 0);
			glVertex2f(190, 125);

			glTexCoord2f(0, 0);
			glVertex2f(10, 125);

			glTexCoord2f(0, 1);
			glVertex2f(10, 175);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *menuNone);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(190, 230);

			glTexCoord2f(1, 0);
			glVertex2f(190, 180);

			glTexCoord2f(0, 0);
			glVertex2f(10, 180);

			glTexCoord2f(0, 1);
			glVertex2f(10, 230);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

	}
	else {
		printf("Erreur il y un problème avec les textures.\n");
		return 0;
	}

	return 1;
}

/*********************** Dessiner les tours ***********************/
/* Dessine les tours. Prend en paramètre la texture de la tour, la texture des shots, la liste de tours,	*
*  la liste de monstres, le monstre target et les variables xt1, xt2, testMouse et k. Retourne k.		*/

int drawTower (GLuint* monster, GLuint* shot, LTower* p_ltower, LMonster* p_lmonster, Monster* target, float xt1, float xt2, int testMouse, int k) {

	if(monster != NULL && shot != NULL && p_ltower != NULL && p_lmonster != NULL) {

		//Création d'un pointeur tour temporaire pour parcourir la liste de tours
		Tower *p_temp = p_ltower->p_tail;

			//Parcours la liste de tours
			while(p_temp != NULL){

				glPushMatrix();
				glTranslatef(p_temp->x,p_temp->y,0.0);
				//if(testMouse == 1)
					drawDisque(p_temp->range);
				glPopMatrix();

				glPushMatrix();
				//Active le texturage 2D
				glEnable(GL_TEXTURE_2D);
				//appel de la texture
				glBindTexture(GL_TEXTURE_2D, *monster);

					int xm1, xm2, ym1, ym2;
					xm1 = p_temp->x + 20;
					xm2 = p_temp->x - 20;
					ym1 = p_temp->y + 20;
					ym2 = p_temp->y - 20;

					glBegin(GL_QUADS);
					//coordonée de la texture
					glTexCoord2f(xt2, 0.625);
					//Cordonnée du quadrilatère 
					glVertex2f(xm1, ym1);

					glTexCoord2f(xt2, 0.5);
					glVertex2f(xm1, ym2);

					glTexCoord2f(xt1, 0.5);
					glVertex2f(xm2, ym2);

					glTexCoord2f(xt1, 0.625);
					glVertex2f(xm2, ym1);

					glEnd();

				//Déblinder la texture
				glBindTexture(GL_TEXTURE_2D, 0);
				//Désactive le texturage 2D
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();

				if(testMouse == 0) {
					if(k%20 == 0) {
						target = inSight (p_lmonster, p_temp);
						if(target != NULL) {
							addShot(p_temp->p_lshot, target, p_temp->x, p_temp->y);
							k=0;
						}
					}
					k++;
				}

				if(p_temp->p_lshot->p_head != NULL) {

					moveShot(p_temp->p_lshot);
					collisionMissile(p_temp->p_lshot, p_lmonster);
					drawShot (shot, p_temp->p_lshot);
				
				}

				p_temp = p_temp->p_prev;
			}
		}
		else
			printf("Erreur un des élements n'est pas alloué\n");

		return k;
}

/*********************** Dessiner les missiles ***********************/
/* Dessine les missiles. Prend en paramètre la texture du missile, et la liste de missiles. Retourne 0 en cas	*
*  d'erreur, 1 sinon.												*/

int drawShot (GLuint* shot, LShot* p_lshot) {

	if(shot != NULL && p_lshot != NULL) {

		Shot* tmp_shot = p_lshot->p_head;

		while(tmp_shot != NULL) {

		
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *shot);

				int xm1, xm2, ym1, ym2;
				xm1 = tmp_shot->x + 5;
				xm2 = tmp_shot->x - 5;
				ym1 = tmp_shot->y + 5;
				ym2 = tmp_shot->y - 5;

				glPushMatrix();
					glBegin(GL_QUADS);
					//coordonée de la texture
					glTexCoord2f(1, 0);
					//Cordonnée du quadrilatère 
					glVertex2f(xm1, ym1);

					glTexCoord2f(1, 1);
					glVertex2f(xm1, ym2);

					glTexCoord2f(0, 1);
					glVertex2f(xm2, ym2);

					glTexCoord2f(0, 0);
					glVertex2f(xm2, ym1);

					glEnd();
				glPopMatrix();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			tmp_shot = tmp_shot->p_next;
		}
	}
	else {
		printf("Erreur : al texture du shot ou la liste de shot n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner les monstres ***********************/
/* Dessine les monstres. Prend en paramètre la texture des monstres, la liste de monstre, les variables x1 et 	*
*  x2. Retourne 0 en cas d'erreur et 1 sinon.									*/

int drawMonster(GLuint* monster, LMonster* p_lmonster, Node* p_tail, float x1, float x2) {

	if(monster != NULL && p_lmonster != NULL) {
	
		//Création d'un monstre temporaire pour parcourir la liste de monstres
		Monster *p_tmp = p_lmonster->p_tail;

		//Parcours la liste de monstres
		while(p_tmp != NULL){
		
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *monster);

				int xm1, xm2, ym1, ym2;
				xm1 = p_tmp->x + 20;
				xm2 = p_tmp->x - 20;
				ym1 = p_tmp->y + 20;
				ym2 = p_tmp->y - 20;
		
		
				glPushMatrix();
					glBegin(GL_QUADS);
					//coordonée de la texture
					glTexCoord2f(x2, 0.375);
					//Cordonnée du quadrilatère 
					glVertex2f(xm1, ym1);

					glTexCoord2f(x2, 0.25);
					glVertex2f(xm1, ym2);

					glTexCoord2f(x1, 0.25);
					glVertex2f(xm2, ym2);

					glTexCoord2f(x1, 0.375);
					glVertex2f(xm2, ym1);

					glEnd();
				glPopMatrix();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			p_tmp = p_tmp->p_prev;
		}
		//Afficher les pv
		drawPVMonster(p_lmonster);
		//Bouger le monstre
		if(moveMonster(p_lmonster, p_tail) == 2)
			return 2;
	}
	else {
		printf("Erreur : la texture du monstre ou la liste de monstre n'existe pas\n");
		return 0;
	}

	return 1;
}

/************* Dessiner la barre de vie du monstre *************/
/* Dessine la barre de vie du monstre. Descend en fonction du nombre de vie restant et change de 	*
*  couleur. Prend en paramètre la liste de monstres. Retourne 0 en cas d'erreur et 1 sinon.		*/
int drawPVMonster(LMonster* p_lmonster) {

	//On vérifie si notre liste a été allouée
	if(p_lmonster != NULL) {
	
		float pourcentagePV, x;

		//Création d'un monstre temporaire pour parcourir la liste de monstres
		Monster *p_tmp = p_lmonster->p_head;

		//Parcours la liste de monstres
		while(p_tmp != NULL){

			pourcentagePV = p_tmp->pv / p_tmp->pvMax;
			x = pourcentagePV * 40;

			glPushMatrix();
				int xm1, xm2, ym1, ym2;
				
				xm1 = p_tmp->x - 20 + x;
				xm2 = p_tmp->x - 20;
				ym1 = p_tmp->y - 22;
				ym2 = p_tmp->y - 26;

				if(pourcentagePV <= 0.1)
					glColor3ub(255,0,0);
				else if(pourcentagePV <= 0.3)
					glColor3ub(255,96,0);
				else if(pourcentagePV <= 0.5)
					glColor3ub(255,150,0);
				else if(pourcentagePV <= 0.7)
					glColor3ub(255,240,0);
				else
					glColor3ub(27,101,10);

				glBegin(GL_QUADS);
					glVertex2f(xm1, ym1);
					glVertex2f(xm1, ym2);
					glVertex2f(xm2, ym2);
					glVertex2f(xm2, ym1);
				glEnd();
				glColor3ub(255,255,255);

			glPopMatrix();

			p_tmp = p_tmp->p_next;
		}
	}
	else {
		printf("Cette liste de monstres n'existe pas");
		return 0;
	}

	return 1;

}


/************* Dessiner un cercle en fonction de son rayon plein *************/
/* Dessine un cercle plein. Prend en paramètre le rayon du cercle.		*/

void drawDisque(float rayon) {
	
	int i, j = 100;
	float angle, x1, y1;
	
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(0, 0);

	for(i = 0; i < j+2; i++) {
		angle = (2*pi*i)/j;
		x1 = rayon*(cos(angle));
		y1 = rayon*(sin(angle));
		glVertex2f(x1,y1);
	}

	glEnd();

}

/************* Dessiner un cercle en fonction de son rayon vide *************/
/* Dessine un cercle vide. Prend en paramètre le rayon du cercle.		*/

void drawCercle(float rayon) {
	
	int i, j = 100;
	float angle, x1, y1;
	
	glBegin(GL_LINE_STRIP);

	for(i = 0; i < j+2; i++) {
		angle = (2*pi*i)/j;
		x1 = rayon*(cos(angle));
		y1 = rayon*(sin(angle));
		glVertex2f(x1,y1);
	}

	glEnd();

}

/******************** Dessiner un rectangle / carré plein ********************/
/* Dessine un carré ou rectangle plein. Prend en paramètre les coordonées des deux points opposés	*/

void drawRectangle (int x1, int y1, int x2, int y2) {

	glBegin(GL_QUADS);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
}

/******************** Dessiner un rectangle / carré vide ********************/
/* Dessine un carré ou rectangle vide. Prend en paramètre les coordonées des deux points opposés	*/

void drawRectangleLine (int x1, int y1, int x2, int y2) {

	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
}


/******************** Ecrire du texte ********************/
/* Ecrire du texte. Prend en paramamètre sa position et la chaine de caractère	*/

void writeString(int x, int y,  char* s) {

		char* c;
		
		// Positionne le premier caractère de la chaîne
		glRasterPos2f(x, y);
		for (c = s; *c != '\0'; c++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Affiche chaque caractère de la chaîne

		// Réinitialise la position du premier caractère de la chaîne
		glRasterPos2f(0, 0);
}


