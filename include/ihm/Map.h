#ifndef LDR_MAP_H_
#define LDR_MAP_H_

#include "geometry/Color3f.h"
#include "ihm/Image.h"
#include "ihm/Node.h"

/************* STRUCTURE DE LA CARTE *************/
typedef struct struct_map {

	//Image ppm
	Image* img;

	//énergie
	int energie;

	//couleur du chemin
	Color3f road;

	//couleur des noeuds
	Color3f node;

	//couleur à la zone constructible
	Color3f construct;
	//liste des pixels de zone constructible
	LNode* list_pixels;

	//couleur clé de la zone d'entrée
	Color3f in;

	//couleur clé de la zone de sortie
	Color3f out;

	//Nombre de noeud
	int number_node;

	//Liste des noeuds
	LNode* list_node;

}Map;

/************* Appel de fonction *************/
int verificationMap(Map*, char*);
int ChangeColor(Image*, unsigned char*, Map*);
int changeColorRoad(Image*, unsigned char*, Map*);
int changeColorConstruct(Image*, unsigned char*, Map*);
int changeColorNode(Image*, unsigned char*, Map*);
int changeColorIn(Image*, unsigned char*, Map*);
int changeColorOut(Image*, unsigned char*, Map*);

#endif
