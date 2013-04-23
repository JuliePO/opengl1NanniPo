#ifndef LDR_LIGHT___
#define LDR_LIGHT___

#include "geometry/Point3D.h"
#include "geometry/Color3f.h"

typedef struct struct_light {
	Point3D position;
	Color3f color;
}Light;

#endif
