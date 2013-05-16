#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "sdl_tools.h"
#include "geometry/Color3f.h"
#include "element/Monster.h"
#include "element/Tower.h"
#include "element/Shot.h"
#include "ihm/Map.h"
#include "ihm/Texture.h"
#include "ihm/Image.h"
#include "ihm/Node.h"
#include "ihm/Draw.h"
#include "ihm/Menu.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 660;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 10;
float pi = 3.14;

void reshape() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0., 800., 660., 0.);
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

int main(int argc, char** argv) {

	int testMouse = 0;
	int play = 0;

	/* Init */
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        	fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}

	setVideoMode();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutInit(&argc, argv); // initialisation de GLUT

    	SDL_WM_SetCaption("Tower Defense IMAC La classe !!", NULL);

	/* Création d'une surface SDL dans laquelle le raytracer dessinera */
    	/*SDL_Surface* framebuffer = NULL;
    	if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, 
        	WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
        	fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}*/

	Map* map = (Map*)malloc(sizeof(Map));
	verificationMap(map,argv[1]);
	
	GLuint texture;
	loadMapTexture(map, &texture);

	GLuint monster;
	loadTexture(&monster, "./images/sprite.png");

	GLuint shot;
	loadTexture(&shot, "./images/shot.png");

	GLuint menu1;
	loadTexture(&menu1, "./images/menu1.png");

	GLuint menu2;
	loadTexture(&menu2, "./images/menu2.png");

	GLuint menuNone;
	loadTexture(&menuNone, "./images/menuNone.png");

	GLuint fondMenu;
	loadTexture(&fondMenu, "./images/fondMenu.png");

	GLuint spriteButton;
	loadTexture(&spriteButton, "./images/sprite_button.png");

	LMonster* p_lmonster = new_LMonster();
	LTower* p_ltower = new_LTower();
	addMonster(p_lmonster, "c", 10.0, 10.0, "p", 10.0, map->list_node);

	int i = 0; int k = 0;
	int nb_monster = 1, j = 0;

	Monster* target = NULL;

	int loop = 1;

	/**** Main loop ***/
  	while(loop) {
   		Uint32 startTime = SDL_GetTicks();

	    	/* dessin */

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		drawMap (&texture);

		drawMenu (&menu1, &menu2, &menuNone, &fondMenu, &spriteButton, play);

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

		if(p_lmonster->length == 0)
			nb_monster = 0;

		k = drawTower(&monster, &shot, p_ltower, p_lmonster, target, xt1, xt2, testMouse, k);
		if(drawMonster(&monster, p_lmonster, map->list_node->p_tail, x1, x2) == 2)
			loop = 0;


		/*Node* tmp = map->list_pixels->p_head;


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

			printf("%d %d\n", tmp->x, tmp->y);

			tmp = tmp->p_next;		

		}*/

		/*writeString(100, 100,  "aaa");
		writeString(200, 200,  "bbb");
		writeString(300, 300,  "ccc");*/

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
					if(testMouse == 0) {
						if(clickMenuTour(p_ltower, e.button.x, e.button.y) == 1)
							testMouse = 1;
					}
					else
						testMouse = 0;
				}
			break;

			case SDL_MOUSEMOTION :
				if(testMouse == 1) {
					moveTower(p_ltower->p_tail, e.button.x, e.button.y);
				}
				break;

			case SDL_KEYDOWN:
			  switch(e.key.keysym.sym){
			    case 'q' : 
			    case SDLK_ESCAPE : 
				loop = 0;
				break;
				
			    case 'a' :
				addTower(p_ltower, 3.0, 10.0, "c", 50., 10.0, 200, 60);
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
	glDeleteTextures(1, &shot);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &monster);
	SDL_Quit();
	return EXIT_SUCCESS;
}
