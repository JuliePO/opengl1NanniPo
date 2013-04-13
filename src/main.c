#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "sdl_tools.h"
#include "geometry/Vector3D.h"
#include "geometry/Point3D.h"
#include "geometry/Color3f.h"
#include "geometry/Ray3D.h"
#include "geometry/Intersection.h"
#include "geometry/Union.h"
#include "geometry/Shape.h"
#include "raytracer/Scene.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
static const unsigned int BIT_PER_PIXEL = 32;

int main(int argc, char** argv) {

   	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        	fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}
    
    	SDL_Surface* screen = NULL;
    	if(NULL == (screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
        	SDL_DOUBLEBUF))) {
        	fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}
    	SDL_WM_SetCaption("Raytracing powa :D", NULL);
    
    	/* Création d'une surface SDL dans laquelle le raytracer dessinera */
    	SDL_Surface* framebuffer = NULL;
    	if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, 
        	WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
        	fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        	return EXIT_FAILURE;
    	}

	/*Point3D point1 = PointXYZ(1.0, 2.0, 3.0);
	Point3D point2 = PointXYZ(4.0, 5.0, 6.0);
	Vector3D vector1 = VectorXYZ(-1, -2, 3);
	Vector3D vector2 = VectorXYZ(1, 1, 1);
	Vector3D vector3 = Vector(point1, point2);

	printf("vector3 : %f %f %f \n", vector3.x, vector3.y, vector3.z);
	printf("vector1 : %f %f %f \n", vector1.x, vector1.y, vector1.z);

	Point3D point3 = PointPlusVector(point1, vector1);
	printf("point3 : %f %f %f \n", point3.x, point3.y, point3.z);
	
	Vector3D vector4 = AddVectors(vector1, vector2);
	printf("vector4 : %f %f %f \n", vector4.x, vector4.y, vector4.z);

	vector4 = SubVectors(vector1, vector2);
	printf("vector4 : %f %f %f \n", vector4.x, vector4.y, vector4.z);

	vector4 = MultVector(3.0, vector1);
	printf("vector4 : %f %f %f \n", vector4.x, vector4.y, vector4.z);

	vector4 = DivVector(2.0, vector1);
	printf("vector4 : %f %f %f \n", vector4.x, vector4.y, vector4.z);

	printf("dot %f \n", DotProduct(vector1, vector2));
	printf("norm vector1 : %f \n", Norm(vector1));

	vector4 = Normalize(vector1);
	printf("vector4 : %f %f %f \n", vector4.x, vector4.y, vector4.z);

	unsigned char test;
	test = convert_f32_to_uc8 (0.7);
	printf("conversion de 0.7 en unsigned char : %d \n", test);

	Color3f rouge = ColorRGB(1, 0, 0);
	Color3f vert = ColorRGB(0, 1, 0);
	Color3f bleu = ColorRGB(0, 0, 1);

	Color3f color1 = AddColors(rouge, bleu);
	printf("addition : %f %f %f \n", color1.r, color1.g, color1.b);

	color1 = SubColors(rouge, bleu);
	printf("soustraction : %f %f %f \n", color1.r, color1.g, color1.b);

	color1 = MultColors(rouge, bleu);
	printf("multiplication : %f %f %f \n", color1.r, color1.g, color1.b);

	color1 = DivColors(rouge, bleu);
	printf("division : %f %f %f \n", color1.r, color1.g, color1.b);

	Intersection inter;
	testSphereInter(..., &inter);*/

	Scene scene;
	scene.nbObjects = 0;

	Point3D centre1 = PointXYZ(1.0, 2.0, -5.0);
	Color3f rouge = ColorRGB(1, 0, 0);

	Sphere sphere1;
	Shape shape1;
	shape1.sphere = sphere1;
	shape1.type = SPHERE_SHAPE;
	sphere1 = SphereInit(centre1, 1.5, rouge);

	AddSceneShape(&scene, shape1);
	
    
    	int loop = 1;
    	while(loop) {
        	/* Nettoyage du framebuffer (remplir un rectangle) */
        	SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));
        
        	/* Placer ici le code de dessin */
		/*colorier un pixel de framebuffer*/
        	/*PutPixel(framebuffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SDL_MapRGB(framebuffer->format, 255, 255, 255));
		/* 300 et 400 => (410, 290) (410, 310) (390, 310) (390, 290) */
		/*int i, j, color=255;
		for(i=390; i <= 410; i++){
			for(j=290; j <= 310; j++) {
				PutPixel(framebuffer, i, j, SDL_MapRGB(framebuffer->format, color, color, color));
				color -= 10;
			}
			color = 255;
		}*/

		SimpleRaytracing(&scene, &framebuffer);
        
        	/* On copie le framebuffer à l'écran */
        	SDL_BlitSurface(framebuffer, NULL, screen, NULL);
        
        	SDL_Flip(screen);
    
        	SDL_Event e;
        	while(SDL_PollEvent(&e)) {
            		if(e.type == SDL_QUIT) {
            			loop = 0;
            			break;
        		}
        	}
    	}
  
    	SDL_Quit();
    
    	return EXIT_SUCCESS;
}
