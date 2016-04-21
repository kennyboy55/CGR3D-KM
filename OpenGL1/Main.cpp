#include <iostream>
#include <GL/freeglut.h>

using namespace std;

void display() {
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);

	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}