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
#include "ihm/Interface.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 660;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 10;
static const Uint32 FRAMERATE_MILLISECONDS_RAPIDE = 1000 / 50;
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
	int testTower = 0;

	/* Initialisation */
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        	fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}

	setVideoMode();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutInit(&argc, argv); // initialisation de GLUT

    	SDL_WM_SetCaption("Tower Defense IMAC1", NULL);

	/* Variables */

	//La carte
	Map* map = newMap (argv[1]);
	//Texture de la carte
	GLuint texture;
	SDL_Surface* imgMap;
	loadMapTexture(map, &texture, imgMap);
	if(argc == 3)
		loadTexture("./images/map2.ppm", &texture, imgMap);
	//Texture des monstres
	GLuint monster;
	SDL_Surface* imgMonster;
	loadTexture("./images/sprite.png", &monster, imgMonster);
	
	GLuint shot;
	SDL_Surface* imgShot;
	loadTexture("./images/shot.png", &shot, imgShot);
	//Texture menu
	GLuint spriteMenu;
	SDL_Surface* imgButtonMenu;
	loadTexture("./images/sprite_menu.png", &spriteMenu, imgButtonMenu);
	//Texture fond menu
	GLuint fondMenu;
	SDL_Surface* imgFondMenu;
	loadTexture("./images/fondMenu.png", &fondMenu, imgFondMenu);
	//Texture pour les boutons
	GLuint spriteButton;
	SDL_Surface* imgSpriteButton;
	loadTexture("./images/sprite_button.png", &spriteButton, imgSpriteButton);

	//Initialisation de l'interface
	Interface* interface = newInterface();

	//Initialisation de la liste de monstre
	LMonster* p_lmonster = new_LMonster();
	//Initialisation de la liste de tours
	LTower* p_ltower = new_LTower();
	//Initialisation de la liste de shots
	LShot* p_lshot = new_LShot();

	int i = 0; int k = 0;
	int nb_monster = 0, j = 0;

	Monster* target = NULL;

	int loop = 1;

	/**** Main loop ***/
  	while(loop) {
   		Uint32 startTime = SDL_GetTicks();

	    	/* dessin */

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		drawMap(&texture);

		drawMenuUp(&spriteButton, play);
		drawMenuLeft(&spriteMenu, &fondMenu, interface);

		drawInterface (interface);

		j++;
		if(j == 50){
			j=0;
			if(nb_monster < 10) {
				addMonster(p_lmonster, "c", 10.0, 10.0, "p", 10.0, 10.0, 10.0, map->list_node->p_head);
				nb_monster ++;
			}
			else if(nb_monster == 10 && p_lmonster->length == 0) {
				updateLvl(interface);
				nb_monster ++;
			}
			else if(nb_monster > 10 && nb_monster <= 15) 
				nb_monster ++;
			else if(nb_monster == 16)
				nb_monster = 0;
		}

		/*if(p_lmonster->length == 0)
			nb_monster = 0;*/
		//Création d'un pointeur tour temporaire pour parcourir la liste de tours
		Tower *p_temp = p_ltower->p_head;

		//Parcours la liste de tours
		while(p_temp != NULL){

			if(testMouse == 0) {
				if(k%20 == 0) {
					target = inSight (p_lmonster, p_temp);
					if(target != NULL) {
						addShot(p_lshot, target, p_temp);
						k=0;
					}
				}
			}

			p_temp = p_temp->p_next;
		}
		k++;


		drawTower(&monster, p_ltower, p_lmonster, target, testMouse, testTower);


		drawMonster(&monster, p_lmonster);
		//Bouger le monstre
		if(moveMonster(p_lmonster, map->list_node->p_tail) == 2) {
			p_lmonster = removeMonster(p_lmonster, p_lmonster->p_head);
			udapteLife(interface);
		}

		drawShot(&shot, p_lshot);
		moveShot(p_lshot);
		collisionMissile(p_lshot, p_lmonster, interface);

		//printf("%d \n", p_lmonster->length);
			//loop = 0;

		/*int nb = 0;
		Monster* m = p_lmonster->p_head;
		while(m != NULL) {
			nb++;
			m = m->p_next;
		}

		fprintf(stderr, "nombre monstre : %d\n", nb);*/

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

			printf("%f %f\n", tmp->x, tmp->y);

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
						if(clickMenuTour(p_ltower, interface, e.button.x, e.button.y) == 1)
							testMouse = 1;
					}
					else {
						if(testTower != 0)
							testMouse = 0;
					}

					play = clickAvanceRapide(e.button.x, e.button.y, play);
					loop = clickExit(e.button.x, e.button.y);
				}
			break;

			case SDL_MOUSEMOTION :
				if(testMouse == 1) {
					if(moveTower(p_ltower, p_ltower->p_tail, map->list_pixels, e.button.x, e.button.y) == 1)
						testTower = 1;
					else
						testTower = 0;
				}
				break;

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
		if(play == 0) {
		    if(elapsedTime < FRAMERATE_MILLISECONDS) {
		      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		    }
		}
		else if(play == 2) {
			if(elapsedTime < FRAMERATE_MILLISECONDS_RAPIDE) {
		      		SDL_Delay(FRAMERATE_MILLISECONDS_RAPIDE - elapsedTime);
		   	}
		}
	  }


	glBindTexture(GL_TEXTURE_2D, 0);

	/*SDL_FreeSurface(image);*/
	/*glDeleteTextures(1, &shot);
	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &monster);*/
	SDL_Quit();
	return EXIT_SUCCESS;
}
