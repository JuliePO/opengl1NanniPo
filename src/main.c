#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sdl_tools.h"
#include "geometry/Color3f.h"
#include "ihm/Map.h"
#include "ihm/Texture.h"
#include "ihm/Image.h"
#include "ihm/Node.h"
#include "element/Monster.h"
#include "element/Tower.h"

static unsigned int WINDOW_WIDTH = 600;
static unsigned int WINDOW_HEIGHT = 600;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 10;
float pi = 3.14;

void reshape() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0., 600., 600., 0.);
}

void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
        	SDL_OPENGL  | SDL_RESIZABLE | SDL_DOUBLEBUF)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  
  reshape();
  
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapBuffers();
}

void dessinCercle(float rayon) {
	
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

int main(int argc, char** argv) {

	int testMouse = 0;

	/* Init */
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        	fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}

	setVideoMode();

    	SDL_WM_SetCaption("Tower Defense IMAC La classe !!", NULL);

	/* Création d'une surface SDL dans laquelle le raytracer dessinera */
    	/*SDL_Surface* framebuffer = NULL;
    	if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, 
        	WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
        	fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}*/

	Map* map = malloc(sizeof(Map));
	verificationMap(map,argv[1]);
	
	GLuint texture;
	loadMapTexture(map, &texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint monster;
	loadTexture(&monster, "./images/sprite.png");

	LMonster* p_lmonster = new_LMonster();
	LTower* p_ltower = new_LTower();
	addMonster(p_lmonster, "c", 10.0, 10.0, "p", 10.0, map->list_node);

	int i = 0;
	int nb_monster = 1, j = 0;

	int loop = 1;

	/**** Main loop ***/
  	while(loop) {
   		Uint32 startTime = SDL_GetTicks();

	    	/* dessin */

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, &texture);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(600, 600);

			glTexCoord2f(1, 0);
			glVertex2f(600, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 600);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		float x1, x2, xt1, xt2;

		if(i == 0) {
			i++;
			x1 = 0.5;
			x2 = 0.583;

			xt1 = 0.25;
			xt2 = 0.333;
		}
		else if (i == 1) {
			i++;
			x1 = 0.583;
			x2 = 0.666;

			xt1 = 0.333;
			xt2 = 0.416;
		}
		else {
			i = 0;
			x1 = 0.666;
			x2 = 0.75;

			xt1 = 0.416;
			xt2 = 0.5;
		}

		j++;
		if(j == 50){
			j=0;
			if(nb_monster <= 10) {
				addMonster(p_lmonster, "c", 10.0, 10.0, "p", 10.0, map->list_node);
				nb_monster ++;
			}
		}

		//Création d'une tour temporaire pour parcourir la liste de tours
		Tower *p_temp = p_ltower->p_tail;

		//Parcours la liste de tours
		while(p_temp != NULL){

			glLoadIdentity();
			glPushMatrix();
			glTranslatef(p_temp->x,p_temp->y,0.0);
			dessinCercle(p_temp->range);
			glPopMatrix();

			glLoadIdentity();
			glPushMatrix();
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, &monster);

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

			if(inSight (p_lmonster, p_temp) == 1)
				printf("Collision\n");

			p_temp = p_temp->p_prev;
		}


		//Création d'un monstre temporaire pour parcourir la liste de monstres
		Monster *p_tmp = p_lmonster->p_tail;

		//Parcours la liste de monstres
		while(p_tmp != NULL){

			glLoadIdentity();
			glPushMatrix();
			//Active le texturage 2D
			glEnable(GL_TEXTURE_2D);
			//appel de la texture
			glBindTexture(GL_TEXTURE_2D, &monster);

				int xm1, xm2, ym1, ym2;
				xm1 = p_tmp->x + 20;
				xm2 = p_tmp->x - 20;
				ym1 = p_tmp->y + 20;
				ym2 = p_tmp->y - 20;
			
			

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

			//Déblinder la texture
			glBindTexture(GL_TEXTURE_2D, 0);
			//Désactive le texturage 2D
			glDisable(GL_TEXTURE_2D);

			glPopMatrix();

			p_tmp = p_tmp->p_prev;
		}

		moveMonster(p_lmonster);


		/*Node* tmp = map->list_node->p_head;


		while(tmp->p_next != NULL){


			glBegin(GL_LINES);
				glColor3ub(0,0,255);
				glVertex2d(tmp->x, tmp->y);
				glVertex2d(tmp->p_next->x, tmp->p_next->y);
			glEnd();

			glBegin(GL_POINTS);
				glColor3ub(255,0,0);
				glVertex2d(tmp->x, tmp->y);
			glEnd();

			tmp = tmp->p_next;		

		}*/

		glFlush();
		 SDL_GL_SwapBuffers();
		    /* ****** */    

		    SDL_Event e;
		    while(SDL_PollEvent(&e)) {
		      if(e.type == SDL_QUIT) {
			loop = 0;
			break;
		      }
		      
		      switch(e.type) {

			case SDL_VIDEORESIZE:
			  WINDOW_WIDTH = e.resize.w;
			  WINDOW_HEIGHT = e.resize.h;
			  setVideoMode();
			  break;

			case SDL_MOUSEBUTTONDOWN :
				if(e.button.button == SDL_BUTTON_LEFT) {
					if(testMouse == 0 && p_ltower->p_tail != NULL) {
						p_ltower->p_tail->x = e.button.x;
						p_ltower->p_tail->y = e.button.y;
						testMouse = 1;
					}
					else
						testMouse = 0;
				}
			break;

			case SDL_MOUSEMOTION :
				if(testMouse == 1) {
					p_ltower->p_tail->x = e.button.x;
					p_ltower->p_tail->y = e.button.y;
				}
				break;

			case SDL_KEYDOWN:
			  switch(e.key.keysym.sym){
			    case 'q' : 
			    case SDLK_ESCAPE : 
				loop = 0;
				break;
				
			    case 'a' :
				addTower(p_ltower, 10.0, 10.0, "c", 50., 10.0);
				break;

			    default : break;
			  }
			  break;
			  
			default:
			  break;
			}
	
		}

		 Uint32 elapsedTime = SDL_GetTicks() - startTime;
	    if(elapsedTime < FRAMERATE_MILLISECONDS) {
	      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
	    }
	  }


	glBindTexture(GL_TEXTURE_2D, 0);

	/*SDL_FreeSurface(image);*/
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &monster);
	SDL_Quit();
	return EXIT_SUCCESS;
}
