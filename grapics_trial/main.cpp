#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "freeimage.h"
#include "Texture.h"
#include "Block.h"

using namespace std;

int numberofblocks = 1;

GLfloat ambientLight[] = { 0.8, 0.8, 0.8, 1 };
GLfloat diffuseLight[] = { 1, 1, 1, 1 };
GLfloat lightPosition[] = { 500, 800, 600, 1 };
float clearRed = 0.4f, clearGreen = 0.47, clearBlue = 0.71;
float cR = clearRed, cG = clearGreen, cB = clearBlue;
int lightDir = 0;

int width;
int height;
float cameraX = 0.0f, cameraY = 0, cameraZ = 5;	//Position of the camera inside the scene
float headingX = 0, headingZ = 0.0f;	//Where the camera is pointed to ! (Heading)
float strafeX = -0.2f, strafeZ = 0;
float cameraAng = 0;
float lookAngle = 0; //Look Up & Down
GLuint textures[NO_OF_TEXTURES];
Texture TexturesInformation[NO_OF_TEXTURES];
Block** blocks;
const char* heightPath = "HeightMap\\heightmap.jpg";
//Vertex **positions=new Vertex *[height];

/*void InitializePositions()
{
	int initial = (height / 2 - height) * 2;
	int x = (width/2-width)*2;
	int y = 0;
	int z = (height / 2 - height) * 2;
	for (int i =0; i < width; i++)
	{
		z = initial;
		blocks[i] = new Block[height];
		for (int j = 0; j < height; j++)
		{
			Vertex tmp;
			tmp.x = x;
			tmp.y = y;
			tmp.z = z;
			blocks[i][j].position = tmp;
			blocks[i][j].Block_id = GRASS_BLOCK;
			z += 2;
		}
		x += 2;
	}
}*/

void CopyCoordinates()
{

}

void manageAsyncKeyPresses()
{
	if (GetAsyncKeyState('W') != 0)//Move Forward
	{
		if (GetAsyncKeyState(VK_LSHIFT) != 0)//Move Forward
		{
			cameraX += headingX;
			cameraZ += headingZ;
			cameraY += lookAngle;
		}
		else
		{
			cameraX += headingX/10;
			cameraZ += headingZ/10;
			cameraY += lookAngle/10;
		}
	}
	if (GetAsyncKeyState('S') != 0)//Move Backward
	{
		if (GetAsyncKeyState(VK_LSHIFT) != 0)//Move Forward
		{
			cameraX -= headingX;
			cameraZ -= headingZ;
			cameraY -= lookAngle;
		}
		else
		{
			cameraX -= headingX/10;
			cameraZ -= headingZ/10;
			cameraY -= lookAngle/10;
		}
	}
	if (GetAsyncKeyState('A') != 0)//Move Left
	{
		cameraX -= strafeX/10;
		cameraZ -= strafeZ/10;
	}
	if (GetAsyncKeyState('D') != 0)//Move Right
	{
		cameraX += strafeX/10;
		cameraZ += strafeZ/10;
	}
	//setCamPos();
}

void updateMovementVectors() {
	//used for moving forward relative to the camera orientation
	headingX = sin(cameraAng);
	headingZ = -cos(cameraAng);

	//used for moving left and right relative to the camera orientation
	/*strafeX = cos(135 - double(cameraAng));
	strafeZ = sin(135 - double(cameraAng));*/

	strafeX = -headingZ;
	strafeZ = headingX;

	//lock the looking up and down rotation to 180 degrees
	if (lookAngle > 1)
		lookAngle = 1;
	else if (lookAngle < -1)
		lookAngle = -1;
}

void OnSpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:// Up function key
		cameraY += 0.1;
		break;
	case GLUT_KEY_DOWN:// Down function key
		cameraY-=0.1;
		break;
	};
}

void myPassiveMotionFunc(int a, int b)
{
	//Find out how much was the mouse moved from the last frame (should be at 100,100)
	a -= 960;
	b -= 540;

	//cameraAng is used to look left and right
	cameraAng += float(a) / 1000;

	//lookAngle is used to look up & down
	lookAngle -= float(b) / 2000;

	//update the angles used for movement
	updateMovementVectors();

	//Reset the pointer to position (100,100) to read input in the next frame
	glutWarpPointer(960, 540);
}

void Render()
{
	glClearColor(cR, cG, cB, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Instructs OpenGL to clear previous Colors on screen and also the depth buffer (3D)

	glLoadIdentity();//Clear screen

	gluLookAt(cameraX, cameraY, cameraZ, (cameraX + headingX), (cameraY + lookAngle), (cameraZ + headingZ), 0, 1, 0);

	RenderBlocks(blocks,textures,width,height);

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glPopMatrix();
	
	glutSwapBuffers();
	manageAsyncKeyPresses();
	//glutPostRedisplay();
}

void myTimerFunc(int  val)
{
	if (lightDir == 0)
	{
		lightPosition[1]--;
		diffuseLight[0] -= 0.00125;
		diffuseLight[1] -= 0.00125;
		diffuseLight[2] -= 0.00125;
		cR -= clearRed / 800.0f;
		cG -= clearGreen / 800.0f;
		cB -= clearBlue / 800.0f;
	}
	else
	{
		lightPosition[1]++;
		diffuseLight[0] += 0.00125;
		diffuseLight[1] += 0.00125;
		diffuseLight[2] += 0.00125;
		cR += clearRed / 800.0f;
		cG += clearGreen / 800.0f;
		cB += clearBlue / 800.0f;
	}

	if (lightPosition[1] == 800)
		lightDir = 0;
	else if (lightPosition[1] == 0)
		lightDir = 1;
	glutPostRedisplay();
	glutTimerFunc(16, myTimerFunc, 16);//Set the framerate to 60 fps
}

void SetTransformations(int width,int height) {
	//set up the logical coordinate system of the window: [-100, 100] x[-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60,(double)width/height,0.01,1000);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE| GLUT_DEPTH);
	//Create an 800x600 window with its top-left corner at pixel(100, 100)
		glutInitWindowPosition(0, 0); //pass (-1, -1) for Window - Manager defaults
		glutInitWindowSize(1920, 1080);
		//glutFullScreen();
	glutCreateWindow("OpenGL Game");
	//OnDisplay will handle the paint event
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(Render);
	glutReshapeFunc(SetTransformations);
	glutPassiveMotionFunc(myPassiveMotionFunc);
	//glEnable(GL_TEXTURE_2D);
	TexturesInitialze(TexturesInformation);
	TexturesLoad(TexturesInformation,textures);
	//blocks = new Block[numberofblocks];
	//Block *tmp = new Block(0, 0, 0, GRASS_BLOCK);
	//blocks[0] ;
	//blocks[0]= new ;
	//InitializePositions();
	blocks=TexturesLoadHeightMap(&width,&height,heightPath);
	Level(blocks, width, height);
	glutTimerFunc(16, myTimerFunc, 16);
	glutSpecialFunc(OnSpecialKeyPress);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//blocks[0] = new Block(0, 0, 0, GRASS_BLOCK);
}


int main(int argc, char* argv[])
{
	InitGraphics(argc, argv);
	glutMainLoop();
}