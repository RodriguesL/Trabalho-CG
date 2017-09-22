#include<GL/glut.h>
#include<vector>
#include<iostream>

using namespace std;

int click_counter = 0;
int intersectionCounter = 0;

struct Point
{
	int x, y;
};

Point p1, p2;
vector<pair<Point,Point> > points;
vector<Point> intersectionPoints;

int intersection() {
	int det;
	Point ip;
	float s, t;
	for (int i = 0; i < points.size() - 1; i++) {
		for (int j = 0; j < points.size(); i++) {

		Point a = points[i].first;
		Point b = points[i].second;
		Point c = points[j].first;
		Point d = points[j].second;

		det = (d.x - c.x) * (b.y - a.y)  -  (d.y - c.y) * (b.x - a.x);

		if (det == 0) return 0;

		s = ((d.x - c.x) * (c.y - a.y) - (d.y - c.y) * (c.x - a.x))/ det ;
		t = ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x))/ det ;

		ip.x = a.x + (b.x-a.x)*s;
	    ip.y = a.y + (b.y-a.y)*s;

	    cout << "ip.x = " << ip.x << " ip.y = " << ip.y << "\n";	    
	    intersectionPoints.push_back(ip);
	    intersectionCounter++;
    	}
    }
	return 1;
}

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
        glViewport(0, 0, w, h);
}

void savePair(Point p1, Point p2) {
	points.push_back(make_pair(p1, p2));
}

void myMouse (int button, int state, int x, int y) {
	bool canSave = false;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (click_counter == 0) {
			p1.x = x;
			p1.y = y;
			cout << "x1 = " << p1.x << ", y1 = " << p1.y << "\n";
			click_counter++;
		}

		else if (click_counter == 1) {
			p2.x = x;
			p2.y = y;
			cout << "x2 = " << p2.x << ", y2 = " << p2.y << "\n";
			click_counter = 0;
			canSave = true;
		}
	}
	if (canSave) savePair(p1, p2);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 640.0, 480.0, 0.0);
	for (int i = 0; i < points.size(); i++) {
		glBegin(GL_LINES);
			glColor3f(255.0, 255.0, 255.0);
			glVertex3f(points[i].first.x, points[i].first.y, 0.0);
			glVertex3f(points[i].second.x, points[i].second.y, 0.0);
		glEnd();
	}
	for (int i = 0; i < intersectionPoints.size(); i++) {
		cout << "x_int = " << intersectionPoints[i].x << " y_int = " << intersectionPoints[i].y << "\n";
		glBegin(GL_POINTS);
			glColor3f(255.0, 0.0, 0.0);
			glPointSize(300.0);
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
	glutInitWindowSize(640,480);
	glutCreateWindow("Trabalho 1 - Computação Gráfica I");
	glutMouseFunc(myMouse);
	intersection();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
	return 0;
}

