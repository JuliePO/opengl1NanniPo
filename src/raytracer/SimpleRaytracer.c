#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sdl_tools.h"
#include "geometry/Point3D.h"
#include "geometry/Ray3D.h"
#include "geometry/Color3f.h"
#include "geometry/Vector3D.h"
#include "geometry/Intersection.h"
#include "geometry/Union.h"
#include "geometry/Shape.h"
#include "raytracer/Scene.h"

void SimpleRaytracing(const Scene* scene, SDL_Surface* framebuffer) {
	
	int i, j;
	Point3D pixelPosition;
	Ray3D ray;
	Intersection intersection;
	Color3f bgColor = ColorRGB(0.0, 0.0, 0.0);

	for(i = 0; i < framebuffer->w; i++) {

		for(j=0; j < framebuffer->h; j++) {

			pixelPosition = PointXYZ(-1+2*i/(float)(framebuffer->w - 1.0), 1-2*i/(float)(framebuffer->h - 1.0), -1.0);
			ray.origine = PointXYZ(0.0, 0.0, 0.0);
			ray.direction = Normalize(Vector(ray.origine, pixelPosition));

			ThrowRayOnScene(ray, scene, &intersection);
	
			if(ThrowRayOnScene(ray, scene, &intersection) == 1)
				PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, intersection.color.r, intersection.color.g, intersection.color.b));
			else
				PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, bgColor.r, bgColor.g, bgColor.b));

		}

	}

}


/* Creer une scene
faire un include de tous les .h scene, raytracer
avant boucle principale évenement déclare la scène
dire nbobject = 0
faire objet de type sphere qui s'appelle sphere dont la position (1, 2, -5) avec un rayon de 1,5
la couleur ce que l'on veut 
appelle simpleraytracer qui prend en parametre la scène et framebuffer*/
