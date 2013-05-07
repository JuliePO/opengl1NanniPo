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
#include "ihm/Image.h"
#include "ihm/Node.h"

static unsigned int WINDOW_WIDTH = 600;
static unsigned int WINDOW_HEIGHT = 600;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {

	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        	fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}

	SDL_Surface* screen = NULL;
    	if(NULL == (screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
        	SDL_OPENGL))) { //SDL_DOUBLEBUF
        	fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}
    	SDL_WM_SetCaption("Tower Defense IMAC La classe !!", NULL);

	/* Création d'une surface SDL dans laquelle le raytracer dessinera */
    	/*SDL_Surface* framebuffer = NULL;
    	if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, 
        	WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
        	fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}*/

	GLuint texture;
	Map* map = malloc(sizeof(Map));
	verificationMap(map,argv[1]);
	SDL_Surface* image = IMG_Load(map->img->path);
	if(image == NULL) {
		fprintf(stderr, "impossible de charger l'image %s\n", map->img->path);
		return EXIT_FAILURE;
	}

	//Fait une copie de la texture pour la stocker
	glGenTextures(1, &texture);
	//dire qu'on fait des modification sur cette texture
	glBindTexture(GL_TEXTURE_2D, &texture);
	//dit qu'on utilise un filtre linéaire : fait une moyenne des couleurs
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//choisi le bon format selon l'image
	GLenum format;
	switch(image->format->BytesPerPixel) {
		case 1:
			format = GL_RED;
			break;
		case 3:
			/* Ne gere pas les machines big-endian (a confirmer...) */
			format = GL_RGB;
			break;
		case 4:
			/* Ne gere pas les machines big-endian (a confirmer...) */
			format = GL_RGBA;
			break;
		default:
			/* On ne traite pas les autres cas */
			fprintf(stderr, "Format des pixels de l’image %s non pris en charge\n", image);
			return EXIT_FAILURE;
	}

	//
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	int loop = 1;

	/**** Main loop ***/
  	while(loop) {
   		Uint32 startTime = SDL_GetTicks();

	    	/* dessin */

		glClear(GL_COLOR_BUFFER_BIT);

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, &texture);

		glBegin(GL_QUADS);
		//couleur neutre
		glColor3ub(255,255,255);
		//coordonée de la texture
		glTexCoord2f(1, 0);
		//Cordonnée du quadrilatère 
		glVertex2f(1, 1);

		glTexCoord2f(1, 1);
		glVertex2f(1, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, -1);

		glTexCoord2f(0, 0);
		glVertex2f(-1, 1);

		glEnd();

		//appel de la texture => changement texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		float x, y;
		Node* tmp = map->list_node->p_head;


		while(tmp->p_next != NULL){


			glBegin(GL_LINES);
				glColor3ub(0,0,255);
				x = tmp->x / 600.0;
				y = tmp->y / 600.0;
				glVertex2d(x,y);

				x = tmp->p_next->x / 600.0;
				y = tmp->p_next->y / 600.0;
				glVertex2d(x,y);
			glEnd();

			glBegin(GL_POINTS);
				glColor3ub(255,0,0);
				x = tmp->x / 600.0;
				y = tmp->y / 600.0;
				glVertex2d(x,y);
			glEnd();

			tmp = tmp->p_next;		

		}

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

			case SDL_KEYDOWN:
			  switch(e.key.keysym.sym){
			    case 'q' : 
			    case SDLK_ESCAPE : 
				loop = 0;
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

	SDL_FreeSurface(image);
	glDeleteTextures(1, &texture);
	SDL_Quit();
	return EXIT_SUCCESS;
}
