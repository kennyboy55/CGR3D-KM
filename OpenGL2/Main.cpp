#include <GL/freeglut.h>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float lastFrameTime = 0;

int width, height;
GLuint grassTexture, blocksTexture;

struct Camera
{
	float posX = 0;
	float posY = -4;
	float posZ = 0;
	float rotX = 0;
	float rotY = 0;
} camera;

bool keys[255];


void drawCube(int index)
{
	int rowNum = index / 16;
	int columnNum = index % 16;

	float part = (float)1 / 16;

	float row = rowNum * part;
	float column = columnNum * part;
	float rowEnd = row + part;
	float columnEnd = column + part;


	glBegin(GL_QUADS);
	glTexCoord2f(column, row); glVertex3f(-1, -1, -1);
	glTexCoord2f(column, rowEnd); glVertex3f(1, -1, -1);
	glTexCoord2f(columnEnd, rowEnd); glVertex3f(1, 1, -1);
	glTexCoord2f(columnEnd, row); glVertex3f(-1, 1, -1);

	glTexCoord2f(column, row); glVertex3f(-1, -1, 1);
	glTexCoord2f(column, rowEnd); glVertex3f(1, -1, 1);
	glTexCoord2f(columnEnd, rowEnd); glVertex3f(1, 1, 1);
	glTexCoord2f(columnEnd, row); glVertex3f(-1, 1, 1);

	glTexCoord2f(column, row); glVertex3f(-1, -1, -1);
	glTexCoord2f(column, rowEnd); glVertex3f(-1, 1, -1);
	glTexCoord2f(columnEnd, rowEnd); glVertex3f(-1, 1, 1);
	glTexCoord2f(columnEnd, row); glVertex3f(-1, -1, 1);

	glTexCoord2f(column, row); glVertex3f(1, -1, -1);
	glTexCoord2f(column, rowEnd); glVertex3f(1, 1, -1);
	glTexCoord2f(columnEnd, rowEnd); glVertex3f(1, 1, 1);
	glTexCoord2f(columnEnd, row); glVertex3f(1, -1, 1);

	glTexCoord2f(column, row); glVertex3f(-1, -1, -1);
	glTexCoord2f(column, rowEnd); glVertex3f(1, -1, -1);
	glTexCoord2f(columnEnd, rowEnd); glVertex3f(1, -1, 1);
	glTexCoord2f(columnEnd, row); glVertex3f(-1, -1, 1);

	glTexCoord2f(column, row); glVertex3f(-1, 1, -1);
	glTexCoord2f(column, rowEnd); glVertex3f(1, 1, -1);
	glTexCoord2f(columnEnd, rowEnd); glVertex3f(1, 1, 1);
	glTexCoord2f(columnEnd, row); glVertex3f(-1, 1, 1);
	glEnd();
}

void drawTree(int xlocation, int ylocation, int zlocation, int height)
{
	for (int z = zlocation; z <= zlocation+height; z += 2)
	{
		glPushMatrix();
		glTranslatef((float)xlocation, (float)z, (float)ylocation);
		drawCube(20);
		glPopMatrix();
	}


	for (int x = xlocation-(height/2); x <= xlocation+ (height / 2); x += 2)
	{
		for (int y = ylocation- (height / 2); y <= ylocation+ (height / 2); y += 2)
		{
			for (int z = zlocation + height -(height/3); z <= zlocation + height+(height / 3); z += 2)
			{
				glPushMatrix();
				glTranslatef((float)x, (float)z, (float)y);
				drawCube(53);
				glPopMatrix();
			}
		}
	}
}

void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width/height, 0.1, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, grassTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-30, -1, -30);
		glTexCoord2f(0, 8); glVertex3f( 30, -1, -30);
		glTexCoord2f(8, 8); glVertex3f( 30, -1,  30);
		glTexCoord2f(8, 0); glVertex3f(-30, -1,  30);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, blocksTexture);
	for (int x = -10; x <= 10; x += 5)
	{
		for (int y = -10; y <= 10; y += 5)
		{
			glPushMatrix();
			glTranslatef((float)x, 0.0f, (float)y);
			drawCube(21);
			glPopMatrix();
		}
	}

	for (int x = 12; x <= 22; x += 2)
	{
		for (int y = 12; y <= 22; y += 2)
		{
			for (int z = 1; z <= 22; z += 2)
			{
				glPushMatrix();
				glTranslatef((float)x, (float)z, (float)y);
				drawCube(1);
				glPopMatrix();
			}
		}
	}

	for (int x = 12; x <= 22; x += 2)
	{
				glPushMatrix();
				glTranslatef((float)x, 0.0f, 0.0f);
				drawCube(6);
				glPopMatrix();

	}

	drawTree(0, 0, 0,10);

	drawTree(-12, -12, 0, 5);
	drawTree(15, 15, 22, 10);
	drawTree(12, -12, 0, 6);

	//drawTree(-12, 12, 0, 50);
	
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void moveZ(float direction, float fac)
{
	camera.posZ += (fac * direction);
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
	if (keys['q']) moveZ(-1, deltaTime*speed);
	if (keys['e']) moveZ(1, deltaTime*speed);

	glutPostRedisplay();
}

void mousePassiveMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	//Cursor
	glutWarpPointer(width / 2, height / 2);
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Load Textures :: grass
	int width1, height1, bpp1;
	unsigned char* imgData1 = stbi_load("grass.jpg", &width1, &height1, &bpp1, 4);

	glGenTextures(1, &grassTexture);
	glBindTexture(GL_TEXTURE_2D, grassTexture);

	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width1,		//width
		height1,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData1);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(imgData1);


	//Load Textures :: blocks
	int width2, height2, bpp2;
	unsigned char* imgData2 = stbi_load("terrain.png", &width2, &height2, &bpp2, 4);

	glGenTextures(1, &blocksTexture);
	glBindTexture(GL_TEXTURE_2D, blocksTexture);

	glTexImage2D(GL_TEXTURE_2D,
		0,		//level
		GL_RGBA,		//internal format
		width2,		//width
		height2,		//height
		0,		//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData2);		//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData2);


	glutMainLoop();


	return 0;
}