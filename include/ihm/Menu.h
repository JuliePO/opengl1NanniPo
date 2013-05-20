#ifndef ITD_MENU_H_
#define ITD_MENU_H_

#include "element/Tower.h"
#include "ihm/Interface.h"
#include "file/FileTower.h"

/************* Appel de fonction *************/
//click pour l'achat d'une tour
int clickMenuTour(LTower*, LFileTower*, Interface*, float, float);
//click avance rapide
int clickAvanceRapide(float, float, int);
//click fermer
int clickExit(float, float);

#endif
