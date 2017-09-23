/**
@file geometry.cpp

Trabalho 1 de Computação Gráfica I
@author Lucas Rodrigues Teixeira Nunes
*/

#include "geometry.h"

/**
Computes twice the signed area of the orientation triangle.
If it is oriented counterclockwise, the area is positive. Otherwise, it is negative.
@fn float orientationTriangleArea(Point a, Point b, Point c)
@param a a Point struct
@param b a Point struct
@param c a Point struct
@return Two times the area of the orientation triangle
*/
float orientationTriangleArea(Point a, Point b, Point c)
{
    return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}

/**
Computes if there is an intersection between all pairs of segments.

If the intersection exists, its coordinates are calculated. It uses the orientation method to determine whether the points are on different sides
@fn void intersection(void)
*/
int intersection(void) {
	int size = points.size();
	for (int i = 0; i < size; i++) {
			Point a = points[i].first;
			Point b = points[i].second;
			Point c = points[size-1].first;
			Point d = points[size-1].second;
			Point p;

		    // signs of areas correspond to which side of ab points c and d are
		    float a1 = orientationTriangleArea(a,b,d); // Compute winding of abd (+ or -)
		    float a2 = orientationTriangleArea(a,b,c); // To intersect, must have sign opposite of a1

		    // If c and d are on different sides of ab, areas have different signs
		    if(a1 * a2 < 0.0f) {// require unsigned x & y values. 
		        float a3 = orientationTriangleArea(c,d,a); // Compute winding of cda (+ or -)
		        float a4 = a3 + a2 - a1; // Since area is constant a1 - a2 = a3 - a4, or a4 = a3 + a2 - a1

		        // Points a and b on different sides of cd if areas have different signs
		        if(a3 * a4 < 0.0f) {
		        
		            // Segments intersect. Find intersection point along L(t) = a + t * (b - a).
		            float t = a3 / (a3 - a4);
		            p.x = a.x + t * (b.x - a.x);
		            p.y = a.y + t * (b.y - a.y);
		            intersectionPoints.push_back(p); // the point of intersection is saved so it can be drawn later
		           
		        }
		    }
		
	}
}

/**
Saves a pair of points (starting point and end point) of a segment.

It saves the pair of points in a vector.
@fn void savePair(Point p1, Point p2)
@param p1 a Point struct
@param p2 a Point struct
*/
void savePair(Point p1, Point p2) {
	points.push_back(make_pair(p1, p2));
}