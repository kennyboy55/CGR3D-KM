#include <iostream>
#include <GL/freeglut.h>

using namespace std;

/* Prototypes */
void obj_flag(void);
void obj_cube(float clr);
void obj_cube2(void);

float rotation = 0;
float color = 0;
int width = 800;
int height = 600;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.7, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)width/height, 0.5f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, -5,
		0, 0, 0,
		0, 1, 0);

	//Cube 1
	glRotatef(rotation, 0, 1, 0);
	obj_cube(1.0f);
	glRotatef(rotation, 0, -1, 0);

	//Cube 2
	glTranslatef(3.0f, 0, 0);
	glRotatef(rotation / 2, 0, 0, 1);
	obj_cube(1.0f);
	glRotatef(rotation / 2, 0, 0, -1);
	glTranslatef(-3.0, 0, 0);

	//Cube 3
	glTranslatef(-3.0f, 0, 0);
	glRotatef(rotation / 2, 1, 0, 0);
	obj_cube(1.0f);
	glRotatef(rotation / 2, -1, 0, 0);
	glTranslatef(3.0f, 0, 0);

	//Cube 4
	glTranslatef(0, 0, 3.0f);
	glRotatef(rotation / 2, 1, 1, 0);
	obj_cube(color);
	glRotatef(rotation / 2, -1, -1, 0);
	glTranslatef(0, 0, -3.0f);

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

void mousemoved(int x, int y)
{
	color = (x / 100);
}

void resize(int w, int h)
{
	width = w;
	height = w;
}

int main(int argc, char *argv[]) 
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);

	glutInit(&argc, argv);
	glutCreateWindow("Hello World");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mousemoved);
	glutReshapeFunc(resize);

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

void obj_cube(float clr)
{
	//Side 1 : Green
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f / clr, 0.0f);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glColor3f(0.5f, 1.0f / clr, 0.5f);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();

	//Side 2 : Red
	glBegin(GL_QUADS);
	glColor3f(1.0f / clr, 0.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glColor3f(1.0f / clr, 0.5f, 0.5f);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glEnd();

	//Side 3 : Blue
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f / clr);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glColor3f(0.5f, 0.5f, 1.0f / clr);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	//Side 4 : Yellow
	glBegin(GL_QUADS);
	glColor3f(1.0f / clr, 1.0f / clr, 0.0f);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glColor3f(1.0f / clr, 1.0f / clr, 0.5f);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glEnd();

	//Side 5 : Purple
	glBegin(GL_QUADS);
	glColor3f(1.0f / clr, 0.0f, 1.0f / clr);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glColor3f(1.0f / clr, 0.5f, 1.0f / clr);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glEnd();

	//Side 6 : Light blue
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f / clr, 1.0f / clr);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glColor3f(0.5f, 1.0f / clr, 1.0f / clr);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glEnd();
}

void obj_flag()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.7f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 1, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glEnd();
}