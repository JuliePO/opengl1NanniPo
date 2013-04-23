#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "geometry/Point3D.h"
#include "geometry/Color3f.h"
#include "geometry/Vector3D.h"
#include "geometry/Ray3D.h"
#include "geometry/Sphere.h"
#include "geometry/Cube.h"
#include "geometry/Union.h"
#include "geometry/Intersection.h"
#include "geometry/Shape.h"

#define epsilon 10E-15

int TestRaySphereIntersection(Ray3D ray, Sphere sphere,Intersection* intersection) {

	/*float A = ((ray->direction->x)*(ray->direction->x)) + ((ray->direction->y)*(ray->direction->y)) + ((ray->direction->z)*(ray->direction->z))
	float B = 2*(((ray->direction->x)*((ray->origine->x) - (sphere->center->x))) + ((ray->direction->y)*((ray->origine->y) - (sphere->center->y))) + ((ray->direction->y)*((ray->origine->y) - (sphere->center->y))));*/

	float A = DotProduct(ray.direction, ray.direction);
	Vector3D RoC = Vector(sphere.center, ray.origine);
	float B = DotProduct(RoC, ray.direction) * 2.0;
	float C = DotProduct(RoC, RoC) - sphere.radius*sphere.radius;

	float delta = B*B - 4*A*C;
	if(delta < 0) return 0;

	float t1 = (-B + sqrt(delta)) / 2*A;
	float t2 = (-B - sqrt(delta)) / 2*A;

	float tmin = (t1 < t2) ? t1 : t2;
	float tmax = (t1 > t2) ? t1 : t2;

	if(tmax < 0) return 0;
	float t;
	if(tmin > 0) t = tmin; else t = tmax;


	intersection->position = PointPlusVector(ray.origine, MultVector(t, ray.direction));
	intersection->normal = Normalize(Vector(sphere.center, intersection->position));
	intersection->color = sphere.color;

	return 1;
}

int TestRayShapeIntersection(Ray3D ray, Shape shape,Intersection* intersection) {

	switch(shape.type) {

		case SPHERE_SHAPE:
			return TestRaySphereIntersection(ray, shape.sphere, intersection);
		break;

		case CUBE_SHAPE:
			printf("Cube yeah !!\n");
		break;

		default :
			return 0;
		break;
	}

	return 0;
}
