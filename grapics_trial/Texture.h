#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Block.h"
#define NO_OF_TEXTURES 6

#define GRASS 0
#define DIRT 1
#define WATER 2
#define OAK 3
#define LEAF 4
#define OAK_ABOVE 5
/*enum Textures
{
	GRASS = 0,
	DIRT = 1
};*/



struct Texture
{
	//int texture_id;
	const char* location;
};


void TexturesInitialze(Texture* TexturesInformation);
void TexturesLoad(Texture* TexturesInformation, GLuint* textures);
Block** TexturesLoadHeightMap( int* heightMapWidth, int* heightMapHeight, const char* path);