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
#include "geometry/Light.h"
#include "raytracer/Scene.h"

void SimpleRaytracing(const Scene* scene, SDL_Surface* framebuffer) {
	
	int i, j;
	Point3D pixelPosition;
	Ray3D ray;
	Intersection intersection;
	Color3f bgColor = ColorRGB(1.0, 1.0, 1.0);

	for(i = 0; i < framebuffer->w; i++) {

		for(j = 0; j < framebuffer->h; j++) {

			pixelPosition = PointXYZ(-1+(2*i)/(float)(framebuffer->w-1.0), 1-(2*j)/(float)(framebuffer->h-1.0), -1.0);
			ray.direction = Normalize(Vector(ray.origine, pixelPosition));

			if(ThrowRayOnScene(ray, scene, &intersection) == 1) {

				PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, convert_f32_to_uc8(intersection.color.r), convert_f32_to_uc8(intersection.color.g), convert_f32_to_uc8(intersection.color.b)));
			}
			else {
				PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, convert_f32_to_uc8(bgColor.r), convert_f32_to_uc8(bgColor.g), convert_f32_to_uc8(bgColor.b)));
			}

		}

	}

}

void BetaLambertRaytracing(const Scene* scene, SDL_Surface* framebuffer) {
	
	int i, j, l;
	Point3D pixelPosition;
	Color3f pixelColor;
	Ray3D ray;
	Intersection intersection;
	Vector3D IL; /*(vectorIntersectionToLight)*/
	Color3f bgColor = ColorRGB(0.0, 0.0, 0.0);

	for(i = 0; i < framebuffer->w; i++) {

		for(j = 0; j < framebuffer->h; j++) {

			pixelPosition = PointXYZ(-1+(2*i)/(float)(framebuffer->w-1.0), 1-(2*j)/(float)(framebuffer->h-1.0), -1.0);
			ray.direction = Normalize(Vector(ray.origine, pixelPosition));

			if(ThrowRayOnScene(ray, scene, &intersection) == 1) {

				pixelColor = MultColor(intersection.color, 0.1);

				for(l = 0; l < scene->nbLight; l++) {
					
					IL = Vector(intersection.position, scene->light[l].position);
					float diffuseCoef = DotProduct(intersection.normal, Normalize(IL))/ (Norm(IL) * Norm(IL));
					Color3f colorTmp = MultColor(MultColors(intersection.color, scene->light[l].color), diffuseCoef);
					pixelColor.r += max(0.0, colorTmp.r);
					pixelColor.g += max(0.0, colorTmp.g);
					pixelColor.b += max(0.0, colorTmp.b);

					PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, convert_f32_to_uc8(pixelColor.r), convert_f32_to_uc8(pixelColor.g), convert_f32_to_uc8(pixelColor.b)));
				}

			}
			else {
				PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, convert_f32_to_uc8(bgColor.r), convert_f32_to_uc8(bgColor.g), convert_f32_to_uc8(bgColor.b)));
			}

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
