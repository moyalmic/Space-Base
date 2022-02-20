#include "Application.h"

Application App(1200, 900, "Space Base");

void reshapeCallback(int width, int height)
{
	App.handleReshape(width, height);
}

void displayCallback()
{
	App.drawDisplay();
}

void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY)
{
	App.handleKeyboard(keyPressed, mouseX, mouseY);
}

void specialCallback(int keyPressed, int mouseX, int mouseY)
{
	App.handleSpecial(keyPressed, mouseX, mouseY);
}

void passiveMotionCallback(int x, int y) 
{
	App.handlePassiveMouse(x, y);
}

void mouseCallback(int buttonPressed, int buttonState, int mouseX, int mouseY)
{
	App.handleMouse(buttonPressed, buttonState, mouseX, mouseY);
}

void timerCallback(int value)
{
	App.handleTimer();
	glutTimerFunc(33, timerCallback, 0);
}

int main(int argc, char** argv)
{
	// initialize windowing system
	App.initializeGlut(argc, argv);

	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(specialCallback);
	glutPassiveMotionFunc(passiveMotionCallback);
	glutMouseFunc(mouseCallback);
	glutTimerFunc(33, timerCallback, 0);

	// initialize PGR framework (GL, DevIl, etc.)
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	App.initializeResources();

	glutMainLoop();
	return 0;
}