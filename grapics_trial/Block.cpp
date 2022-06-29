#include "Block.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "Texture.h"

/*Block::Block(int x, int y, int z, enum BlockType Block_id)
{
	this->Block_id = Block_id;
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

Block::Block()
{

}*/

void Level(Block** blocks,int width,int height)
{
	for (int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			//if (blocks[j][i].position.y >= 0 && blocks[j][i].position.y <= 1)
				blocks[j][i].Block_id = GRASS_BLOCK;
			//else if (blocks[j][i].position.y >1 && blocks[j][i].position.y <= 20)
				//blocks[j][i].Block_id = WATER_BLOCK;
			//else
			//{
			//	blocks[j][i].Block_id = GRASS_BLOCK;
			//}

		}
}

void RenderTree(int x, int y,int z,GLuint *textures)
{
	int i;
	for (i = y + 2; i <= y + 6; i += 2)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, textures[OAK_ABOVE]);

		glBegin(GL_QUADS);

		//Top 
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-1 + x, 1 + i, 1 + z);

		glTexCoord2f(1, 1);
		glVertex3f(1 + x, 1 + i, 1 + z);

		glTexCoord2f(1, 0);
		glVertex3f(1 + x, 1 + i, -1 + z);

		glTexCoord2f(0, 0);
		glVertex3f(-1 + x, 1 + i, -1 + z);
		glEnd();
		//glColor3f(1, 1, 1);

		glBindTexture(GL_TEXTURE_2D, textures[OAK]);


		glBegin(GL_QUADS);
		//Front

		glNormal3f(0, 0, 1);

		glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
		glVertex3f(-1 + x, -1 + i, 1 + z);	//Down Left Vertex

		glTexCoord2f(1, 0);
		glVertex3f(1 + x, -1 + i, 1 + z);

		glTexCoord2f(1, 1);
		glVertex3f(1 + x, 1 + i, 1 + z);

		glTexCoord2f(0, 1);
		glVertex3f(-1 + x, 1 + i, 1 + z);
		glEnd();


		glBegin(GL_QUADS);
		//Left
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(-1 + x, -1 + i, -1 + z);
		glTexCoord2f(1, 0);
		glVertex3f(-1 + x, -1 +i, 1 + z);
		glTexCoord2f(1, 1);
		glVertex3f(-1 + x, 1 + i, 1 + z);
		glTexCoord2f(0, 1);
		glVertex3f(-1 + x, 1 + i, -1 + z);
		glEnd();

		glBegin(GL_QUADS);
		//Right
		glTexCoord2f(0, 0);
		glVertex3f(1 + x, -1 + i, -1 + z);
		glTexCoord2f(1, 0);
		glVertex3f(1 + x, -1 + i, 1 + z);
		glTexCoord2f(1, 1);
		glVertex3f(1 + x, 1 + i, 1 + z);
		glTexCoord2f(0, 1);
		glVertex3f(1 + x, 1 + i, -1 + z);
		glEnd();

		//BACK
		glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);

		glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
		glVertex3f(-1 + x, -1 + i, -1 + z);	//Down Left Vertex

		glTexCoord2f(1, 0);
		glVertex3f(1 + x, -1 + i, -1 + z);

		glTexCoord2f(1, 1);
		glVertex3f(1 + x, 1 + i, -1 + z);

		glTexCoord2f(0, 1);
		glVertex3f(-1 + x, 1 + i, -1 + z);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	/*for (int j = -6; j <= 6; j += 2)
	{
		for (int k = -6; k <= 6; k += 2)
		{
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, textures[LEAF]);

			glBegin(GL_QUADS);

			//Top 
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-1 + x + k, 1 + i, 1 + z + j);

			glTexCoord2f(1, 1);
			glVertex3f(1 + x + k, 1 + i, 1 + z - +j);

			glTexCoord2f(1, 0);
			glVertex3f(1 + x + k, 1 + i, -1 + z + j);

			glTexCoord2f(0, 0);
			glVertex3f(-1 + x + k, 1 + i, -1 + z + j);
			glEnd();
			//glColor3f(1, 1, 1);

			//glBindTexture(GL_TEXTURE_2D, textures[OAK]);


			glBegin(GL_QUADS);
			//Front

			glNormal3f(0, 0, 1);

			glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
			glVertex3f(-1 + k, -1 + i, 1 + z+j);	//Down Left Vertex

			glTexCoord2f(1, 0);
			glVertex3f(1 + k, -1 + i, 1 + z+j);

			glTexCoord2f(1, 1);
			glVertex3f(1 + k, 1 + i, 1 + z+j);

			glTexCoord2f(0, 1);
			glVertex3f(-1 + k, 1 + i, 1 + z+j);
			glEnd();


			glBegin(GL_QUADS);
			//Left
			glNormal3f(-1, 0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(-1 + x+k, -1 + i, -1 + z+j);
			glTexCoord2f(1, 0);
			glVertex3f(-1 + x+k, -1 + i, 1 + z+j);
			glTexCoord2f(1, 1);
			glVertex3f(-1 + x+k, 1 + i, 1 + z+j);
			glTexCoord2f(0, 1);
			glVertex3f(-1 + x+k, 1 + i, -1 + z+j);
			glEnd();

			glBegin(GL_QUADS);
			//Right
			glTexCoord2f(0, 0);
			glVertex3f(1 + x+k, -1 + i, -1 + z+j);
			glTexCoord2f(1, 0);
			glVertex3f(1 + x+k, -1 + i, 1 + z+j);
			glTexCoord2f(1, 1);
			glVertex3f(1 + x+k, 1 + i, 1 + z+j);
			glTexCoord2f(0, 1);
			glVertex3f(1 + x+k, 1 + i, -1 + z+j);
			glEnd();

			//BACK
			glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);

			glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
			glVertex3f(-1 + x+k, -1 + i, -1 + z+j);	//Down Left Vertex

			glTexCoord2f(1, 0);
			glVertex3f(1 + x+k, -1 + i, -1 + z+j);

			glTexCoord2f(1, 1);
			glVertex3f(1 + x+k, 1 + i, -1 + z+j);

			glTexCoord2f(0, 1);
			glVertex3f(-1 + x+k, 1 + i, -1 + z+j);

			glEnd();

			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		}
	}*/
}

void RenderBlocks(Block** blocks, GLuint* textures, int width, int height)
{
	//glPushMatrix();
	int x, y, z;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			x = blocks[j][i].position.x;
			y = blocks[j][i].position.y;
			z = blocks[j][i].position.z;
			if (blocks[j][i].Block_id == GRASS_BLOCK)
			{
				glPushMatrix();
				glEnable(GL_TEXTURE_2D);

				glBindTexture(GL_TEXTURE_2D, textures[GRASS]);

				glBegin(GL_QUADS);

				//Top 
				glNormal3f(0, 1, 0);
				glTexCoord2f(0, 1);
				glVertex3f(-1 + x, 1 + y, 1 + z);

				glTexCoord2f(1, 1);
				glVertex3f(1 + x, 1 + y, 1 + z);

				glTexCoord2f(1, 0);
				glVertex3f(1 + x, 1 + y, -1 + z);

				glTexCoord2f(0, 0);
				glVertex3f(-1 + x, 1 + y, -1 + z);
				glEnd();
				//glColor3f(1, 1, 1);

				glBindTexture(GL_TEXTURE_2D, textures[DIRT]);


				glBegin(GL_QUADS);
				//Front

				glNormal3f(0, 0, 1);

				glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
				glVertex3f(-1 + x, -1 + y, 1 + z);	//Down Left Vertex

				glTexCoord2f(1, 0);
				glVertex3f(1 + x, -1 + y, 1 + z);

				glTexCoord2f(1, 1);
				glVertex3f(1 + x, 1 + y, 1 + z);

				glTexCoord2f(0, 1);
				glVertex3f(-1 + x, 1 + y, 1 + z);
				glEnd();


				glBegin(GL_QUADS);
				//Left
				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 0);
				glVertex3f(-1 + x, -1 + y, -1 + z);
				glTexCoord2f(1, 0);
				glVertex3f(-1 + x, -1 + y, 1 + z);
				glTexCoord2f(1, 1);
				glVertex3f(-1 + x, 1 + y, 1 + z);
				glTexCoord2f(0, 1);
				glVertex3f(-1 + x, 1 + y, -1 + z);
				glEnd();

				glBegin(GL_QUADS);
				//Right
				glTexCoord2f(0, 0);
				glVertex3f(1 + x, -1 + y, -1 + z);
				glTexCoord2f(1, 0);
				glVertex3f(1 + x, -1 + y, 1 + z);
				glTexCoord2f(1, 1);
				glVertex3f(1 + x, 1 + y, 1 + z);
				glTexCoord2f(0, 1);
				glVertex3f(1 + x, 1 + y, -1 + z);
				glEnd();

				//BACK
				glBegin(GL_QUADS);
				glNormal3f(0, 0, -1);

				glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
				glVertex3f(-1 + x, -1 + y, -1 + z);	//Down Left Vertex

				glTexCoord2f(1, 0);
				glVertex3f(1 + x, -1 + y, -1 + z);

				glTexCoord2f(1, 1);
				glVertex3f(1 + x, 1 + y, -1 + z);

				glTexCoord2f(0, 1);
				glVertex3f(-1 + x, 1 + y, -1 + z);

				glEnd();

				glDisable(GL_TEXTURE_2D);
				glPopMatrix();

				RenderTree(blocks[width/2][height/2].position.x, blocks[width / 2][height / 2].position.y, blocks[width / 2][height / 2].position.z, textures);

				if (blocks[j][i].position.y <= WATER_LEVEL)
				{
					int pos;
					for (pos = blocks[j][i].position.y + 2; pos <= WATER_LEVEL; pos += 2)
					{
						glPushMatrix();
						glDisable(GL_LIGHTING);
						glEnable(GL_TEXTURE_2D);

						glBindTexture(GL_TEXTURE_2D, textures[WATER]);
						glEnable(GL_BLEND);//Transparent
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


						glBegin(GL_QUADS);

						glColor4f(1, 1, 1, 0.3f);
						//Top 
						glNormal3f(0, 1, 0);
						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, 1 + z);

						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, 1 + z);

						glTexCoord2f(1, 0);
						glVertex3f(1 + x, 1 + pos, -1 + z);

						glTexCoord2f(0, 0);
						glVertex3f(-1 + x, 1 + pos, -1 + z);
						glEnd();
						//glColor3f(1, 1, 1);

						//glBindTexture(GL_TEXTURE_2D, textures[DIRT]);


						glBegin(GL_QUADS);
						//Front

						glNormal3f(0, 0, 1);

						glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
						glVertex3f(-1 + x, -1 + pos, 1 + z);	//Down Left Vertex

						glTexCoord2f(1, 0);
						glVertex3f(1 + x, -1 + pos, 1 + z);

						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, 1 + z);

						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, 1 + z);
						glEnd();


						glBegin(GL_QUADS);
						//Left
						glNormal3f(-1, 0, 0);
						glTexCoord2f(0, 0);
						glVertex3f(-1 + x, -1 + pos, -1 + z);
						glTexCoord2f(1, 0);
						glVertex3f(-1 + x, -1 + pos, 1 + z);
						glTexCoord2f(1, 1);
						glVertex3f(-1 + x, 1 + pos, 1 + z);
						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, -1 + z);
						glEnd();

						glBegin(GL_QUADS);
						//Right
						glTexCoord2f(0, 0);
						glVertex3f(1 + x, -1 + pos, -1 + z);
						glTexCoord2f(1, 0);
						glVertex3f(1 + x, -1 + pos, 1 + z);
						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, 1 + z);
						glTexCoord2f(0, 1);
						glVertex3f(1 + x, 1 + pos, -1 + z);
						glEnd();

						//BACK
						glBegin(GL_QUADS);
						glNormal3f(0, 0, -1);

						glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
						glVertex3f(-1 + x, -1 + pos, -1 + z);	//Down Left Vertex

						glTexCoord2f(1, 0);
						glVertex3f(1 + x, -1 + pos, -1 + z);

						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, -1 + z);

						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, -1 + z);
						glEnd();
						glPopMatrix();
						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);
						glEnable(GL_LIGHTING);
					}
				}
				else
				{
					int pos;
					for (pos = 0; pos < blocks[j][i].position.y - 2; pos += 2)
					{
						glPushMatrix();
						glEnable(GL_TEXTURE_2D);

						glBindTexture(GL_TEXTURE_2D, textures[GRASS]);

						glBegin(GL_QUADS);

						//Top 
						glNormal3f(0, 1, 0);
						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, 1 + z);

						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, 1 + z);

						glTexCoord2f(1, 0);
						glVertex3f(1 + x, 1 + pos, -1 + z);

						glTexCoord2f(0, 0);
						glVertex3f(-1 + x, 1 + pos, -1 + z);
						glEnd();
						//glColor3f(1, 1, 1);

						glBindTexture(GL_TEXTURE_2D, textures[DIRT]);


						glBegin(GL_QUADS);
						//Front

						glNormal3f(0, 0, 1);

						glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
						glVertex3f(-1 + x, -1 + pos, 1 + z);	//Down Left Vertex

						glTexCoord2f(1, 0);
						glVertex3f(1 + x, -1 + pos, 1 + z);

						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, 1 + z);

						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, 1 + z);
						glEnd();


						glBegin(GL_QUADS);
						//Left
						glNormal3f(-1, 0, 0);
						glTexCoord2f(0, 0);
						glVertex3f(-1 + x, -1 + pos, -1 + z);
						glTexCoord2f(1, 0);
						glVertex3f(-1 + x, -1 + pos, 1 + z);
						glTexCoord2f(1, 1);
						glVertex3f(-1 + x, 1 + pos, 1 + z);
						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, -1 + z);
						glEnd();

						glBegin(GL_QUADS);
						//Right
						glTexCoord2f(0, 0);
						glVertex3f(1 + x, -1 + pos, -1 + z);
						glTexCoord2f(1, 0);
						glVertex3f(1 + x, -1 + pos, 1 + z);
						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, 1 + z);
						glTexCoord2f(0, 1);
						glVertex3f(1 + x, 1 + pos, -1 + z);
						glEnd();

						//BACK
						glBegin(GL_QUADS);
						glNormal3f(0, 0, -1);

						glTexCoord2f(0, 0);	//Down Left Pixel (Range from 0 to 1 (UV) )
						glVertex3f(-1 + x, -1 + pos, -1 + z);	//Down Left Vertex

						glTexCoord2f(1, 0);
						glVertex3f(1 + x, -1 + pos, -1 + z);

						glTexCoord2f(1, 1);
						glVertex3f(1 + x, 1 + pos, -1 + z);

						glTexCoord2f(0, 1);
						glVertex3f(-1 + x, 1 + pos, -1 + z);

						glEnd();

						glDisable(GL_TEXTURE_2D);
						glPopMatrix();
					}

				}
				//glPopMatrix();
			}
		}
	}
}