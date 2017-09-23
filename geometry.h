#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include<vector>
#include<iostream>
#include<GL/glut.h>

using namespace std;

/**
@struct Point

Struct to facilitate manipulation of x and y coordinates.
*/
struct Point {
	float x, y;
};

extern Point p1;
extern Point p2;
extern vector<pair<Point,Point> > points;
extern vector<Point> intersectionPoints;
extern int click_counter;

float orientationTriangleArea(Point a, Point b, Point c);
int intersection(void);
void savePair(Point p1, Point p2);

#endif
