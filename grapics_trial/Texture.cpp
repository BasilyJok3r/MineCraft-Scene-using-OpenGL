#include "Texture.h"
#include "GL\freeglut.h"
#include "FreeImage.h"
#include <list>
#include "Block.h"



using namespace std;

void TexturesInitialze(Texture *TexturesInformation)
{
	//TexturesInformation[GRASS].texture_id = GRASS;
	TexturesInformation[GRASS].location = "Textures\\grass.jpg";

	//TexturesInformation[DIRT].texture_id = DIRT;
	TexturesInformation[DIRT].location = "Textures\\dirt.jpg";

	TexturesInformation[WATER].location = "Textures\\water.jpg";

	TexturesInformation[OAK].location = "Textures\\oak.jpg";

	TexturesInformation[LEAF].location = "Textures\\leaf.jpg";

	TexturesInformation[OAK_ABOVE].location = "Textures\\above.jpg";
}

void TexturesLoad(Texture *TexturesInformation, GLuint *textures)
{
	for (int i = 0; i < NO_OF_TEXTURES; i++)
	{
		GLuint texture;
		FIBITMAP* originalImage= FreeImage_Load(FreeImage_GetFileType(TexturesInformation[i].location, 0), TexturesInformation[i].location);
		FIBITMAP*  finalImage = FreeImage_ConvertTo32Bits(originalImage);
		int width = FreeImage_GetWidth(finalImage);
		int height= FreeImage_GetHeight(finalImage);

		glGenTextures(1, &texture);


		glBindTexture(GL_TEXTURE_2D, texture);	//Set 'texture' as the active texture

		//Set the MAG and MIN Filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Min Filter, use interpolation
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Mag Filter, use interpolation

		//Convert from image to a texture
		//GL_BGRA_EXT is used because Freeimage API uses the big endian format (bytes are in reversed order)
		//GL_UNSIGNED_BYTE means that each channel is rep. using a value from 0~255
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, FreeImage_GetBits(finalImage));

		textures[i] = texture;
	}
}

Block** TexturesLoadHeightMap(int* heightMapWidth,int* heightMapHeight,const char* path)
{
	FIBITMAP* heightMapImage = FreeImage_Load(FreeImage_GetFileType(path, 0), path);
	FIBITMAP* gHeightMap = FreeImage_ConvertTo8Bits(heightMapImage);
	gHeightMap = FreeImage_ConvertToGreyscale(gHeightMap);

	*heightMapWidth = FreeImage_GetWidth(gHeightMap);
	*heightMapHeight = FreeImage_GetHeight(gHeightMap);

	//Dynamic Allocation for the height map
	Block **blocks = new Block * [*heightMapWidth];
	for (int i = 0; i < *heightMapWidth; i++)
		blocks[i] = new Block[*heightMapHeight];

	int initial = (*heightMapWidth / 2 - *heightMapWidth) * 2;
	int x = (*heightMapHeight / 2 - *heightMapHeight) * 2;
	int z= initial;
	for (int i = 0;  i< *heightMapHeight; i++)
	{
		z = initial;
		BYTE* sLine = FreeImage_GetScanLine(gHeightMap, i);
		for (int j = 0; j < *heightMapWidth; j++)
		{
			Vertex tmp;
			tmp.x = x;
			tmp.y = sLine[j]/10;
			tmp.z = z;
			blocks[j][*heightMapHeight - i - 1].position = tmp;
			blocks[j][i].Block_id = GRASS_BLOCK;
			z += 2;
			//blocks[x][y].position = sLine[x];
		}
		x += 2;
	}
	return blocks;
}