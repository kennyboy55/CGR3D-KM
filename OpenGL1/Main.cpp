#include <iostream>
#include <GL/freeglut.h>

using namespace std;
void obj_cube2(void);
float rotation = 0;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.7, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.5f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -3,
		0, 0, 0,
		0, 1, 0);

	glRotatef(rotation, 0, 1, 0);
	glRotatef(rotation/2, 0, 0, 1);
	obj_cube2();

	glutSwapBuffers();
}

void idle()
{
	rotation += 0.1f;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

int main(int argc, char *argv[]) 
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);

	glutInit(&argc, argv);
	glutCreateWindow("Hello World");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

void obj_cube2()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.7f, 1.0f);
	glVertex3f(0, 0, 0);
	glColor3f(0.5, 1, 0.1);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 1, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 1, 0);
	glColor3f(0.1, 1, 0.1);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.5, 0.1);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.5, 0.5);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.1, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.1, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.1, 0.5);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 1, 0.5);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0.5);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.3, 0.8);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glEnd();

}