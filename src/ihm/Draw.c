#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "element/Monster.h"
#include "element/Tower.h"
#include "element/Shot.h"

#include "ihm/Node.h"
#include "ihm/Draw.h"
#include "ihm/Interface.h"
#include "file/Texture.h"
#include "file/Map.h"

#define pi 3.14

/*********************** Dessiner le menu des map ***********************/
/* Dessine le menu des map. Prend en paramètre les textures.	*/

int drawMenuMap (GLuint* texture, GLuint* bt_texture, int nbTexture) {

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
			glVertex2f(800, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 660);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		if(nbTexture == 0) {

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *bt_texture);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.5, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(492, 121);

				glTexCoord2f(0.5, 0);
				glVertex2f(492, 68);

				glTexCoord2f(0, 0);
				glVertex2f(300, 68);

				glTexCoord2f(0, 1);
				glVertex2f(300, 121);

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
			glBindTexture(GL_TEXTURE_2D, *bt_texture);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(492, 121);

				glTexCoord2f(1, 0);
				glVertex2f(492, 68);

				glTexCoord2f(0.5, 0);
				glVertex2f(300, 68);

				glTexCoord2f(0.5, 1);
				glVertex2f(300, 121);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}

	}
	else {
		fprintf(stderr, "Erreur la texture de la map n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner le menu principale ***********************/
/* Dessine le menu principale. Prend en paramètre les textures.	*/

int drawMenuPrincipale (GLuint* texture, GLuint* spriteButton) {

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
			glVertex2f(800, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 660);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		/** Bouton jouer **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 0.25);
			//Cordonnée du quadrilatère 
			glVertex2f(514, 352);

			glTexCoord2f(1, 0);
			glVertex2f(514, 296);

			glTexCoord2f(0, 0);
			glVertex2f(272, 296);

			glTexCoord2f(0, 0.25);
			glVertex2f(272, 352);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		/** Bouton aide **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 0.5);
			//Cordonnée du quadrilatère 
			glVertex2f(514, 421);

			glTexCoord2f(1, 0.25);
			glVertex2f(514, 364);

			glTexCoord2f(0, 0.25);
			glVertex2f(272, 364);

			glTexCoord2f(0, 0.5);
			glVertex2f(272, 421);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		/** Bouton changer de carte **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 0.75);
			//Cordonnée du quadrilatère 
			glVertex2f(514, 490);

			glTexCoord2f(1, 0.5);
			glVertex2f(514, 432);

			glTexCoord2f(0, 0.5);
			glVertex2f(272, 432);

			glTexCoord2f(0, 0.75);
			glVertex2f(272, 490);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

	}
	else {
		fprintf(stderr, "Erreur la texture de la map n'existe pas\n");
		return 0;
	}

	return 1;

}

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
		fprintf(stderr, "Erreur la texture de la map n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner l'aide ***********************/
/* Dessine la map. Prend en paramètre une texture.	*/

int drawHelp (GLuint* texture, GLuint* spriteButton, GLuint* spriteButtonMenu, int nbMenu) {

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
			glVertex2f(800, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 660);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		if(nbMenu == 3) {

			/** Bouton fermer **/

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
				glVertex2f(790, 45);

				glTexCoord2f(1, 0);
				glVertex2f(790, 15);

				glTexCoord2f(0.875, 0);
				glVertex2f(760, 15);

				glTexCoord2f(0.875, 1);
				glVertex2f(760, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);
		}
		else {

			/** Bouton menu **/

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButtonMenu);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(310, 627);

				glTexCoord2f(1, 0.75);
				glVertex2f(310, 570);

				glTexCoord2f(0, 0.75);
				glVertex2f(68, 570);

				glTexCoord2f(0, 1);
				glVertex2f(68, 627);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			/** Bouton jouer **/

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButtonMenu);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(1, 0.25);
				//Cordonnée du quadrilatère 
				glVertex2f(732, 627);

				glTexCoord2f(1, 0);
				glVertex2f(732, 570);

				glTexCoord2f(0, 0);
				glVertex2f(490, 570);

				glTexCoord2f(0, 0.25);
				glVertex2f(490, 627);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}

	}
	else {
		fprintf(stderr, "Erreur la texture de la map n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner du chemin et des noeuds ***********************/
/* Dessine du chemin et des noeuds. Prend en paramètre la liste de noeud et la map.	*
*  Retourne 0 en cas d'erreur et 1 sinon.						*/

int drawRoad (Map* map) {

	if(map != NULL) {

		Node* p_tmp = map->list_node->p_head;

		while(p_tmp->p_next != NULL) {
		
			glBegin(GL_LINES);
				glColor3ub(29,168,194);
				glVertex2d(p_tmp->x, p_tmp->y);
				glVertex2d(p_tmp->p_next->x, p_tmp->p_next->y);
			glEnd();

			glPushMatrix();
				glColor3ub((map->node).r,(map->node).g,(map->node).b);
				glTranslatef(p_tmp->x,p_tmp->y, 0.0);
				drawDisque(5);
			glPopMatrix();

			glColor3ub(255,255,255);

			p_tmp = p_tmp->p_next;					

		}
	}
	else {
		fprintf(stderr, "Erreur la carte n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner le menu haut ***********************/
/* Dessine le menu. Prend en paramètre la texture pour le menu et la variable play. Retourne 0 en cas d'erreur 1 sinon.	*/

int drawMenuUp (GLuint* spriteButton, GLuint* fondMenuUp, int play) {

	if(spriteButton != NULL) {

		/** Fonc menu **/
		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *fondMenuUp);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(800, 60);

			glTexCoord2f(1, 0);
			glVertex2f(800, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 60);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);
		
		
		/** Bouton fermer **/

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
			glVertex2f(790, 45);

			glTexCoord2f(1, 0);
			glVertex2f(790, 15);

			glTexCoord2f(0.875, 0);
			glVertex2f(760, 15);

			glTexCoord2f(0.875, 1);
			glVertex2f(760, 45);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);


		/** Bouton aide **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(0.875, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(755, 45);

			glTexCoord2f(0.875, 0);
			glVertex2f(755, 15);

			glTexCoord2f(0.75, 0);
			glVertex2f(725, 15);

			glTexCoord2f(0.75, 1);
			glVertex2f(725, 45);

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
				glTexCoord2f(0.625, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(720, 45);

				glTexCoord2f(0.625, 0);
				glVertex2f(720, 15);

				glTexCoord2f(0.5, 0);
				glVertex2f(690, 15);

				glTexCoord2f(0.5, 1);
				glVertex2f(690, 45);

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
				glTexCoord2f(0.5, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(720, 45);

				glTexCoord2f(0.5, 0);
				glVertex2f(720, 15);

				glTexCoord2f(0.375, 0);
				glVertex2f(690, 15);

				glTexCoord2f(0.375, 1);
				glVertex2f(690, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}

		/** Bouton avance rapide **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(0.75, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(685, 45);

			glTexCoord2f(0.75, 0);
			glVertex2f(685, 15);

			glTexCoord2f(0.625, 0);
			glVertex2f(655, 15);

			glTexCoord2f(0.625, 1);
			glVertex2f(655, 45);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

	}
	else {
		fprintf(stderr, "Erreur il y un problème avec les textures.\n");
		return 0;
	}

	return 1;
}

/*********************** Dessiner le menu left ***********************/
/* Dessine le menu. Prend en paramètre les textures pour le menu et un pointeur vers l'interface.	*
*  Retourne 0 en cas d'erreur 1 sinon.									*/

int drawMenuLeft (GLuint* spriteMenu, GLuint* fondMenu, Interface* interface) {

	if(spriteMenu != NULL && fondMenu != NULL) {
		
		/** Fond du menu de gauche **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D); 
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *fondMenu);

			glBegin(GL_QUADS);
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

		/*** Première tour ***/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteMenu);

			if(interface->money >= 50)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			glBegin(GL_QUADS);
			//coordonée de la texture
			glTexCoord2f(1, 0.142);
			//Cordonnée du quadrilatère 
			glVertex2f(190, 120);

			glTexCoord2f(1, 0);
			glVertex2f(190, 70);

			glTexCoord2f(0, 0);
			glVertex2f(10, 70);

			glTexCoord2f(0, 0.142);
			glVertex2f(10, 120);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);


		/*** Deuxième tour ***/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteMenu);

			if(interface->money >= 100)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);


			glBegin(GL_QUADS);
			//coordonée de la texture
			glTexCoord2f(1, 0.285);
			//Cordonnée du quadrilatère 
			glVertex2f(190, 175);

			glTexCoord2f(1, 0.142);
			glVertex2f(190, 125);

			glTexCoord2f(0, 0.142);
			glVertex2f(10, 125);

			glTexCoord2f(0, 0.285);
			glVertex2f(10, 175);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		if(interface->lvl >= 3) {

			if(interface->money >= 200)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteMenu);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 0.428);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 230);

				glTexCoord2f(1, 0.285);
				glVertex2f(190, 180);

				glTexCoord2f(0, 0.285);
				glVertex2f(10, 180);

				glTexCoord2f(0, 0.428);
				glVertex2f(10, 230);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}
		else {

			/*** Aucune tour ***/

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteMenu);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(1, 0.714);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 230);

				glTexCoord2f(1, 0.571);
				glVertex2f(190, 180);

				glTexCoord2f(0, 0.571);
				glVertex2f(10, 180);

				glTexCoord2f(0, 0.714);
				glVertex2f(10, 230);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);
		}

		if(interface->lvl >= 5) {

			if(interface->money >= 300)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteMenu);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 0.571);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 285);

				glTexCoord2f(1, 0.428);
				glVertex2f(190, 235);

				glTexCoord2f(0, 0.428);
				glVertex2f(10, 235);

				glTexCoord2f(0, 0.571);
				glVertex2f(10, 285);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}
		else {

			/*** Aucune tour ***/

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteMenu);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(1, 0.714);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 285);

				glTexCoord2f(1, 0.571);
				glVertex2f(190, 235);

				glTexCoord2f(0, 0.571);
				glVertex2f(10, 235);

				glTexCoord2f(0, 0.714);
				glVertex2f(10, 285);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);
		}

	}
	else {
		fprintf(stderr, "Erreur il y un problème avec les textures.\n");
		return 0;
	}

	return 1;
}

/*********************** Dessiner l'interface (score, argent, vie, nb de monstre tués ***********************/
/* Dessine l'interface. Prend en paramètre un pointeur vers la texture et un pointeur vers l'interface.	*
*  Retourne 0 en cas d'erreur, 1 sinon. 								*/

int drawInterface (GLuint* spriteButton, Interface* interface) {

	if(interface != NULL) {

		//Alloue de la mémoire pour une chaine de caractère
		char* machaine = malloc(20*sizeof(char));

		//Si la chaine de caracteres à bien été alloué
		if(machaine != NULL) {

			/**** Niveau ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",interface->lvl);

			writeString(40, 35,  "Niveau : ");
			//Affiche la chaine de caractère
			writeString(110, 35,  machaine);

			/**** Money ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",interface->money);
			//Affiche la chaine de caractère
			writeString(180, 35,  machaine);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.125, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(140, 45);

				glTexCoord2f(0.125, 0);
				glVertex2f(140, 15);

				glTexCoord2f(0, 0);
				glVertex2f(170, 15);

				glTexCoord2f(0, 1);
				glVertex2f(170, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			/**** Score ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",interface->score);

			writeString(280, 35,  "Score ");
			//Affiche la chaine de caractère
			writeString(335, 35,  machaine);

			/**** nombre de monstre ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",interface->nbMonster);

			//Affiche la chaine de caractère
			writeString(470, 35,  machaine);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.25, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(430, 45);

				glTexCoord2f(0.25, 0);
				glVertex2f(430, 15);

				glTexCoord2f(0.125, 0);
				glVertex2f(460, 15);

				glTexCoord2f(0.125, 1);
				glVertex2f(460, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);


			/**** nombre de vie ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",interface->life);
			//Affiche la chaine de caractère
			writeString(600, 35,  machaine);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteButton);

				glBegin(GL_QUADS);
				//couleur neutre
				glColor3ub(255,255,255);
				//coordonée de la texture
				glTexCoord2f(0.375, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(560, 45);

				glTexCoord2f(0.375, 0);
				glVertex2f(560, 15);

				glTexCoord2f(0.25, 0);
				glVertex2f(590, 15);

				glTexCoord2f(0.25, 1);
				glVertex2f(590, 45);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}
		else {
			fprintf(stderr, "probleme d'allocation memoire pour la chaine de caractere\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Il y a un problème avec l'interface\n");
		return 0;
	}	

	return 1;

}

/*********************** Dessiner les propriétés des tours ***********************/
/* Dessine les propriétés des tours. Prend en paramètre un pointeur vers la tour courante 		*
*  Retourne 0 en cas d'erreur, 1 sinon. 								*/

int drawProprieteTower (GLuint* tower, GLuint* spriteMenu, GLuint* btPlus, Tower* p_courant, Interface* interface) {

	if(p_courant != NULL) {

		int towerNumber = 0;
		//Choisir le bon monstre dans le sprite
		if(strcmp("H", p_courant->type_tower) == 0) 
			towerNumber = 0;
		else if(strcmp("M", p_courant->type_tower) == 0) 
			towerNumber = 1;
		else if(strcmp("L", p_courant->type_tower) == 0) 
			towerNumber = 3;
		else if(strcmp("R", p_courant->type_tower) == 0) 
			towerNumber = 2;

		float x1 = 0, x2 = 1, y1 = (towerNumber * (1.0/4.0)) + 0;
		float y2 = (towerNumber * (1.0/4.0)) + 0.25;

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *tower);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(x2, y1);
			//Cordonnée du quadrilatère 
			glVertex2f(20, 300);

			glTexCoord2f(x2, y2);
			glVertex2f(20, 340);

			glTexCoord2f(x1, y2);
			glVertex2f(60, 340);

			glTexCoord2f(x1, y1);
			glVertex2f(60, 300);


			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);


		//Alloue de la mémoire pour une chaine de caractère
		char* machaine = malloc(20*sizeof(char));

		//Si la chaine de caracteres à bien été alloué
		if(machaine != NULL) {

			int money = 0;

			/**** Niveau ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->lvl);

			writeString(20, 365,  "Niveau : ");
			//Affiche la chaine de caractère
			writeString(120, 365,  machaine);

			/**** Cadence ****/
			glColor4f(255,255,255, 1);
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->rate);

			writeString(20, 390,  "Cadence : ");
			//Affiche la chaine de caractère
			writeString(120, 390,  machaine);

			//Si c'est une tour hybride
			if(strcmp("H", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 20;
			}
			//Si c'est une tour mitrailette 
			else if(strcmp("M", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 40;
			}
			//Si c'est une tour laser 
			else if(strcmp("R", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 40;
			}
			//Si c'est une tour rocket 
			else if(strcmp("L", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 50;
			}

			if(interface->money >= money)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *btPlus);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 395);

				glTexCoord2f(1, 0);
				glVertex2f(190, 372);

				glTexCoord2f(0, 0);
				glVertex2f(165, 372);

				glTexCoord2f(0, 1);
				glVertex2f(165, 395);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			/**** Périmètre d'action ****/
			glColor4f(255,255,255, 1);
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->range);

			writeString(20, 415,  "Range : ");
			//Affiche la chaine de caractère
			writeString(120, 415,  machaine);

			//Si c'est une tour hybride
			if(strcmp("H", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 20;
			}
			//Si c'est une tour mitrailette 
			else if(strcmp("M", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 50;
			}
			//Si c'est une tour laser 
			else if(strcmp("R", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 30;
			}
			//Si c'est une tour rocket 
			else if(strcmp("L", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 50;
			}

			if(interface->money >= money)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *btPlus);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 420);

				glTexCoord2f(1, 0);
				glVertex2f(190, 397);

				glTexCoord2f(0, 0);
				glVertex2f(165, 397);

				glTexCoord2f(0, 1);
				glVertex2f(165, 420);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			/**** puissance ****/

			glColor4f(255,255,255, 1);
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->power);

			writeString(20, 440,  "Puissance : ");
			//Affiche la chaine de caractère
			writeString(120, 440,  machaine);

			//Si c'est une tour hybride
			if(strcmp("H", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 20;
			}
			//Si c'est une tour mitrailette 
			else if(strcmp("M", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 30;
			}
			//Si c'est une tour laser 
			else if(strcmp("R", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 20;
			}
			//Si c'est une tour rocket 
			else if(strcmp("L", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 30;
			}

			if(interface->money >= money)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *btPlus);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 445);

				glTexCoord2f(1, 0);
				glVertex2f(190, 422);

				glTexCoord2f(0, 0);
				glVertex2f(165, 422);

				glTexCoord2f(0, 1);
				glVertex2f(165, 445);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);


			/**** type de la tour ****/
			glColor4f(255,255,255, 1);
			writeString(20, 465,  "Type : ");
			//Affiche la chaine de caractère
			writeString(120, 465,  p_courant->type_tower);

			
			/*** Bouton supprimer ****/
			glColor4f(255,255,255, 1);			

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteMenu);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 0.857);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 540);

				glTexCoord2f(1, 0.714);
				glVertex2f(190, 490);

				glTexCoord2f(0, 0.714);
				glVertex2f(10, 490);

				glTexCoord2f(0, 0.857);
				glVertex2f(10, 540);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);


			//Si c'est une tour hybride
			if(strcmp("H", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 20;
			}
			//Si c'est une tour mitrailette 
			else if(strcmp("M", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 30;
			}
			//Si c'est une tour laser 
			else if(strcmp("R", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 20;
			}
			//Si c'est une tour rocket 
			else if(strcmp("L", p_courant->type_tower) == 0) {
				money = (p_courant->lvl) * 30;
			}

			if(interface->money >= money)
				glColor4f(255,255,255, 1);
			else 
				glColor4f(255,255,255, 0.5);

			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *spriteMenu);

				glBegin(GL_QUADS);
				//coordonée de la texture
				glTexCoord2f(1, 1);
				//Cordonnée du quadrilatère 
				glVertex2f(190, 595);

				glTexCoord2f(1, 0.857);
				glVertex2f(190, 545);

				glTexCoord2f(0, 0.857);
				glVertex2f(10, 545);

				glTexCoord2f(0, 1);
				glVertex2f(10, 595);

				glEnd();

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

		}
		else {
			fprintf(stderr, "probleme d'allocation memoire pour la chaine de caractere\n");
			return 0;
		}	
	}

	return 1;

}

/*********************** Dessiner les propriétés des monstres ***********************/
/* Dessine les propriétés des tours. Prend en paramètre un pointeur vers le monstre courant 		*
*  Retourne 0 en cas d'erreur, 1 sinon. 								*/

int drawProprieteMonster (GLuint* monster, Monster* p_courant) {

	if(p_courant != NULL) {

		int monsterNumber = 0;
			//Choisir le bon monstre dans le sprite
			if(strcmp("C1", p_courant->type) == 0) 
				monsterNumber = 0;
			else if(strcmp("C2", p_courant->type) == 0) 
				monsterNumber = 1;
			else if(strcmp("P", p_courant->type) == 0) 
				monsterNumber = 2;
			else if(strcmp("F", p_courant->type) == 0) 
				monsterNumber = 3;

		float x1 = (monsterNumber * (3.0/12.0)) + (2.0/12.0), x2 = (monsterNumber * (3.0/12.0)) + (3.0/12.0), y1 = 0, y2 = 0.25;

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *monster);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(x2, y1);
			//Cordonnée du quadrilatère 
			glVertex2f(20, 300);

			glTexCoord2f(x2, y2);
			glVertex2f(20, 340);

			glTexCoord2f(x1, y2);
			glVertex2f(60, 340);

			glTexCoord2f(x1, y1);
			glVertex2f(60, 300);


			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		//Alloue de la mémoire pour une chaine de caractère
		char* machaine = malloc(20*sizeof(char));

		//Si la chaine de caracteres à bien été alloué
		if(machaine != NULL) {

			/**** points de vie ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->pv);

			writeString(20, 365,  "pv : ");
			//Affiche la chaine de caractère
			writeString(120, 365,  machaine);

			/**** vitesse ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->pace);

			writeString(20, 390,  "Vitesse : ");
			//Affiche la chaine de caractère
			writeString(120, 390,  machaine);

			/**** Resistant à tel type de tour ****/
			//Convertie un int en un string
			writeString(20, 415,  "Resistant a : ");
			//Affiche la chaine de caractère
			writeString(120, 415,  p_courant->type_tower);

			/**** Resistance ****/
			//Convertie un int en un string
			sprintf(machaine,"%d",p_courant->resistance);

			writeString(20, 440,  "Resistance : ");
			//Affiche la chaine de caractère
			writeString(120, 440,  machaine);


			/**** nombre de monstre ****/
			writeString(20, 465,  "Type : ");
			//Affiche la chaine de caractère
			writeString(120, 465,  p_courant->type);

		}
		else {
			fprintf(stderr, "probleme d'allocation memoire pour la chaine de caractere\n");
			return 0;
		}
	}

	return 1;

}


/*********************** Dessiner les tours ***********************/
/* Dessine les tours. Prend en paramètre la texture de la tour, la liste de tours, la liste de monstres, la tour courant	*
*  et les variables xt1, xt2, testMouse et propriete. Retourne 0 en cas d'erreur, 1 sinon. 					*/

int drawTower (GLuint* tower, LTower* p_ltower, LMonster* p_lmonster, Tower* p_courant, int testMouse, int testTower) {

	if(tower != NULL && p_ltower != NULL && p_lmonster != NULL) {

		//Création d'un pointeur tour temporaire pour parcourir la liste de tours
		Tower *p_temp = p_ltower->p_tail;

			//Parcours la liste de tours
			while(p_temp != NULL){

				if(testMouse == 1) {
					glPushMatrix();
					glTranslatef(p_temp->x,p_temp->y, 0.0);

						//Choisie la couleur
						if(p_temp == p_ltower->p_tail) {
							if(testTower == 1) 
								glColor4f(0,255,0, 0.2);
							else
								glColor4f(255,0,0, 0.2);
						}
						else
							glColor4f(255,255,255, 0.2);
						//Affiche le périmètre d'action
						drawDisque(p_temp->range);
				
					glPopMatrix();
				}

				if(p_courant != NULL && testMouse != 1) {
					if(p_courant == p_temp) {
						glPushMatrix();
							glTranslatef(p_temp->x,p_temp->y, 0.0);
							glColor4f(255,255,255, 0.2);
							drawDisque(p_temp->range);
						glPopMatrix();
					}
				}
				
				glColor3ub(255,255,255);
				glPushMatrix();
				//Active le texturage 2D
				glEnable(GL_TEXTURE_2D);
				//appel de la texture
				glBindTexture(GL_TEXTURE_2D, *tower);

					int xm1, xm2, ym1, ym2;
					xm1 = p_temp->x + 20;
					xm2 = p_temp->x - 20;
					ym1 = p_temp->y + 20;
					ym2 = p_temp->y - 20;

					int towerNumber = 0;
					//Choisir le bon monstre dans le sprite
					if(strcmp("H", p_temp->type_tower) == 0) 
						towerNumber = 0;
					else if(strcmp("M", p_temp->type_tower) == 0) 
						towerNumber = 1;
					else if(strcmp("L", p_temp->type_tower) == 0) 
						towerNumber = 3;
					else if(strcmp("R", p_temp->type_tower) == 0) 
						towerNumber = 2;

					float x1 = 0, x2 = 1, y1 = (towerNumber * (1.0/4.0)) + 0;
					float y2 = (towerNumber * (1.0/4.0)) + 0.25;

					glBegin(GL_QUADS);
					//coordonée de la texture
					glTexCoord2f(x2, y2);
					//Cordonnée du quadrilatère 
					glVertex2f(xm1, ym1);

					glTexCoord2f(x2, y1);
					glVertex2f(xm1, ym2);

					glTexCoord2f(x1, y1);
					glVertex2f(xm2, ym2);

					glTexCoord2f(x1, y2);
					glVertex2f(xm2, ym1);

					glEnd();

				//Déblinder la texture
				glBindTexture(GL_TEXTURE_2D, 0);
				//Désactive le texturage 2D
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();

				p_temp = p_temp->p_prev;
			}
		}
		else {
			fprintf(stderr, "Erreur un des élements n'est pas alloué\n");
			return 0;
		}

		return 1;
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
		fprintf(stderr, "Erreur : al texture du shot ou la liste de shot n'existe pas\n");
		return 0;
	}

	return 1;

}

/*********************** Dessiner les monstres ***********************/
/* Dessine les monstres. Prend en paramètre la texture des monstres, la liste de monstre, le dernier noeud. 	*
*  Retourne 0 en cas d'erreur et 1 sinon.									*/

int drawMonster(GLuint* monster, LMonster* p_lmonster, int play) {

	//Vérifie qu'il existe
	if(monster != NULL && p_lmonster != NULL) {
	
		//Création d'un pointeur monstre temporaire pour parcourir la liste de monstres
		Monster *p_tmp = p_lmonster->p_tail;

		//Parcours la liste de monstres
		while(p_tmp != NULL){

			int monsterNumber = 0;
			//Choisir le bon monstre dans le sprite
			if(strcmp("C1", p_tmp->type) == 0) 
				monsterNumber = 0;
			else if(strcmp("C2", p_tmp->type) == 0) 
				monsterNumber = 1;
			else if(strcmp("P", p_tmp->type) == 0) 
				monsterNumber = 2;
			else if(strcmp("F", p_tmp->type) == 0) 
				monsterNumber = 3;
			
			float xm1, xm2, ym1, ym2;
			xm1 = p_tmp->x + 20;
			xm2 = p_tmp->x - 20;
			ym1 = p_tmp->y + 20;
			ym2 = p_tmp->y - 20;

			float x1 = (monsterNumber * (3.0/12.0)), x2 = (monsterNumber * (3.0/12.0)), y1 = 0, y2 = 0;

			switch(p_tmp->sens) {
				//haut
				case 1 :
					y1 = 0.5;
					y2 = 0.75;
					break;
				//doite
				case 2 :
					y1 = 0.75;
					y2 = 1;
					break;
				//bas
				case 3 :
					y1 = 0;
					y2 = 0.25;
					break;
				//gauche
				case 4 :
					y1 = 0.25;
					y2 = 0.5;
					break;

			}

			switch(p_tmp->animation) {
				case 0 :
					x1 += 0;
					x2 += 0.083;
					//si ce n'est pas en pause
					if(play != 1) {
						p_tmp->animation ++;
					}
					break;
				case 1: 
					x1 += 0.083;
					x2 += 0.166;
					if(play != 1) {
						p_tmp->animation ++;
					}
					break;
				case 2 :
					x1 += 0.166;
					x2 += 0.25;
					if(play != 1) {
						p_tmp->animation = 0;
					}
					break;
			
			}
		
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, *monster);
		
				glPushMatrix();
					glBegin(GL_QUADS);
						//coordonée de la texture
						glTexCoord2f(x2, y2);
						//Cordonnée du quadrilatère 
						glVertex2f(xm1, ym1);

						glTexCoord2f(x2, y1);
						glVertex2f(xm1, ym2);

						glTexCoord2f(x1, y1);
						glVertex2f(xm2, ym2);

						glTexCoord2f(x1, y2);
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

		//Création d'un pointeur monstre temporaire pour parcourir la liste de monstres
		Monster *p_tmp = p_lmonster->p_head;

		//Parcours la liste de monstres
		while(p_tmp != NULL){

			//Calcule le pourcentage de pv restant
			pourcentagePV = (float)p_tmp->pv / (float)p_tmp->pvMax;
			x = pourcentagePV * 40;

			glPushMatrix();
				float xm1, xm2, ym1, ym2;
				
				//Calcule des coordonées du rectangle
				xm1 = p_tmp->x - 20 + x;
				xm2 = p_tmp->x - 20;
				ym1 = p_tmp->y - 22;
				ym2 = p_tmp->y - 26;

				//Choix de la couleur du rectangle en fonction du poucentage de pv restant
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

				//Dessine le rectangle
				glBegin(GL_QUADS);
					glVertex2f(xm1, ym1);
					glVertex2f(xm1, ym2);
					glVertex2f(xm2, ym2);
					glVertex2f(xm2, ym1);
				glEnd();
				
				//Remet la couleur neutre (blanc)
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

/******************** Dessiner GameOver / Win ********************/
/* Affiche Game Over ou Win. Prend en paramètre les textures.		*/

int drawGameOverWin(GLuint* texture, GLuint* spriteButton) {

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
			glVertex2f(800, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 660);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		/** Bouton jouer **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 0.25);
			//Cordonnée du quadrilatère 
			glVertex2f(514, 352);

			glTexCoord2f(1, 0);
			glVertex2f(514, 296);

			glTexCoord2f(0, 0);
			glVertex2f(272, 296);

			glTexCoord2f(0, 0.25);
			glVertex2f(272, 352);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		/** Bouton aide **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 0.5);
			//Cordonnée du quadrilatère 
			glVertex2f(514, 421);

			glTexCoord2f(1, 0.25);
			glVertex2f(514, 364);

			glTexCoord2f(0, 0.25);
			glVertex2f(272, 364);

			glTexCoord2f(0, 0.5);
			glVertex2f(272, 421);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		/** Bouton changer de carte **/

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *spriteButton);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 0.75);
			//Cordonnée du quadrilatère 
			glVertex2f(514, 490);

			glTexCoord2f(1, 0.5);
			glVertex2f(514, 432);

			glTexCoord2f(0, 0.5);
			glVertex2f(272, 432);

			glTexCoord2f(0, 0.75);
			glVertex2f(272, 490);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

	}
	else {
		fprintf(stderr, "Erreur la texture n'existe pas\n");
		return 0;
	}

	return 1;

}

/************ Faire apparaitre un monstre sur la map **************/
/* Fait apparaitre un monstre sur la map. Prend en paramètre un pointeur vers la liste de monstre, un pointeur vers 	*
*  l'interface, un pointeur vers la map, un int, un int (apparition) et int nombre de monstre. Retourne 0 en cas 	*
*  d'erreur et 1 sinon.													*/

int apparitionMonster(LMonster* p_lmonster, Interface* interface, Map* map, int apparition, int j, int* nb_monster) {

	if(p_lmonster != NULL) {

		if(interface != NULL) {

			int random;

			//ajoute un monstre à chaque fois que j est un muliple de 50
			if(j%apparition == 0){

				fprintf(stderr, "%d \n", *nb_monster);

				//S'il y a moins ou 10 monstres
				if((*nb_monster) < 10) {

					//Si le joueur est au niveau 0
					if(interface->lvl == 0)
						//Ajoute un monstre c1 (champignon)
						addMonster(p_lmonster, interface->lvl, "C1", 50, 5, "M", 3, 10, 5, map->list_node->p_head);
					//Si le joueur est à un niveau entre 1 et 3
					else if(interface->lvl > 0 && interface->lvl <= 3) {

						//Random entre 1 et 2
						random = rand()%(3-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1", 100, 5, "M", 3, 10, 5, map->list_node->p_head);
						else
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 120, 3, "H", 2, 15, 5, map->list_node->p_head);
					
					}
					//Si le joueur est à un niveau entre 4 et 5
					else if(interface->lvl > 3 && interface->lvl <= 5) {
						apparition = 100;

						//Random entre 1 et 3
						random = rand()%(4-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1", 250, 8, "M", 3, 10, 5, map->list_node->p_head);
						else if(random == 2)
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 200, 8, "H", 2, 15, 5, map->list_node->p_head);
						else
							//Ajoute un monstre P (puce)
							addMonster(p_lmonster, interface->lvl, "P", 250, 8, "L", 1, 20, 5, map->list_node->p_head);

					}
					//Si le joueur est à un niveau suppérieur à 6 à 8
					else if(interface->lvl > 5 && interface->lvl <= 8) {
						apparition = 50;

						//Random entre 1 et 4
						random = rand()%(5-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1", 150, 8, "M", 2, 10, 5, map->list_node->p_head);
						else if(random == 2)
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 200, 5, "H", 1, 15, 5, map->list_node->p_head);
						else if(random == 3)
							//Ajoute un monstre P (puce)
							addMonster(p_lmonster, interface->lvl, "P", 250, 10, "L", 1, 20, 5, map->list_node->p_head);
						else 
							//Ajoute un monstre F (fourmi)
							addMonster(p_lmonster, interface->lvl, "F", 300, 10, "R", 1, 30, 5, map->list_node->p_head);

					}
					//Si le joueur est à un niveau suppérieur à 9 à 12
					else if(interface->lvl > 8 && interface->lvl <= 12) {
						apparition = 50;

						//Random entre 1 et 5
						random = rand()%(6-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1",200, 10, "M", 1, 10, 5, map->list_node->p_head);
						else if(random == 2  || random == 4)
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 250, 10, "H", 1, 15, 5, map->list_node->p_head);
						else if(random == 3)
							//Ajoute un monstre P (puce)
							addMonster(p_lmonster, interface->lvl, "P", 300, 10, "L", 1, 20, 5, map->list_node->p_head);
						else 
							//Ajoute un monstre F (fourmi)
							addMonster(p_lmonster, interface->lvl, "F", 350, 10, "R", 1, 30, 5, map->list_node->p_head);

					}
					//Si le joueur est à un niveau suppérieur à 9 à 12
					else if(interface->lvl > 8 && interface->lvl <= 12) {
						apparition = 50;

						//Random entre 1 et 6
						random = rand()%(7-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1", 250, 10, "M", 1, 10, 5, map->list_node->p_head);
						else if(random == 2 || random == 4)
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 300, 15, "H", 1, 15, 5, map->list_node->p_head);
						else if(random == 3  || random == 5)
							//Ajoute un monstre P (puce)
							addMonster(p_lmonster, interface->lvl, "P", 350, 15, "L", 1, 20, 5, map->list_node->p_head);
						else 
							//Ajoute un monstre F (fourmi)
							addMonster(p_lmonster, interface->lvl, "F", 400, 15, "R", 1, 30, 5, map->list_node->p_head);

					}
					//Si le joueur est à un niveau suppérieur à 13 à 15
					else if(interface->lvl > 12 && interface->lvl <= 15) {
						apparition = 50;

						//Random entre 1 et 7
						random = rand()%(8-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1", 300, 10, "M", 1, 10, 5, map->list_node->p_head);
						else if(random == 2 || random == 4)
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 350, 20, "H", 1, 15, 5, map->list_node->p_head);
						else if(random == 3 || random == 5)
							//Ajoute un monstre P (puce)
							addMonster(p_lmonster, interface->lvl, "P", 400, 20, "L", 1, 20, 5, map->list_node->p_head);
						else 
							//Ajoute un monstre F (fourmi)
							addMonster(p_lmonster, interface->lvl, "F", 450, 20, "R", 1, 30, 5, map->list_node->p_head);

					}
					//Si le joueur est à un niveau suppérieur à 13 à 15
					else if(interface->lvl > 12 && interface->lvl <= 15) {
						apparition = 30;

						//Random entre 1 et 8
						random = rand()%(9-1) +1;

						if(random == 1)
							//Ajoute un monstre c1 (champignon)
							addMonster(p_lmonster, interface->lvl, "C1", 350, 15, "M", 1, 10, 5, map->list_node->p_head);
						else if(random == 2 || random == 4)
							//Ajoute un monstre c2 (champignon)
							addMonster(p_lmonster, interface->lvl, "C2", 400, 25, "H", 1, 15, 5, map->list_node->p_head);
						else if(random == 3 || random == 5)
							//Ajoute un monstre P (puce)
							addMonster(p_lmonster, interface->lvl, "P", 450, 25, "L", 1, 20, 5, map->list_node->p_head);
						else 
							//Ajoute un monstre F (fourmi)
							addMonster(p_lmonster, interface->lvl, "F", 500, 25, "R", 1, 30, 5, map->list_node->p_head);

					}
					

					(*nb_monster)++;
				}
				//S'il n'y a plus de monstre
				else if(*nb_monster == 10 && p_lmonster->length == 0) {
					updateLvl(interface); //Monte de niveau
					(*nb_monster)++;
				}
				else if(*nb_monster > 10 && *nb_monster <= 15) 
					(*nb_monster)++;
				else if(*nb_monster == 16) 
					*nb_monster = 0;

			}

		}
		else {
			fprintf(stderr, "Erreur avec l'interface\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Erreur avec la liste de monstre\n");
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

	for(i = 0; i <= j; i++) {
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

	for(i = 0; i <= j; i++) {
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


