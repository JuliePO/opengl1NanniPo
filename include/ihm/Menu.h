#ifndef ITD_MENU_H_
#define ITD_MENU_H_

#include "element/Tower.h"
#include "element/Monster.h"
#include "element/Shot.h"
#include "ihm/Interface.h"
#include "file/Map.h"
#include "file/FileTower.h"

/************* Appel de fonction *************/
//click menu principal
void clickMenuPrincipale(float, float, int*, int*);
//click pour l'achat d'une tour
int clickMenuTour(LTower*, LFileTower*, Interface*, float, float);
//click supprimer une tour
int clickTourDelete(LTower*, LShot*, Tower*, Interface*, float, float, int*);
//click monte de niveau une tour
int clickTourUpgrate(Tower*, Interface*, float, float, int*);
//click avance rapide / play / pause
int clickTime(float, float, int);
//click fermer
int clickExit(LMonster*, LShot*, LTower*, LFileTower*, Map*, Interface*, float, float, int);
//click aide
int clickAide(float, float, int);
//click sur une tours : afficher les propriétés
Tower* clickTower(LTower*, float, float, int*);
//click sur monstre : afficher les propriétés
Monster* clickMonster(LMonster*, float, float, int*);
//Free tous les élements
void freeAll (LMonster*, LShot*, LTower*, LFileTower*, Map*, Interface*);

#endif
