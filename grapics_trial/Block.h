#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

#define WATER_LEVEL 13

enum BlockType
{
	GRASS_BLOCK = 0,
	WATER_BLOCK = 1
};

struct Vertex
{
	float x, y, z;
	Vertex()
	{
		x = y = z = 0;
	}
};

struct Block
{
//public:
	enum BlockType Block_id;
	Vertex position;
	//static int numberofblocks = 1;
	//Block();
	//Block(int x,int y,int z, enum BlockType Block_id);
};

void RenderBlocks(Block **blocks, GLuint* textures,int width,int height);
void Level(Block** blocks,int width,int height);
void RenderTree(int x, int y,int z,GLuint *textures);