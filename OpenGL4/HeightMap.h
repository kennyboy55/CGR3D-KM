#pragma once
#include <string>
#include <vector>

class HeightMap
{
private:
	int height;
	int width;
public:
	HeightMap(const std::string &file);
	~HeightMap();

	void Draw();

	struct Vertex {
		float x;
		float y;
		float z;

		float normalX;
		float normalY;
		float normalZ;

		float texX;
		float texY;
	};

	std::vector<Vertex> vertices;
};

