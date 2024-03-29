#include "Application.h"

Application App(1200, 900, "Space Base");

void reshapeCallback(int width, int height)
{
	App.handleReshape(width, height);
}

void displayCallback()
{
	App.updateDisplay();
}

void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY)
{
	App.addKeyActive(keyPressed);
	auto res = glutGetModifiers();
	switch (res)
	{
		case GLUT_ACTIVE_SHIFT:
			App.addKeyActive(GLUT_ACTIVE_SHIFT);
			break;
		case GLUT_ACTIVE_CTRL:
			App.addKeyActive(GLUT_ACTIVE_CTRL);
			break;
		case GLUT_ACTIVE_ALT:
			App.addKeyActive(GLUT_ACTIVE_ALT);
			break;
		default:
			break;
	}
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

void menuCallback(int item)
{
	switch (item)
	{
		case 1:
		case 2:
		case 3:
			App.setCameraView(item);
			break;
		case 4:
			App.toggleCameraLock();
			break;
		default:
			break;
	}
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

	//Menu setup
	glutCreateMenu(menuCallback);
	glutAddMenuEntry("Camera Position 1", 1);
	glutAddMenuEntry("Camera Position 2", 2);
	glutAddMenuEntry("Camera Position 3", 3);
	glutAddMenuEntry("Toggle Camera Mode", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// initialize PGR framework (GL, DevIl, etc.)
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	App.initializeResources();

	glutMainLoop();
	return 0;
}