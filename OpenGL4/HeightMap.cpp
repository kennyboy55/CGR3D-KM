#include "HeightMap.h"
#include "stb_image.h"

#include <GL/freeglut.h>
#include <iostream>
#include <string>

HeightMap::HeightMap(const std::string &file)
{
	int bpp;
	unsigned char* imgData = stbi_load(file.c_str(), &width, &height, &bpp, 4);
	
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			int offsets[4][2] = { { 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 } };
			for (int i = 0; i < 4; i++)
			{
				float height = ((float)imgData[((h + offsets[i][0]) + (w + offsets[i][1]) * width) * 4]);
				height = (height / 256.0f) * 100.0f;

				vertices.push_back(Vertex{ (float)(h + offsets[i][0]), height, (float)(w + offsets[i][1]),
									0, 1, 0,
									h*0.1f, (w*0.f) + offsets[i][1] });
			}
		}
	}

	stbi_image_free(imgData);
}

HeightMap::~HeightMap()
{
}

void HeightMap::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), ((float*)vertices.data()) + 0);
	//glNormalPointer(GL_FLOAT, sizeof(Vertex), ((float*)cubeVertices.data()) + 3);
	//glColorPointer(4, GL_FLOAT, sizeof(Vertex), ((float*)cubeVertices.data()) + 6);
	glDrawArrays(GL_QUADS, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
}