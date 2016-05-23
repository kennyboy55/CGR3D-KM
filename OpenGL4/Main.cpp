#include <GL/freeglut.h>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float lastFrameTime = 0;

int width, height;


struct Camera
{
	float posX = 0;
	float posY = -4;
	float rotX = 0;
	float rotY = 0;
} camera;

bool keys[255];

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
	float r, g, b, a;
};

std::vector<Vertex> cubeVertices;


void drawCube()
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex),	((float*)cubeVertices.data()) + 0);
	glNormalPointer(GL_FLOAT, sizeof(Vertex),		((float*)cubeVertices.data()) + 3);
	glColorPointer(4, GL_FLOAT, sizeof(Vertex),		((float*)cubeVertices.data()) + 6);
	glDrawArrays(GL_QUADS, 0, cubeVertices.size());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}


void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width/height, 0.1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, 0, camera.posY);

	float pos[4] = { 0.5, 1, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	glColor3f(0.1f, 1.0f, 0.2f);
	glBegin(GL_QUADS);
		glVertex3f(-15, -1, -15);
		glVertex3f( 15, -1, -15);
		glVertex3f( 15, -1,  15);
		glVertex3f(-15, -1,  15);
	glEnd();

	for (int x = -10; x <= 10; x += 5)
	{
		for (int y = -10; y <= 10; y += 5)
		{
			glPushMatrix();
			glTranslatef((float)x, 0.0f, (float)y);
			drawCube();
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);

	glutPostRedisplay();
}

bool justMoved = false;
void mousePassiveMotion(int x, int y)
{
	if (justMoved)
	{
		justMoved = false;
		return;
	}
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
		justMoved = true;
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	keys[key] = true;
}

void keyboardUp(unsigned char key, int,int)
{
	keys[key] = false;
}

int main(int argc, char* argv[])
{
	width = 800;
	height = 600;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);



	cubeVertices.push_back(Vertex{ -1, -1, -1, 0,0,1, 1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1,  1, -1, 0,0,1, 1,1,1,1 });
	cubeVertices.push_back(Vertex{  1,  1, -1, 0,0,1, 1,1,1,1 });
	cubeVertices.push_back(Vertex{  1, -1, -1, 0,0,1, 1,1,1,1 });

	cubeVertices.push_back(Vertex{ -1, -1,  1, 0,0,-1, 1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1,  1,  1, 0,0,-1, 1,1,1,1 });
	cubeVertices.push_back(Vertex{  1,  1,  1, 0,0,-1, 1,1,1,1 });
	cubeVertices.push_back(Vertex{  1, -1,  1, 0,0,-1, 1,1,1,1 });

	cubeVertices.push_back(Vertex{ -1,  -1, -1,		0,-1,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1,  -1,  1,		0,-1,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{  1,  -1,  1,		0,-1,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{  1,  -1, -1,		0,-1,0,		1,1,1,1 });

	cubeVertices.push_back(Vertex{ -1,  1, -1,		0,1,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1,  1,  1,		0,1,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ 1,  1,  1,		0,1,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ 1,  1, -1,		0,1,0,		1,1,1,1 });

	cubeVertices.push_back(Vertex{ -1, -1, -1,		-1,0,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1, -1,  1,		-1,0,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1,  1,  1,		-1,0,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ -1,  1, -1,		-1,0,0,		1,1,1,1 });

	cubeVertices.push_back(Vertex{ 1, -1, -1,		1,0,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ 1, -1,  1,		1,0,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ 1,  1,  1,		1,0,0,		1,1,1,1 });
	cubeVertices.push_back(Vertex{ 1,  1, -1,		1,0,0,		1,1,1,1 });




	glutWarpPointer(width / 2, height / 2);

	glutMainLoop();


	return 0;
}