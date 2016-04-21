#include <GL/freeglut.h>



void display()
{
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(800, 600);
	glutInit(&argc, argv);

	glutDisplayFunc(display);

	glutCreateWindow("Hello World");
	glutMainLoop();
}