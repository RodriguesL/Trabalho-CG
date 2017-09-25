/**
@file main.cpp

Trabalho 1 de Computação Gráfica I
@author Lucas Rodrigues Teixeira Nunes
*/

#include "geometry.h"

//Global variables
float width = 640;
float height = 480;

int click_counter = 0;

Point p1, p2;

vector<pair<Point,Point> > points;
vector<Point> intersectionPoints;

/**
Resizes the viewport when the window size changes.

@fn void changeSize(int w, int h)
@param w an integer variable
@param h an integer variable
*/
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
           h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	width = w;
	height = h;
    glViewport(0, 0, w, h);
}

/**
Callback function that gets mouse coordinates and button state.

@fn void myMouse (int button, int state, int x, int y)
@param button an integer variable
@param state an integer variable
@param x an integer variable
@param y an integer variable
*/
void myMouse (int button, int state, int x, int y) {
	bool canSave = false; //Control variable to decide if the pair of points can be saved

	//When left button is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//When it is the first click
		if (click_counter == 0) {
			p1.x = x;
			p1.y = y;
			cout << "x1 = " << p1.x << ", y1 = " << p1.y << "\n";
			click_counter++;
		}
		//Or when it is the second click
		else if (click_counter == 1) {
			p2.x = x;
			p2.y = y;
			cout << "x2 = " << p2.x << ", y2 = " << p2.y << "\n";
			click_counter = 0;
			canSave = true;
		}
	}
	//If there were two clicks, save the pair of points to draw the segment
	if (canSave) savePair(p1, p2);
}

/**
Callback function to render OpenGL scene and draw the segments and intersections.

@fn void renderScene(void)
*/
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, width, height, 0.0);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    //For all points coordinates added by the mouse, draw the lines
	for (int i = 0; i < points.size(); i++) {
		glBegin(GL_LINES);
			glColor3f(255.0, 255.0, 255.0);
			glVertex3f(points[i].first.x, points[i].first.y, 0.0);
			glVertex3f(points[i].second.x, points[i].second.y, 0.0);
		glEnd();
	}
	intersection(); //Check if there are intersections
	//For all intersecting points found between the last drawn line and the lines that were already drawn
	for (int i = 0; i < intersectionPoints.size(); i++) {
		glPointSize(7.0);
		glBegin(GL_POINTS);
			glColor3f(255.0, 0.0, 0.0);
			glVertex3f(intersectionPoints[i].x, intersectionPoints[i].y, 0.0);
		glEnd();
	}
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width,height);
	glutCreateWindow("Trabalho 1 - Computação Gráfica I - Lucas Rodrigues");
	glutMouseFunc(myMouse);
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutMainLoop();
	return 0;
}

