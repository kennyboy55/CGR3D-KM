#include <GL/freeglut.h>
#include <cstdio>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

float lastFrameTime = 0;

int width, height;
GLuint blocksTexture;

const int worldWidth = 32;
const int worldDepth = 32;
const int worldHeight = 8;
const int blockSize = 2;

struct Camera
{
	float posX = -worldWidth*blockSize / 2;
	float posZ = -worldDepth*blockSize / 2;
	float posY = -worldHeight*blockSize;
	float rotX = 0;
	float rotY = 0;
} camera;

struct Block 
{
	int textureTop;
	int textureSide;
};

Block world[worldWidth][worldDepth][worldHeight];

bool keys[255];

void generateWorld() {

	for (int x = 0; x < worldWidth; x++)
	{
		for (int z = 0; z < worldDepth; z++)
		{
			float heigth = stb_perlin_noise3((1.0f/(float)worldWidth)*(float)x, (1.0f / (float)worldDepth)*(float)z, 0);
			int heightInt = (int)(height * 8);
			std::cout << height << " - " << heightInt << std::endl;

			for (int y = 0; y < worldHeight; y++)
			{
				if (y < worldHeight / 2)
					world[x][z][y] = Block{ 1, 1};
				else if (y < (heightInt + worldHeight / 2))
					world[x][z][y] = Block{ 2, 2 };
				else if (y == (heightInt + worldHeight/2))
					world[x][z][y] = Block{ 0, 3 };
				else
					world[x][z][y] = Block{ -1, -1 };
			}
		}
	}
}

void drawCube(int top, int sides)
{
	int rowNum = sides / 16;
	int columnNum = sides % 16;

	float part = (float)1 / 16;

	float row = rowNum * part;
	float column = columnNum * part;
	float rowEnd = row + part;
	float columnEnd = column + part;

	glBegin(GL_QUADS);

	glColor4f(1.0, 1.0, 1.0, 1.0);

	//Side blockSize
	glTexCoord2f(column, rowEnd);		glVertex3f(0, 0, 0);		//Linksonder
	glTexCoord2f(columnEnd, rowEnd);	glVertex3f(blockSize, 0, 0);		//Rechtsonder
	glTexCoord2f(columnEnd, row);		glVertex3f(blockSize, blockSize, 0);		//Rechtsboven
	glTexCoord2f(column, row);			glVertex3f(0, blockSize, 0);		//Linksboven

																	//Side 2
	glTexCoord2f(column, rowEnd);		glVertex3f(0, 0, blockSize);
	glTexCoord2f(columnEnd, rowEnd);	glVertex3f(blockSize, 0, blockSize);
	glTexCoord2f(columnEnd, row);		glVertex3f(blockSize, blockSize, blockSize);
	glTexCoord2f(column, row);			glVertex3f(0, blockSize, blockSize);

	//Side 3
	glTexCoord2f(column, rowEnd);		glVertex3f(0, 0, 0);
	glTexCoord2f(column, row);			glVertex3f(0, blockSize, 0);
	glTexCoord2f(columnEnd, row);		glVertex3f(0, blockSize, blockSize);
	glTexCoord2f(columnEnd, rowEnd);	glVertex3f(0, 0, blockSize);

	//Side 4
	glTexCoord2f(column, rowEnd);		glVertex3f(blockSize, 0, 0);
	glTexCoord2f(column, row);			glVertex3f(blockSize, blockSize, 0);
	glTexCoord2f(columnEnd, row);		glVertex3f(blockSize, blockSize, blockSize);
	glTexCoord2f(columnEnd, rowEnd);	glVertex3f(blockSize, 0, blockSize);

	if (top == -1)
	{
		glEnd();
		return;
	}

	//Different textures
	rowNum = top / 16;
	columnNum = top % 16;

	row = rowNum * part;
	column = columnNum * part;
	rowEnd = row + part;
	columnEnd = column + part;


	//Bottom
	glTexCoord2f(column, row);			glVertex3f(0, 0, 0);
	glTexCoord2f(column, rowEnd);		glVertex3f(blockSize, 0, 0);
	glTexCoord2f(columnEnd, rowEnd);	glVertex3f(blockSize, 0, blockSize);
	glTexCoord2f(columnEnd, row);		glVertex3f(0, 0, blockSize);

	//Top
	glTexCoord2f(column, row);			glVertex3f(0, blockSize, 0);
	glTexCoord2f(column, rowEnd);		glVertex3f(blockSize, blockSize, 0);
	glTexCoord2f(columnEnd, rowEnd);	glVertex3f(blockSize, blockSize, blockSize);
	glTexCoord2f(columnEnd, row);		glVertex3f(0, blockSize, blockSize);
	glEnd();
}

void drawCube(int texture)
{
	drawCube(texture, texture);
}

void drawTree(int xlocation, int ylocation, int zlocation, int height)
{
	for (int z = zlocation; z <= zlocation+height; z += blockSize)
	{
		glPushMatrix();
		glTranslatef((float)xlocation, (float)z, (float)ylocation);
		drawCube(21, 20);
		glPopMatrix();
	}

	for (int x = xlocation-(height/2); x <= xlocation+ (height / 2); x += blockSize)
	{
		for (int y = ylocation- (height / 2); y <= ylocation+ (height / 2); y += blockSize)
		{
			for (int z = zlocation + height -(height/3); z <= zlocation + height+(height / 3); z += blockSize)
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
	gluPerspective(60.0f, (float)width/height, 0.5, 50);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, blocksTexture);

	for (int x = 0; x < worldWidth; x++)
	{
		for (int z = 0; z < worldDepth; z++)
		{
			for (int y = 0; y < worldHeight; y++)
			{
				if (world[x][z][y].textureSide == -1)
					continue;

				glPushMatrix();
				glTranslatef((float)x*blockSize, (float)y*blockSize, (float)z*blockSize);
				drawCube(world[x][z][y].textureTop, world[x][z][y].textureSide);
				glPopMatrix();
			}
		}
	}

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void moveZ(float direction, float fac)
{
	camera.posY += (fac * direction);
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

void loadTexture()
{
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
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	//Cursor
	glutWarpPointer(width / 2, height / 2);
	glutSetCursor(GLUT_CURSOR_NONE);

	loadTexture();
	generateWorld();

	glutMainLoop();

	return 0;
}