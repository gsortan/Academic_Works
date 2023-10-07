//NGenesis created by Gary Ng: January 11, 2012 - Present
//The main function will include all activites related to windowing and basic rendering as well as program initialization. Essentially just core program functionality

#include "Game.h"

const unsigned int WINDOW_LOCATION_X = glutGet(GLUT_SCREEN_WIDTH) * 0.1; //Sets window location x to middle of screen based off of the above 80%
const unsigned int WINDOW_LOCATION_Y = glutGet(GLUT_SCREEN_HEIGHT) * 0.1; //Sets window location y to middle of screen based off of the above 80%

float MAIN_WINDOW_WIDTH = glutGet(GLUT_SCREEN_WIDTH) * 0.8;
float MAIN_WINDOW_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT) * 0.8;

float SIDE_WINDOW_WIDTH = 0.0f; //Side window is for the one thats supposed to render the sample object
float SIDE_WINDOW_HEIGHT = MAIN_WINDOW_HEIGHT;

#define NG_FRAMES_PER_SECOND 30; //Ideal FPS
const int FRAME_DELAY_SPRITE = 1000 / NG_FRAMES_PER_SECOND;

Game* theGame;

void initViewport(int startX, int startY, int endX, int endY) //Sets up viewport
{
	glViewport(startX, startY, endX, endY); //Sets up viewport to specified size
	glMatrixMode(GL_PROJECTION); //Sets to projection mode
	glLoadIdentity(); //Clears matrix	
}

void initModelview()
{
	glMatrixMode(GL_MODELVIEW); //Sets to model view mode
	glLoadIdentity(); //Clears matrix
}

void initImageLibrary() //Initializes DevIL
{
	glEnable(GL_TEXTURE_2D);
	ilInit(); //Inits Il
	iluInit(); //Inits Ilu
	ilutRenderer(ILUT_OPENGL); //Uses OpenGL to render?
}

void set2DView(int startX, int endX, int startY, int endY) //Needs 2D orientation for sprites
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(startX, endX, startY, endY, -1.0, 1.0);
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears screen

	initViewport(SIDE_WINDOW_WIDTH, 0.0f, MAIN_WINDOW_WIDTH - SIDE_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);		

	
	gluPerspective(60.0, MAIN_WINDOW_WIDTH / MAIN_WINDOW_HEIGHT, 1.0f, 4000.0); //Sets perspective mode
	
	theGame ->getCamera() ->moveCameraToLocationAndLookAtSomething(theGame ->getCharacter() ->getPosition().add(Vector3f(sin(mDegToRad(theGame ->getCharacter() ->getRotate().getY())) * -75.0f, theGame ->getCharacter() ->getMaxSize().getY(), cos(mDegToRad(theGame ->getCharacter() ->getRotate().getY())) * -75.0f)), theGame ->getCharacter() ->getPosition(), Vector3f(0.0f, 0.0f, -1.0f));
	
	
	theGame ->setLightMatrices();

	theGame ->shadowQuad ->bindFBO(NG_DEPTH_TEXTURE);	
	theGame ->drawShadowModels();	
	theGame ->shadowQuad ->unbindFBO(NG_DEPTH_TEXTURE);

	theGame ->getCamera() ->update(float(MAIN_WINDOW_WIDTH - SIDE_WINDOW_WIDTH), float(MAIN_WINDOW_HEIGHT), 1.0, 4000.0);
	
	initModelview();

	theGame ->the3DQuad ->bindFBO(NG_RGBA_TEXTURE);
	theGame ->drawParticles();
	theGame ->drawModels();
	theGame ->drawShadowModels();	

	theGame ->the3DQuad ->unbindFBO(NG_RGBA_TEXTURE);

	set2DView(0.0f, MAIN_WINDOW_WIDTH, 0.0f, MAIN_WINDOW_HEIGHT);
	initModelview();	
	
	theGame ->the2DQuad ->bindFBO(NG_RGBA_TEXTURE);	
	theGame ->drawText();
	theGame ->drawSprites();
	theGame ->the2DQuad ->unbindFBO(NG_RGBA_TEXTURE);


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	theGame ->drawQuad(NG_3D_QUAD, theGame ->the3DQuad);	

	theGame ->drawQuad(NG_2D_QUAD, theGame ->the2DQuad);	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);


	char windowTitle[52] = "SHFTed: ";
	float fps = theGame ->getTimer() ->getFPS();
	strcat_s(windowTitle, Conversion::numToCharArray(fps));
	strcat_s(windowTitle, " FPS");	

	glutSetWindowTitle(windowTitle);

	glutSwapBuffers();
}

void windowReshape(int newWidth, int newHeight) //Reshapes window
{
	float widthMultiplier = newWidth / MAIN_WINDOW_WIDTH;
	float heightMultiplier = newHeight / MAIN_WINDOW_HEIGHT;

	MAIN_WINDOW_WIDTH *= widthMultiplier;
	MAIN_WINDOW_HEIGHT *= heightMultiplier;

	SIDE_WINDOW_WIDTH *= widthMultiplier;
	SIDE_WINDOW_HEIGHT *= heightMultiplier;
}

void keyDownHandler(unsigned char keyPressed, int x, int y) //Checks keyboard input
{
	theGame ->keyDownHandler(keyPressed, x, y);
}

void keyUpHandler(unsigned char keyReleased, int x, int y) //Checks keyboard input
{
	theGame ->keyUpHandler(keyReleased, x, y);
}

void specialKeyDownHandler(int keyPressed, int x, int y) //Checks keyboard input for special characters
{
	theGame ->specialKeyDownHandler(keyPressed, x, y);
}

void specialKeyUpHandler(int keyReleased, int x, int y) //Checks keyboard input for special characters
{
	theGame ->specialKeyUpHandler(keyReleased, x, y);
}

void mouseClickHandler(int mouseButton, int state, int x, int y) //Checks mouse clicks
{
	theGame ->mouseClickHandler(mouseButton, state, x, y);
}

void mouseMovementHandler(int x, int y)
{
	theGame ->mouseMovementHandler(x, y);
}

void enterFrame(int value) //Checks for time
{	
	//calculateFPS();
	theGame ->enterFrame();

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY_SPRITE, enterFrame, 0); //The 0 is the value that gets passed in. Doesn't do anything
}

int main(int argc, char **argv)
{
	//GLUT Initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Double buffer with RGBA colors and depth
	glutInitWindowPosition(WINDOW_LOCATION_X, WINDOW_LOCATION_Y); //Where the window starts on your screen
	glutInitWindowSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT); //Window size. Temp
	glShadeModel(GL_FLAT); //Used for texturing I guess
	glutCreateWindow("SHFTed"); //Window title

	//Event Handler Registration
	glutDisplayFunc(renderScene); //Displays renderScene
	glutReshapeFunc(windowReshape); //Reshapes using windowReshape
	glutKeyboardFunc(keyDownHandler); //Keyboard event listener
	glutKeyboardUpFunc(keyUpHandler); 
	glutSpecialFunc(specialKeyDownHandler); //Special keyboard event listener
	glutSpecialUpFunc(specialKeyUpHandler);
	glutMouseFunc(mouseClickHandler); //Mouse click listener
	glutPassiveMotionFunc(mouseMovementHandler); //Mouse movement listener
	glutMotionFunc(mouseMovementHandler); //Mouse movement listener - Only when clicked
	glutTimerFunc(0, enterFrame, 0); //"enterFrame" listener	
	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	initImageLibrary();
	glewInit();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); //Depth info
	glEnable(GL_ALPHA_TEST); //Enables alpha testing

	glutSetCursor(GLUT_CURSOR_NONE); //Disables cursor

	theGame = new Game();

	glutMainLoop(); //Loops handlers every FPS

	return 0;
}