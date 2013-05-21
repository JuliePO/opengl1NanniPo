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
#include "file/Map.h"
#include "file/Texture.h"
#include "file/Image.h"
#include "ihm/Node.h"
#include "ihm/Draw.h"
#include "ihm/Menu.h"
#include "ihm/Interface.h"
#include "file/FileTower.h"

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
	int nbMenu = 0;
	int nbMap = 0;

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

	/***** Variables ******/
	//Texture menuMap
	GLuint menuMap;
	SDL_Surface* imgMenuMap = NULL;
	loadTexture("./images/menu-map.png", &menuMap, imgMenuMap);

	//Texture menuMap button
	/*GLuint menuMapButton;
	SDL_Surface* imgMenuMapButton = NULL;
	loadTexture("./images/map1/sprite_button_menu.png", &menuMapButton, imgMenuMapButton);*/


	//Texture menuPrincipal
	GLuint menuPrincipal;
	SDL_Surface* imgMenuPrincipal = NULL;
	loadTexture("./images/map1/MenuPrincipal.png", &menuPrincipal, imgMenuPrincipal);

	//Texture menuPrincipal button
	GLuint menuPrincipalButton;
	SDL_Surface* imgMenuPrincipalButton = NULL;
	loadTexture("./images/map1/sprite_button_menu.png", &menuPrincipalButton, imgMenuPrincipalButton);

	Map* map;

	//La carte
	GLuint texture;
	SDL_Surface* imgMap = NULL;

	//Texture aide
	GLuint help;
	SDL_Surface* imgHelp = NULL;

	//Texture des monstres
	GLuint monster;
	SDL_Surface* imgMonster = NULL;

	//Texture des tours
	GLuint tower;
	SDL_Surface* imgTower = NULL;

	//Texture des shots	
	GLuint shot;
	SDL_Surface* imgShot = NULL;

	//Texture menu
	GLuint spriteMenu;
	SDL_Surface* imgButtonMenu = NULL;

	//Texture fond menu
	GLuint fondMenu;
	SDL_Surface* imgFondMenu = NULL;

	//Texture pour les boutons
	GLuint spriteButton;
	SDL_Surface* imgSpriteButton = NULL;

	//Texture fond menu up
	GLuint fondMenuUp;
	SDL_Surface* imgFondMenuUp = NULL;

	if(nbMap == 1) {

		//La carte
		map = newMap ("./data/IDTMap1.idt");
		//Texture de la carte

		loadMapTexture(map, &texture, imgMap);
		if(argc == 3)
			loadTexture("./images/map1.ppm", &texture, imgMap);
		//Texture aide
		loadTexture("./images/map1/help.png", &help, imgHelp);

		//Texture des monstres
		loadTexture("./images/map1/sprite_monster.png", &monster, imgMonster);
		//Texture des tours
		loadTexture("./images/map1/sprite_tour.png", &tower, imgTower);

		//Texture des shots	
		loadTexture("./images/shot.png", &shot, imgShot);
		//Texture menu
		loadTexture("./images/map1/sprite_menu1.png", &spriteMenu, imgButtonMenu);
		//Texture fond menu
		loadTexture("./images/fondMenu.png", &fondMenu, imgFondMenu);
		//Texture pour les boutons
		loadTexture("./images/map1/sprite_button1.png", &spriteButton, imgSpriteButton);
		//Texture fond menu up
		loadTexture("./images/map1/fondMenuUp.png", &fondMenuUp, imgFondMenuUp);
	}
	else {
		//La carte
		map = newMap ("./data/IDTMap2.idt");
		//Texture de la carte

		loadMapTexture(map, &texture, imgMap);
		if(argc == 3)
			loadTexture("./images/map2.ppm", &texture, imgMap);
		//Texture aide
		loadTexture("./images/map2/help.png", &help, imgHelp);

		//Texture des monstres
		loadTexture("./images/map2/sprite_monster.png", &monster, imgMonster);
		//Texture des tours
		loadTexture("./images/map2/sprite_tour.png", &tower, imgTower);

		//Texture des shots	
		loadTexture("./images/shot.png", &shot, imgShot);
		//Texture menu
		loadTexture("./images/map2/sprite_menu1.png", &spriteMenu, imgButtonMenu);
		//Texture fond menu
		loadTexture("./images/fondMenu.png", &fondMenu, imgFondMenu);
		//Texture pour les boutons
		loadTexture("./images/map2/sprite_button1.png", &spriteButton, imgSpriteButton);
		//Texture fond menu up
		loadTexture("./images/map2/fondMenuUp.png", &fondMenuUp, imgFondMenuUp);
	}

	//Initialisation de l'interface
	Interface* interface = newInterface();

	//Initialisation de la liste de monstre
	LMonster* p_lmonster = new_LMonster();
	//Initialisation de la liste de tours
	LTower* p_ltower = new_LTower();
	//Initialisation de la liste de shots
	LShot* p_lshot = new_LShot();

	//Initialisation de la liste de tours (file)
	LFileTower* p_lfileTower =  newFileTower ("./data/IDTtower.idt");

	int i = 0;
	int nb_monster = 0, j = 0;
	int propriete = 0;
	int aide = 0;

	//Pour afficher les propriétés
	Tower* pTower = NULL;
	Monster* pMonster = NULL;

	int random;

	int pvMax, resistance, pace, points, gain;
	pvMax = 50;
	resistance = 5;
	pace = 50;
	points = 10;
	gain = 5;

	int loop = 1;

	/**** Main loop ***/
  	while(loop) {
   		Uint32 startTime = SDL_GetTicks();

	    	/* dessin */

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		if(nbMenu == 0)
			drawMenuMap (&menuMap);
		else if(nbMenu == 1) {
			drawMenuPrincipale (&menuPrincipal, &menuPrincipalButton);
		}
		else if(nbMenu == 2) 
			drawHelp (&help, &spriteButton, &menuPrincipalButton, nbMenu);
		else {
			//Afficher l'aide
			if(aide == 1)
				drawHelp (&help, &spriteButton, &menuPrincipalButton, nbMenu);
			else {
				drawMap(&texture);
				drawMenuUp(&spriteButton, &fondMenuUp, play);
				drawMenuLeft(&spriteMenu, &fondMenu, interface);
				drawInterface (&spriteButton, interface);

				if(propriete == 1) {
					drawProprieteTower(&tower, &spriteMenu, pTower, interface);
					pMonster = NULL;
				}
				else if(propriete == 2) {

					pTower = NULL;
					if(pMonster != NULL) {
						if(pMonster->pv > 0) {
							drawProprieteMonster(&monster, pMonster);
						}
						else {
							propriete = 0;
							pMonster = NULL;
						}
					}
					else
						propriete = 0;
				}

				if(play != 1) {

					if(j%pace == 0){
						j=0;
						if(nb_monster < 10) {

							if(interface->lvl == 0)
								addMonster(p_lmonster, interface->lvl, "C1", pvMax, resistance, "M", pace, points, gain, map->list_node->p_head);
							else if(interface->lvl > 0 && interface->lvl <= 3) {
								random = rand()%(3-1) +1;
	
								if(random == 1)
									addMonster(p_lmonster, interface->lvl, "C1", pvMax, resistance, "M", pace, points, gain, map->list_node->p_head);
								else
									addMonster(p_lmonster, interface->lvl, "C2", 120, 2, "H", 40, 15, 10, map->list_node->p_head);
							
							}
							else if(interface->lvl > 3 && interface->lvl <= 5) {

								random = rand()%(4-1) +1;

								if(random == 1)
									addMonster(p_lmonster, interface->lvl, "C1", pvMax, resistance, "M", pace, points, gain, map->list_node->p_head);
								else if(random == 2)
									addMonster(p_lmonster, interface->lvl, "C2", 120, 2, "H", 45, 15, 10, map->list_node->p_head);
								else
									addMonster(p_lmonster, interface->lvl, "P", 140, 2, "L", 40, 20, 20, map->list_node->p_head);

							}
							else if(interface->lvl > 5) {

								random = rand()%(5-1) +1;

								if(random == 1)
									addMonster(p_lmonster, interface->lvl, "C1", pvMax, resistance, "M", pace, points, gain, map->list_node->p_head);
								else if(random == 2)
									addMonster(p_lmonster, interface->lvl, "C2", 120, 2, "H", 45, 15, 10, map->list_node->p_head);
								else if(random == 3)
									addMonster(p_lmonster, interface->lvl, "P", 140, 2, "L", 40, 20, 20, map->list_node->p_head);
								else 
									addMonster(p_lmonster, interface->lvl, "F", 160, 2, "R", 35, 30, 30, map->list_node->p_head);

							}

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
					j++;

					//Création d'un pointeur tour temporaire pour parcourir la liste de tours
					Tower *p_temp = p_ltower->p_head;

					//Parcours la liste de tours
					while(p_temp != NULL){

						if(p_temp == p_ltower->p_tail) {
							if(testMouse == 0) {
								if((p_temp->compteur)%(p_temp->rate) == 0) {
									if(inSight (p_lshot, p_lmonster, p_temp) != 0) {
										(p_temp->compteur)=0;
									}
								}
							}
						}
						else {
							if((p_temp->compteur)%(p_temp->rate) == 0) {
								if(inSight (p_lshot, p_lmonster, p_temp) != 0) {
									(p_temp->compteur)=0;
								}
							}
						}

						(p_temp->compteur)++;
						p_temp = p_temp->p_next;
					}
				}


				drawTower(&tower, p_ltower, p_lmonster, pTower, testMouse, testTower);

				drawMonster(&monster, p_lmonster, play);

				if(play != 1) {

					//Bouger le monstre
					if(moveMonster(p_lmonster, map->list_node->p_tail) == 2) {

						//Pointeur shot temporaire pour parcourir la liste
						Shot *p_tempS = p_lshot->p_head;

						while(p_tempS != NULL) {
							if(p_tempS->target == p_lshot->p_head)
								p_tempS->target == NULL;

							p_tempS = p_tempS->p_next;
						}
						p_lmonster = removeMonster(p_lmonster, p_lmonster->p_head);
						udapteLife(interface);
					}

					while(i < 3) {
						drawShot(&shot, p_lshot);
						moveShot(p_lshot);
						collisionMissile(p_lshot, p_lmonster, interface, pMonster, &propriete);
						i++;
					}
					i = 0;

				}
				else {
					drawShot(&shot, p_lshot);
				}
			}
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

				case SDL_VIDEORESIZE:
					WINDOW_WIDTH = e.resize.w;
					WINDOW_HEIGHT = e.resize.h;
					setVideoMode();
					break;

				case SDL_MOUSEBUTTONDOWN :
					if(e.button.button == SDL_BUTTON_LEFT) {
						if(nbMenu != 3) {
							clickMenuPrincipale(e.button.x, e.button.y, &nbMenu, &nbMap);
						}
						else {

							if(testMouse == 0) {
								if(clickMenuTour(p_ltower, p_lfileTower, interface, e.button.x, e.button.y) == 1)
									testMouse = 1;
							}
							else {
								if(testTower != 0)
									testMouse = 0;
							}

							if(pTower != NULL && propriete == 1) {
								clickTourDelete(p_ltower, p_lshot, pTower, interface, e.button.x, e.button.y, &propriete);
								clickTourUpgrate(pTower, interface, e.button.x, e.button.y, &propriete);
							}

							play = clickTime(e.button.x, e.button.y, play);
							loop = clickExit(e.button.x, e.button.y, aide);

							pTower = clickTower(p_ltower, e.button.x, e.button.y, &propriete);
							pMonster = clickMonster(p_lmonster, e.button.x, e.button.y, &propriete);

							aide = clickAide(e.button.x, e.button.y, aide);
						}
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
