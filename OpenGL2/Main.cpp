#include <GL/freeglut.h>
#include <cstdio>
#include <time.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"


void generateTree(int, int, int);


float lastFrameTime = 0;

float speed = 10;

int width, height;
GLuint blocksTexture;

const int worldWidth = 64;
const int worldDepth = 64;
const int worldHeight = 16;
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

	std::srand(time(NULL));
	float rand = std::rand() * (1.0f / worldDepth);

	std::cout << "Generating world... " << rand << std::endl;

	for (int x = 0; x < worldWidth; x++){
		for (int z = 0; z < worldDepth; z++){
			for (int y = 0; y < worldHeight; y++){
				world[x][z][y] = Block{ -1,-1 };
			}
		}
	}

	for (int x = 0; x < worldWidth; x++)
	{
		for (int z = 0; z < worldDepth; z++)
		{
			float h = stb_perlin_noise3((1.0f/(float)worldWidth)*(float)x, (1.0f / (float)worldDepth)*(float)z, rand);
			int heightInt = abs((int)(h * 8));

			for (int y = 0; y < worldHeight; y++)
			{

				if (y < worldHeight / 4)
				{
					int d = std::rand() % 100;
					if (d > 95)
						world[x][z][y] = Block{ 32, 32 };
					else if (d > 92)
						world[x][z][y] = Block{ 33, 33 };
					else if (d > 90)
						world[x][z][y] = Block{ 34, 34 };
					else
						world[x][z][y] = Block{ 1, 1 };
				}
				else if (y < (heightInt + worldHeight / 4))
				{
					world[x][z][y] = Block{ 2, 2 };
				}
				else if (y == (heightInt + worldHeight / 4))
				{
					world[x][z][y] = Block{ 0, 3 };

					int d = std::rand() % 100;
					if (d > 98)
						generateTree(x, z, y+1);
					else if (d > 93)
						world[x][z][y + 1] = Block{ -1, 39 };
				}
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

void generateTree(int xlocation, int zlocation, int ylocation)
{
	int size = std::rand() % 3 +  3; //Size from 2 to 5;
	int treetype = std::rand() % 4;

	for (int y = ylocation; y <= ylocation+size; y ++)
	{
		if (y >= 0 && y < worldHeight)
		{
			if(treetype <= 1)
				world[xlocation][zlocation][y] = Block{ 21, 20 };
			else if(treetype <= 2)
				world[xlocation][zlocation][y] = Block{ 21, 117 };
			else
				world[xlocation][zlocation][y] = Block{ 21, 116 };
		}
	}

	for (int x = (-size /2); x <=  (size / 2); x ++)
	{
		for (int z = - (size / 2); z <=  (size / 2); z ++)
		{
			for (int y = size - (size / 3); y <= size + (size / 3); y++)
			{
				if (x + xlocation >= 0 && x + xlocation < worldWidth && z + zlocation >= 0 && z + zlocation < worldDepth && y + ylocation >= 0 && y + ylocation < worldHeight)
				{
					if (abs(x) == (size / 2) && abs(y) == size + (size / 3)|| abs(z) == (size / 2) && abs(y) == size + (size / 3))
					{

					}
					else
					{
						if (treetype <= 2)
							world[x + xlocation][z + zlocation][y + ylocation] = Block{ 52, 52 };
						else
							world[x + xlocation][z + zlocation][y + ylocation] = Block{ 132, 132 };
					}
				}
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
	gluPerspective(60.0f, (float)width/height, 0.5, 300);


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

	if (keys['+']) speed += speed > 25 ? 0 : 0.5;
	if (keys['-']) speed -= speed < 5 ? 0 : 0.5;

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
	glutCreateWindow("Minecraft 2.0");

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