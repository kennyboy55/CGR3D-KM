#include <iostream>
#include <string>
#include <GL/freeglut.h>

/* Prototypes */
void obj_flag(void);
void obj_cube(float clr);
void obj_cube2(void);
void set_view(int);
void draw_string(std::string, int, int);
void calculateFPS(void);


/* Variables */
float rotation = 0;
float keyrotationx = 0;
float keyrotationy = 0;
float color = 0;
int width = 800;
int height = 600;
bool wireframe = false;
bool persp = true;
bool rotatec = true;

int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
int fps = 0;

float cameraRot = 0;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.7, 0.0, 1.0);

	set_view(0);

	if(rotatec)
		cameraRot += 0.001f;

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

	//Cube 1
	float tempx = keyrotationx;
	float tempy = keyrotationy;

	glRotatef(tempy, 1, 0, 0);
	glRotatef(tempx, 0, 1, 0);
	obj_cube(1.0f);
	glRotatef(tempy, -1, 0, 0);
	glRotatef(tempx, 0, -1, 0);


	//overlay
	set_view(1);
	std::string str0 = "FPS: " + std::to_string(fps);
	std::string str1 = "Wireframe: " + std::string(wireframe ? "On" : "Off");
	std::string str2 = "Projectie: " + std::string(persp ? "Perspective" : "Ortho");
	std::string str3 = "Rotation: " + std::string(rotatec ? "On" : "Off");

	draw_string(str0, 10, 30);
	draw_string(str1, 10, 60);
	draw_string(str2, 10, 90);
	draw_string(str3, 10, 120);

	frameCount++;

	glutSwapBuffers();
}

void draw_string(std::string s, int x, int y)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(x, y, 0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)s.c_str());
}

void set_view(int view)
{
	if (view == 0)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (persp)
			gluPerspective(90, (float)width / height, 0.5f, 20.0f);
		else
			glOrtho(-8, 8, -8, 8, 0.5f, 20.0f);

		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cos(cameraRot) * 5, 5, sin(cameraRot) * 5,
			0, 0, 0,
			0, 1, 0);
	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -0.5f, 20.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

void idle()
{
	rotation += 0.1f;
	glutPostRedisplay();
	calculateFPS();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	else if (key == 32)
		persp = !persp;
	else if (key == 114)
		rotatec = !rotatec;
	else if (key == 108)
		wireframe = !wireframe;
}

void specialkeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		keyrotationy += 2.0f;
		break;
	case GLUT_KEY_DOWN:
		keyrotationy -= 2.0f;
		break;
	case GLUT_KEY_LEFT:
		keyrotationx -= 2.0f;
		break;
	case GLUT_KEY_RIGHT:
		keyrotationx += 2.0f;
		break;
	}
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

void calculateFPS()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		fps = frameCount / (timeInterval / 1000.0f);
		previousTime = currentTime;
		frameCount = 0;
	}
}

int main(int argc, char *argv[]) 
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);

	glutInit(&argc, argv);
	glutCreateWindow("Cubes");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutPassiveMotionFunc(mousemoved);
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