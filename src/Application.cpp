#include "Application.h"

void Application::addModelName(string modelName)
{
	modelNames.push_back(modelName);
}

void Application::initializeModels()
{
	//All objects that are imported through .obj
	for (string modelName : modelNames)
	{
		string temp = modelName.substr(7, modelName.size() - 4 - 7);
		models[temp] = new ModelData(modelName, objectShader);
	}
	//Adding base with array instead of .obj
	ModelData* lamp = new ModelData();
	lamp->loadModelFromArray(objectShader, "models/LampTex.png", lampNVertices, lampVertices, lampNTriangles, lampTriangles);
	models["lamp"] = lamp;
}

void Application::initializeObjects()
{
	objects.push_back(new SceneObject(0, glm::vec3(0.0f, 10.0f, 0.0f), 0.0f, 180.0f, -30.0f, 0.0f, 3.0f, models["spaceship"]));
	objects.push_back(new SceneObject(0, glm::vec3(0.0f, 8.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, 75.0f, models["terrain"]));
	objects.push_back(new SceneObject(0, glm::vec3(-15.0f, -0.5f, -20.0f), 0.0f, 37.5f, 0.0f, 0.0f, 7.0f, models["base"]));
	objects.push_back(new SceneObject(0, glm::vec3(-8.0f, -2.5f, -16.0f), 0.0f, -52.5f, 0.0f, 0.0f, 1.5f, models["military_box"]));
	objects.push_back(new SceneObject(0, glm::vec3(12.0f, -1.0f, -4.0f), 0.0f, 90.0f, 0.0f, 0.0f, 2.0f, models["signpost"]));
	objects.push_back(new SceneObject(3, glm::vec3(-10.0f, -1.8f, 15.0f), 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, models["rock1"]));
	objects.push_back(new SceneObject(3, glm::vec3(10.0f, -1.5f, -40.0f), -90.0f, 0.0f, 0.0f, 0.0f, 2.0f, models["rock1"]));
	objects.push_back(new SceneObject(3, glm::vec3(-35.0f, -0.7f, 37.0f), -32.5f, 0.0f, 0.0f, 0.0f, 2.0f, models["rock2"]));
	objects.push_back(new SceneObject(3, glm::vec3(46.0f, 6.0f, 49.0f), -18.0f, 0.0f, 0.0f, 0.0f, 2.0f, models["rock3"]));
	plants.push_back(new SceneObject(4, glm::vec3(35.0f, -1.7f, 5.0f), 0.0f, 37.5f, 0.0f, 0.0f, 2.0f, models["plant"]));
	plants.push_back(new SceneObject(5, glm::vec3(-30.0f, -1.7f, 15.0f), 0.0f, 60.0f, 0.0f, 0.0f, 2.0f, models["plant"]));
	plants.push_back(new SceneObject(6, glm::vec3(52.0f, 20.0f, -63.0f), 0.0f, 90.0f, 0.0f, 0.0f, 2.0f, models["plant"]));
	plants.push_back(new SceneObject(7, glm::vec3(-20.0f, -1.7f, -30.0f), 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, models["plant"]));
	plants.push_back(new SceneObject(8, glm::vec3(15.0f, -1.7f, 25.0f), 0.0f, 37.5f, 0.0f, 0.0f, 2.0f, models["plant"]));
}

void Application::initializeCamera()
{
	camera = new CameraObject(glm::vec3(10.0f, 2.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		0.0f, -90.0f, 1, false);
}

void Application::initializeLights()
{
	//Directional light (the sun)
	sun = new DirectionalLightObject();
	sun->setIntensity(0.5f);
	sun->setupLight(objectShader);
	//Point light (lamp inside shelter)
	lamps.push_back(new PointLightObject(glm::vec3(-15.0f, -2.0f, -20.0f), 
		new SceneObject(1, glm::vec3(0.0f, 0.0f, 0.0f), -90.0f, 0.0f, 0.0f, 0.0f, 0.5f, models["lamp"])));
	//Yes this is called for a vector, but there will only be one point light because the shader can't handle more
	for (PointLightObject* light : lamps)
	{
		light->setAttenuationConstants(1.0f, 0.09f, 0.0032f);
		light->setupLight(objectShader);
	}
	//Spotlight (light ontop of shelter)
	spotlights.push_back(new SpotLightObject(glm::vec3(-12.0f, 2.2f, -16.0f), 
		new SceneObject(2, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, -45.0f, 0.0f, 0.0f, 0.5f, models["spotlight"])));
	for (SpotLightObject* spotlight : spotlights)
	{
		spotlight->setDirection(glm::radians(0.0f), glm::radians(-45.0f));
		spotlight->setCutoffs(0.91f, 0.82f);
		spotlight->setupLight(objectShader);
	}
}

void Application::initializeSkybox()
{
	skyboxDay = new Skybox(skyboxShader, "day");
}

void Application::initializeFog()
{
	fog = new Fog(0.014f, 2.5f, glm::vec3(0.4f, 0.5f, 0.6f));
	fog->setupFog(objectShader);
}

void Application::initializeBillboards()
{
	explosionData = new BillboardData("models/explosion.png", billboardShader);
}

void Application::updateModels(float currentTime)
{
	//This erases all destoryed plants
	auto plant = plants.begin();
	while (plant != plants.end())
	{
		if ((*plant)->isDestroyed())
			plant = plants.erase(plant);
		else
			plant++;
	}
	//This will update the explosion billboards
	auto explosion = explosions.begin();
	while (explosion != explosions.end())
	{
		if (elapsedTime > (*explosion)->getLifetime())
			explosion = explosions.erase(explosion);
		else
			explosion++;
	}
	//This moves the spaceship
	objects[0]->moveAlongCircle(currentTime);
}

void Application::updateSun()
{
	glm::vec3 currentPosition = sun->getPosition();

	float positionX = 0 + (float)50 * cos(-elapsedTime);
	float positionY = 0 + (float)50 * sin(-elapsedTime);
	
	sun->setPosition(glm::vec3(positionX, positionY, currentPosition.z));
	sun->updatePosition(objectShader);
}

bool Application::checkCollisions(CameraObject* camera, vector<SceneObject*> objects)
{
	glm::vec3 cameraPos = camera->getPosition();
	for (auto object : objects)
	{
		if (object->getID() == 3)
		{
			glm::vec3 objectPos = object->getPosition();
			float dx = cameraPos.x - objectPos.x;
			float dy = cameraPos.y - objectPos.y;
			float dz = cameraPos.z - objectPos.z;

			float distance = dx * dx + dy * dy + dz * dz;
			// This is done to avoid squaring numbers to find out the distance
			if (distance < (camera->getSize() + object->getSize()) * (camera->getSize() + object->getSize()))
				return true;
		}
	}
	return false;
}

Application::Application(int width, int height, string title):
	windowWidth(width), windowHeight(height), windowTitle(title), elapsedTime(0)
{
	
}

void Application::initializeGlut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowTitle.c_str());
}

void Application::initializeResources()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);

	addModelName("models/spaceship.obj");
	addModelName("models/terrain.obj");
	addModelName("models/base.obj");
	addModelName("models/rock1.obj");
	//addModelName("models/lamp.obj"); Bylo pridano jako C pole v configure.h
	addModelName("models/spotlight.obj");
	addModelName("models/military_box.obj");
	addModelName("models/plant.obj");
	addModelName("models/rock2.obj");
	addModelName("models/rock3.obj");
	addModelName("models/signpost.obj");

	objectShader.initializeShaders();
	skyboxShader.initializeShaders();
	billboardShader.initializeShaders();
	initializeModels();
	initializeLights();
	initializeObjects();
	initializeCamera();
	initializeSkybox();
	initializeFog();
	initializeBillboards();
	glutWarpPointer(windowHeight / 2, windowWidth / 2);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Application::handlePassiveMouse(int x, int y)
{
	if (camera->isFree())
	{
		camera->update(x, y, windowWidth, windowHeight);
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	else
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	
	glutPostRedisplay();
}

void Application::handleMouse(int buttonPressed, int buttonState, int mouseX, int mouseY)
{
	if (buttonPressed == GLUT_LEFT_BUTTON && buttonState == GLUT_DOWN)
	{
		unsigned char clickedObjectID;
		glReadPixels(mouseX, windowHeight - 1 - mouseY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &clickedObjectID);

		switch (clickedObjectID)
		{
		case 1:
			lamps[0]->toggleLight(objectShader);
			break;
		case 2:
			spotlights[0]->toggleLight(objectShader);
			break;
		default:
			break;
		}
		if (clickedObjectID >= 4 && clickedObjectID <= 8)
		{
			auto it = std::find_if(plants.begin(), plants.end(), [&](SceneObject* const& obj) {return obj->getID() == clickedObjectID; });
			if (!(*it)->isDestroyed())
			{
				glm::vec3 explosionPosition = (*it)->getPosition();
				(*it)->destroy();
				explosions.push_back(new Explosion(explosionPosition, explosionData, elapsedTime, 16));
			}
		}
	}
}

void Application::handleKeyboard(unsigned char keyPressed, int mouseX, int mouseY)
{
	switch (keyPressed)
	{
	case 27: //escape
		glutLeaveMainLoop();
		break;
	case 'w':
		if (camera->isFree())
		{
			camera->moveForward();
			camera->updateShaderPosition(objectShader);
		}
		break;
	case 's':
		if (camera->isFree())
		{
			camera->moveBack();
			camera->updateShaderPosition(objectShader);
		}
		break;
	case 'a':
		if (camera->isFree())
		{
			camera->moveLeft();
			camera->updateShaderPosition(objectShader);
		}
		break;
	case 'd':
		if (camera->isFree())
		{
			camera->moveRight();
			camera->updateShaderPosition(objectShader);
		}
		break;
	case 'W':
		if (camera->isFree())
		{
			camera->moveUp();
			camera->updateShaderPosition(objectShader);
		}
		break;
	case 'S':
		if (camera->isFree())
		{
			camera->moveDown();
			camera->updateShaderPosition(objectShader);
		}
		break;
	case 'f':
		camera->changeMode();
		break;
	case 'c':
		if(!camera->isFree())
			camera->changeView();
		break;
	case 'q':
		camera->togglePlaneAttach();
	default:
		break;
	}
	glutPostRedisplay();
}

void Application::handleSpecial(int keyPressed, int mouseX, int mouseY)
{
	switch (keyPressed)
	{
	case GLUT_KEY_LEFT:
		camera->changeView();
		break;
	case GLUT_KEY_RIGHT:
		camera->changeView();
	}
}

void Application::handleReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

void Application::updateDisplay()
{
	GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
	glClear(mask);
	//Set the cameras position and pitch/yaw to that of the plane if it should be attached
	if (camera->attachedToPlane())
	{
		auto newPos = objects[0]->getPosition();
		newPos.y += 2.0f; //Make the camera go above the plane
		camera->setPosition(newPos);
	}
	//Calculate view and projection matrices
	glm::vec3 cameraPosition = camera->getPosition();
	glm::vec3 cameraUpVector = camera->getUpVector();
	glm::vec3 cameraCenter = cameraPosition + camera->getDirection();

	glm::mat4 viewMatrix = glm::lookAt(
		cameraPosition,
		cameraCenter,
		cameraUpVector
	);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), windowWidth / (float)windowHeight, 0.1f, 1000.0f);
	//Draw Skybox
	skyboxDay->draw(skyboxShader, viewMatrix, projectionMatrix, elapsedTime);
	//Draw Scene objects
	for (SceneObject* object : objects)
	{
		object->drawSceneObject(objectShader, viewMatrix, projectionMatrix);
	}
	//Setting up stencil buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	CHECK_GL_ERROR();
	//Draw plants (clickable objects)
	for (SceneObject* object : plants)
	{
		glStencilFunc(GL_ALWAYS, object->getID(), -1);
		CHECK_GL_ERROR();
		object->drawSceneObject(objectShader, viewMatrix, projectionMatrix);
	}
	//Draw Point lights (they have models, for example a lamp)
	for (PointLightObject* light : lamps)
	{
		glStencilFunc(GL_ALWAYS, light->getID(), -1);
		CHECK_GL_ERROR();
		light->drawLightModel(objectShader, viewMatrix, projectionMatrix);
	}
	//Draw Spot lights 
	for (SpotLightObject* light : spotlights)
	{
		glStencilFunc(GL_ALWAYS, light->getID(), -1);
		CHECK_GL_ERROR();
		light->drawLightModel(objectShader, viewMatrix, projectionMatrix);
	}
	glDisable(GL_STENCIL_TEST);
	//Draw active explosions
	glDisable(GL_DEPTH_TEST);
	for (Explosion* explosion : explosions)
	{
		explosion->drawExplosion(billboardShader, viewMatrix, projectionMatrix, elapsedTime);
	}
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void Application::handleTimer()
{
	elapsedTime = 0.001f * glutGet(GLUT_ELAPSED_TIME);
	updateModels(elapsedTime);
	if (checkCollisions(camera, objects))
		glutLeaveMainLoop();
	updateSun();

	glutPostRedisplay();
}

