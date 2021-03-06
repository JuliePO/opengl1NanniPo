#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "geometry/Point2D.h"
#include "geometry/Vector2D.h"
#include "geometry/Intersection.h"

/************* Intersection d'un segment avec un point *************/
/* Vérifie s'il y a une intersection entre un segment et un point. Calcule l'équation de le droite. Vérifie 	*
*  s'il y a une intersection. Si oui vérifie s'il appartient au segment. Si oui retourne 1 sinon retourne 0. 	*
*  Prend en paramètre 3 points dont 2 qui constituent le segment.							*/

int intersectionPointSegment (Point2D point, Point2D A, Point2D B) {

	float a, b;
	
	//Calcule le vecteur constituer du point A et B
	Vector2D vector = Vector(A, B);

	//Si b différent de 0 (pas de division par 0)
	if(vector.y != 0)
		a = (vector.x) / (vector.y); 
	else
		a = 0;
	
	b = (A.y) - (A.x)*a;

	//Vérifie si le point appartient à la droite = intersection
	if((point.x)*a + b - (point.y) == 0) {

		float xmin = ((A.x) < (B.x)) ? (A.x) : (B.x);
		float xmax = ((A.x) > (B.x)) ? (A.x) : (B.x);

		float ymin = ((A.y) < (B.y)) ? (A.y) : (B.y);
		float ymax = ((A.y) > (B.y)) ? (A.y) : (B.y);

		//Vérifie que le point appartient au segment
		if(point.x >= xmin && point.x <= xmax && point.y >= ymin && point.y <= ymax)
			return 1;

	}

	return 0;

}

/************* Intersection entre deux segments de droite *************/
/* Vérifie s'il y a une intersection entre deux segments. Calcule l'équation de le droite et vérifie si	*
*  l'intersection se trouve dans les deux segments. Si oui retourne le point d'intersection. Prend en 	*
*  paramètre 4 points qui constituent les deux segments. 						*/

int intersectionSegments (Point2D A1, Point2D B1, Point2D A2, Point2D B2) {
		
	float a1, b1, a2, b2;
	float x, y;

	//Calcule les vecteurs
	Vector2D vector1 = Vector(A1, B1);
	Vector2D vector2 = Vector(A2, B2);

	//Si b différent de 0 (pas de division par 0)
	if(vector1.y != 0)
		a1 = vector1.x / vector1.y;
	else
		a1 = 0;

	//Si b différent de 0 (pas de division par 0)
	if(vector2.y != 0)
		a2 = vector2.x / vector2.y;
	else
		a2 = 0;

	//Si a1 et a2 sont différents sinon ils sont parrallèles donc pas de point d'intersection
	if(a1 != a2) {
	
		b1 = (A1.y) - (A1.x)*a1;
		b2 = (A2.y) - (A2.x)*a2;

		x = (b1 - b2) / (a2- a1);
		y = a2*x+b2;

		int xmin1 = ((A1.x) < (B1.x)) ? (A1.x) : (B1.x);
		int xmax1 = ((A1.x) > (B1.x)) ? (A1.x) : (B1.x);

		int ymin1 = ((A1.y) < (B1.y)) ? (A1.y) : (B1.y);
		int ymax1 = ((A1.y) > (B1.y)) ? (A1.y) : (B1.y);

		int xmin2 = ((A2.x) < (B2.x)) ? (A2.x) : (B2.x);
		int xmax2 = ((A2.x) > (B2.x)) ? (A2.x) : (B2.x);

		int ymin2 = ((A2.y) < (B2.y)) ? (A2.y) : (B2.y);
		int ymax2 = ((A2.y) > (B2.y)) ? (A2.y) : (B2.y);

		//Vérifie que le point d'intersection se trouve sur les segments
		if(x >= xmin1 && x <= xmax1 && y >= ymin1 && y <= ymax1 && x >= xmin2 && x <= xmax2 && y >= ymin2 && y <= ymax2)
			return 1;
	}
	else {
		fprintf(stderr, "Les droites sont parrallèles : Il n'y a pas d'intersection\n");
		return 0;
	}

	return 0;

}

/************* Intersection entre un segment et un cercle *************/
/* Vérifie s'il y a une intersection entre un segment et un cercle.  					*
*  Si oui retourne 1 sinon retourne 0. Prend en paramètre deux points, l'origine et le rayon du cercle 	*/

int intersectionSegmentCercle (Point2D A, Point2D B, Point2D origin, float ray) {

	float a, b;
	
	//Calcule le vecteur constituer du point A et B
	Vector2D vector = Vector(A, B);

	//Si b différent de 0 (pas de division par 0)
	if(vector.y != 0)
		a = (vector.x) / (vector.y); 
	else
		a = 0;
	
	b = (A.y) - (A.x)*a;

	//Calcule de A, B et C du polynome
	float Ad = a*a + 1;
	float Bd = 2*(-(origin.x) + a * (b - origin.y));
	float Cd = ((origin.x)*(origin.x)) + ((b - origin.y)*(b - origin.y)) - ((ray)*(ray));

	//Calcule de delta
	float delta = Bd*Bd - 4*Ad*Cd;

	int xmin = ((A.x) < (B.x)) ? (A.x) : (B.x);
	int xmax = ((A.x) > (B.x)) ? (A.x) : (B.x);

	int ymin = ((A.y) < (B.y)) ? (A.y) : (B.y);
	int ymax = ((A.y) > (B.y)) ? (A.y) : (B.y);

	if(delta < 0)
		return 0;
	else if (delta == 0) {
		int x, y;
		
		//Calcule des coordonnées du point d'intersection
		x = -Bd/ (2*Ad);
		y = a*x + b;

		//Vérifie que le point se trouve dans le segment
		if(xmin <= x && xmax >= x && ymin <= y && ymax >= y)
			return 1;
	}
	else {
		int x1, x2, y1, y2, test = 0;

		//Calcule des coordonnées des points d'intersections 
		x1 = (-Bd - sqrt(delta)) / (2*Ad);
		x2 = (-Bd + sqrt(delta)) / (2*Ad);

		y1 = a*x1 + b;
		y2 = a*x2 + b;

		//Vérifie qu'au moins un des points appartiennent au segment
		if(xmin <= x1 && xmax >= x1 && ymin <= y1 && ymax >= y1)
			test = 1;

		if(xmin <= x2 && xmax >= x2 && ymin <= y2 && ymax >= y2)
			test = 1;

		if(test == 1)
			return 1;
	}

	return 0;
}

/************* Intersection entre deux carrés *************/
/* Vérifie s'il y a une intersection entre deux carrés. Regarde pour chaque extremité du carré	*
*  s'il est contenu dans l'autre carré. Si oui retourne 1 sinon retourne 0. Prend en paramètre 	*
*  quatres points : les deux extremités opposées de chaque carré				*/

int intersectionCarres (Point2D point1, Point2D point2, Point2D pointC1, Point2D pointC2) {

	int i;
	Point2D point;

	int xmin = ((point1.x) < (point2.x)) ? (point1.x) : (point2.x);
	int xmax = ((point1.x) > (point2.x)) ? (point1.x) : (point2.x);

	int ymin = ((point1.y) < (point2.y)) ? (point1.y) : (point2.y);
	int ymax = ((point1.y) > (point2.y)) ? (point1.y) : (point2.y);

	for(i = 0; i < 4; i++) {

		//Vérifie avec les quatres points du quad
		switch(i) {
			case 0 :
				point.x = pointC1.x; point.y = pointC1.y;
				break;
			case 1 :
				point.x = pointC1.x; point.y = pointC2.y;
				break;
			case 2 :
				point.x = pointC2.x; point.y = pointC2.y;
				break;
			case 3 :
				point.x = pointC2.x; point.y = pointC1.y;
				break;
			default :
				break;

		}

		if(point.x <= xmax && point.x >= xmin && point.y <= ymax && point.y >= ymin)
			return 1;

	}

	return 0;
}

/************* Intersection entre un carré et un disque *************/
/* Vérifie s'il y a une intersection entre un carré et un disque. Regarde pour chaque extremité du carré	*
*  s'il est contenu dans dans le cercle. Si oui retourne 1 sinon retourne 0. Prend en paramètre quatre points :	*
*  les deux extremités opposées du carré, le rayon du cercle et son centre.					*/

int intersectionCarreDisque (Point2D point1, Point2D point2, float rayon, Point2D origin) {

	int i;
	Point2D point;

	for(i = 0; i < 4; i++) {

		//Vérifie avec les quatres points du quad
		switch(i) {
			case 0 :
				point.x = point1.x; point.y = point1.y;
				break;
			case 1 :
				point.x = point1.x; point.y = point2.y;
				break;
			case 2 :
				point.x = point2.x; point.y = point2.y;
				break;
			case 3 :
				point.x = point2.x; point.y = point1.y;
				break;
			default :
				break;

		}

		if(((point.x - origin.x) * (point.x - origin.x)) + ((point.y - origin.y) * (point.y - origin.y)) - (rayon * rayon) <= 0)
			return 1;

	}

	return 0;
}
