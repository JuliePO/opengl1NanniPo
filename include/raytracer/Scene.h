#ifndef LDR_SCENE_3D___
#define LDR_SCENE_3D___

#include "geometry/Light.h"
#include "geometry/Union.h"

#define SCENE_NB_OBJECT_MAX 10
#define SCENE_NB_LIGHT_MAX 10

typedef struct struct_scene {

	Shape objects[SCENE_NB_OBJECT_MAX];
	unsigned int nbObjects;

	Light light[SCENE_NB_LIGHT_MAX];
	unsigned int nbLight;
	/* lumiere, camera*/
	
}Scene;

void AddSceneShape(Scene*, Shape);
void AddSceneLight(Scene*, Light);
int ThrowRayOnScene(Ray3D, const Scene*, Intersection*);

#endif
