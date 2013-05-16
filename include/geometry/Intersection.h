#ifndef ITD_INTERSECTION_H_
#define ITD_INTERSECTION_H_

#include "geometry/Point2D.h"
#include "geometry/Vector2D.h"

/************* Appel de fonction *************/
int intersectionPointSegment (Point2D, Point2D, Point2D);
Point2D intersectionSegments (Point2D, Point2D, Point2D, Point2D);
Point2D intersectionSegmentCercle (Point2D, Point2D, Point2D, float);
int intersectionCarres (Point2D, Point2D, Point2D, Point2D);
int intersectionCarreDisque (Point2D, Point2D, float, Point2D);

#endif
