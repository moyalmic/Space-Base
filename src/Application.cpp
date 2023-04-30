#include "Application.h"

void Application::addModelName(string modelName)
{
	m_ModelNames.push_back(modelName);
}

void Application::initializeModels()
{
	//All objects that are imported through .obj
	for (string modelName : m_ModelNames)
	{
		string temp = modelName.substr(7, modelName.size() - 4 - 7);
		m_Models[temp] = new ModelData(modelName, m_ObjectShader);
	}
	//Adding base with array instead of .obj
	ModelData* lamp = new ModelData();
	lamp->loadModelFromArray(m_ObjectShader, "models/LampTex.png", lampNVertices, lampVertices, lampNTriangles, lampTriangles);
	m_Models["lamp"] = lamp;
}

void Application::initializeObjects()
{
	m_Objects.push_back(new SceneObject(0, glm::vec3(0.0f, 15.0f, 0.0f), 0.0f, 180.0f, -30.0f, 0.0f, 3.0f, m_Models["spaceship"]));
	m_Objects.push_back(new SceneObject(0, glm::vec3(0.0f, 13.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, 75.0f, m_Models["terrain"]));
	m_Objects.push_back(new SceneObject(0, glm::vec3(-15.0f, 4.5f, -20.0f), 0.0f, 37.5f, 0.0f, 0.0f, 7.0f, m_Models["base"]));
	m_Objects.push_back(new SceneObject(0, glm::vec3(-8.0f, 2.5f, -16.0f), 0.0f, -52.5f, 0.0f, 0.0f, 1.5f, m_Models["military_box"]));
	m_Objects.push_back(new SceneObject(0, glm::vec3(12.0f, 4.0f, -4.0f), 0.0f, 90.0f, 0.0f, 0.0f, 2.0f, m_Models["signpost"]));

	vector<glm::vec3> positions = {glm::vec3(-10.0f, 3.2f, 15.0f), glm::vec3(10.0f, 3.5f, -40.0f), glm::vec3(-35.0f, 4.3f, 37.0f), glm::vec3(46.0f, 11.0f, 49.0f)};
	//Randomness for rock scaling and orientation
	std::mt19937 gen(std::random_device{}()); // seed the generator
	std::uniform_real_distribution<> distrScale(m_RockScaling.first, m_RockScaling.second); // define the range
	std::uniform_real_distribution<> distrPitch(0.0f, 360.0f); // define the range

	//Randomness for rock type
	std::discrete_distribution<int> distrType(m_RockDistribution.begin(), m_RockDistribution.end());

	for (const auto& pos : positions)
	{
		string modelName = "rock" + to_string(distrType(gen) + 1);
		m_Objects.push_back(new SceneObject(3, pos, distrPitch(gen), 0.0f, 0.0f, 0.0f, distrScale(gen), m_Models[modelName]));
	}
	
}

void Application::initializeCamera()
{
	m_Camera = new CameraObject(glm::vec3(10.0f, 7.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		0.0f, -90.0f, 1, false);
}

void Application::initializeLights()
{
	//Directional light (the sun)
	m_Sun = new DirectionalLightObject();
	m_Sun->setIntensity(0.5f);
	m_Sun->setupLight(m_ObjectShader);
	//Point light (lamp inside shelter)
	m_Lamps.push_back(new PointLightObject(glm::vec3(-15.0f, 3.0f, -20.0f), 
		new SceneObject(1, glm::vec3(0.0f, 0.0f, 0.0f), -90.0f, 0.0f, 0.0f, 0.0f, 0.5f, m_Models["lamp"])));
	//Yes this is called for a vector, but there will only be one point light because the shader can't handle more
	for (PointLightObject* light : m_Lamps)
	{
		light->setAttenuationConstants(1.0f, 0.09f, 0.0032f);
		light->setupLight(m_ObjectShader);
	}
	//Spotlight (light ontop of shelter)
	m_Spotlights.push_back(new SpotLightObject(glm::vec3(-12.0f, 7.2f, -16.0f), 
		new SceneObject(2, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, -45.0f, 0.0f, 0.0f, 0.5f, m_Models["spotlight"])));
	for (SpotLightObject* spotlight : m_Spotlights)
	{
		spotlight->setDirection(glm::radians(0.0f), glm::radians(-45.0f));
		spotlight->setCutoffs(0.91f, 0.82f);
		spotlight->setupLight(m_ObjectShader);
	}
}

void Application::initializeSkybox()
{
	m_Skybox = new Skybox(m_SkyboxShader, SkyboxType::Day);
}

void Application::initializeFog()
{
	m_Fog = new Fog(0.0001f, 0.001f, 0.0f, 15.0f, glm::vec3(0.4f, 0.5f, 0.6f));
	m_Fog->setupFog(m_ObjectShader);
}

void Application::initializeBillboards()
{
	m_ExplosionData = new BillboardData("models/explosion.png", m_BillboardShader);
}

void Application::updateModels(float currentTime)
{
	//This erases all destoryed plants
	auto plant = m_Plants.begin();
	while (plant != m_Plants.end())
	{
		if ((*plant)->isDestroyed())
			plant = m_Plants.erase(plant);
		else
			plant++;
	}
	//This will update the explosion billboards
	auto explosion = m_Explosions.begin();
	while (explosion != m_Explosions.end())
	{
		if (m_ElapsedTime > (*explosion)->getLifetime())
			explosion = m_Explosions.erase(explosion);
		else
			explosion++;
	}
	//This moves the spaceship
	m_Objects[0]->moveAlongCircle(currentTime);
}

void Application::updateSun()
{
	glm::vec3 currentPosition = m_Sun->getPosition();

	float positionX = 0 + (float)50 * cos(-m_ElapsedTime);
	float positionY = 0 + (float)50 * sin(-m_ElapsedTime);
	
	m_Sun->setPosition(glm::vec3(positionX, positionY, currentPosition.z));
	m_Sun->updatePosition(m_ObjectShader);
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
	m_WindowWidth(width), m_WindowHeight(height), m_WindowTitle(title), m_ElapsedTime(0), m_ConfigFilename("settings/config.txt")
{
	m_MenuOption = 4;
}

void Application::initializeGlut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(m_WindowWidth, m_WindowHeight);
	glutCreateWindow(m_WindowTitle.c_str());
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

	m_ObjectShader.initializeShaders();
	m_SkyboxShader.initializeShaders();
	m_BillboardShader.initializeShaders();
	initializeSkybox();
	initializeModels();
	initializeLights();
	initializeCamera();
	initializeFog();
	initializeBillboards();
	loadConfig();
	initializeObjects();
	glutWarpPointer(m_WindowHeight / 2, m_WindowWidth / 2);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

}

void Application::handlePassiveMouse(int x, int y)
{
	if (m_Camera->isFree())
	{
		m_Camera->updateMouseMovement(x, y, m_WindowWidth, m_WindowHeight);
		glutWarpPointer(m_WindowWidth / 2, m_WindowHeight / 2);
	}
	else
		glutWarpPointer(m_WindowWidth / 2, m_WindowHeight / 2);
	
	glutPostRedisplay();
}

void Application::handleMouse(int buttonPressed, int buttonState, int mouseX, int mouseY)
{
	if (buttonPressed == GLUT_LEFT_BUTTON && buttonState == GLUT_DOWN)
	{
		unsigned char clickedObjectID;
		glReadPixels(mouseX, m_WindowHeight - 1 - mouseY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &clickedObjectID);

		switch (clickedObjectID)
		{
		case 1:
			m_Lamps[0]->toggleLight(m_ObjectShader);
			break;
		case 2:
			m_Spotlights[0]->toggleLight(m_ObjectShader);
			break;
		default:
			break;
		}
		if (clickedObjectID >= 4 && clickedObjectID <= 8)
		{
			auto it = std::find_if(m_Plants.begin(), m_Plants.end(), [&](SceneObject* const& obj) {return obj->getID() == clickedObjectID; });
			if (!(*it)->isDestroyed())
			{
				glm::vec3 explosionPosition = (*it)->getPosition();
				(*it)->destroy();
				m_Explosions.push_back(new Explosion(explosionPosition, m_ExplosionData, m_ElapsedTime, 16));
			}
		}
	}
}

void Application::handleKeyboard()
{
	//escape 
	if (m_KeyStates[27])
		glutLeaveMainLoop();
	//Modified keys come before solo ones
	else if (m_KeyStates['w'] && m_KeyStates[GLUT_ACTIVE_ALT])
	{
		if (m_Camera->isFree())
		{
			m_Camera->moveUp();
			m_Camera->updateShaderPosition(m_ObjectShader);
		}
	}
	else if (m_KeyStates['s'] && m_KeyStates[GLUT_ACTIVE_ALT])
	{
		if (m_Camera->isFree())
		{
			m_Camera->moveDown();
			m_Camera->updateShaderPosition(m_ObjectShader);
		}
	}
	else if (m_KeyStates['w'])
	{
		if (m_Camera->isFree())
		{
			m_Camera->moveForward();
			m_Camera->updateShaderPosition(m_ObjectShader);
		}
	}
	else if (m_KeyStates['s'])
	{
		if (m_Camera->isFree())
		{
			m_Camera->moveBack();
			m_Camera->updateShaderPosition(m_ObjectShader);
		}
	}
	else if (m_KeyStates['a'])
	{
		if (m_Camera->isFree())
		{
			m_Camera->moveLeft();
			m_Camera->updateShaderPosition(m_ObjectShader);
		}
	}
	else if (m_KeyStates['d'])
	{
		if (m_Camera->isFree())
		{
			m_Camera->moveRight();
			m_Camera->updateShaderPosition(m_ObjectShader);
		}
	}
	else if (m_KeyStates['q'])
		m_Camera->togglePlaneAttach();
	else if (m_KeyStates['r'])
		loadConfig();
	else if (m_KeyStates['n'])
		m_Camera->toggleMoveAlongSpline();

	//Input is handled, clear for the next frame
	m_KeyStates.clear();

	glutPostRedisplay();
}

void Application::addKeyActive(unsigned char activeKey)
{
	m_KeyStates[activeKey] = true;
}

void Application::handleSpecial(int keyPressed, int mouseX, int mouseY)
{
	switch (keyPressed)
	{
	case GLUT_KEY_LEFT:
		m_Camera->cycleView();
		break;
	case GLUT_KEY_RIGHT:
		m_Camera->cycleView();
	}
}

void Application::handleReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	m_WindowWidth = width;
	m_WindowHeight = height;
}

void Application::updateDisplay()
{
	//Handle keyboard input
	handleKeyboard();
	GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
	glClear(mask);
	//Set the cameras position to that of the plane if it should be attached
	if (m_Camera->attachedToPlane())
	{
		auto newPos = m_Objects[0]->getPosition();
		newPos.y += 2.0f; //Make the camera go above the plane
		m_Camera->setPosition(newPos);
	}
	//Set the cameras position to the appropriate point along the spline curve
	else if (m_Camera->movingAlongSpline())
	{
		std::vector<glm::vec3> testPoints = {glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(10.0f, 20.0f, 5.0f), glm::vec3(15.0f, 20.0f, -5.0f), glm::vec3(-10.0f, 20.0f, 5.0f) };
		float t = glm::sin(m_ElapsedTime) * 0.5f + 0.5f; //This produces an oscillating value between 0 and 1 based on game time
		m_Camera->updateSplineMovement(t);
	}
	//Calculate view and projection matrices
	glm::vec3 cameraPosition = m_Camera->getPosition();
	glm::vec3 cameraUpVector = m_Camera->getUpVector();
	glm::vec3 cameraCenter = cameraPosition + m_Camera->getDirection();

	glm::mat4 viewMatrix = glm::lookAt(
		cameraPosition,
		cameraCenter,
		cameraUpVector
	);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(m_Camera->getFOV()), m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	//Draw Skybox
	m_Skybox->draw(m_SkyboxShader, viewMatrix, projectionMatrix, m_ElapsedTime);
	//Draw Scene objects
	for (SceneObject* object : m_Objects)
	{
		object->drawSceneObject(m_ObjectShader, viewMatrix, projectionMatrix);
	}
	//Setting up stencil buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	CHECK_GL_ERROR();
	//Draw plants (clickable objects)
	for (SceneObject* object : m_Plants)
	{
		glStencilFunc(GL_ALWAYS, object->getID(), -1);
		CHECK_GL_ERROR();
		object->drawSceneObject(m_ObjectShader, viewMatrix, projectionMatrix);
	}
	//Draw Point lights (they have models, for example a lamp)
	for (PointLightObject* light : m_Lamps)
	{
		glStencilFunc(GL_ALWAYS, light->getID(), -1);
		CHECK_GL_ERROR();
		light->drawLightModel(m_ObjectShader, viewMatrix, projectionMatrix);
	}
	//Draw Spot lights 
	for (SpotLightObject* light : m_Spotlights)
	{
		glStencilFunc(GL_ALWAYS, light->getID(), -1);
		CHECK_GL_ERROR();
		light->drawLightModel(m_ObjectShader, viewMatrix, projectionMatrix);
	}
	glDisable(GL_STENCIL_TEST);
	//Draw active explosions
	glDisable(GL_DEPTH_TEST);
	for (Explosion* explosion : m_Explosions)
	{
		explosion->drawExplosion(m_BillboardShader, viewMatrix, projectionMatrix, m_ElapsedTime);
	}
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void Application::handleTimer()
{
	m_ElapsedTime = 0.001f * glutGet(GLUT_ELAPSED_TIME);
	updateModels(m_ElapsedTime);
	if (checkCollisions(m_Camera, m_Objects))
		glutLeaveMainLoop();
	updateSun();

	glutPostRedisplay();
}

void Application::loadConfig()
{
	//Clear the plants array because they are going to be loaded from the config again
	m_Plants.clear();

	ifstream inFile(m_ConfigFilename);
	if (!inFile.is_open())
		return;

	std::string line;
	int idx = 4; // This is a workaround for the plants to have id's and be clickable
	while (std::getline(inFile, line))
	{
		std::string delimiter = ":";
		std::string token = line.substr(0, line.find(delimiter));

		//Load the type of the skybox
		if (token == "skyboxType")
		{
			token = line.substr(line.find(delimiter)+1, line.length());

			if (token == "day")
				m_Skybox->setType(SkyboxType::Day);
			else if (token == "night")
				m_Skybox->setType(SkyboxType::Night);
			m_Skybox->loadImages();
		}
		//Load locations for the plants
		else if (token == "plant")
		{
			float x, y, z;
			std::stringstream position(line.substr(line.find(delimiter) + 1, line.length()));
			position >> x >> y >> z;

			auto pos = glm::vec3(x, y, z);									//Give the plant a random spin
			m_Plants.push_back(new SceneObject(idx, pos, 0.0f, (float)(rand() % 360), 0.0f, 0.0f, 2.0f, m_Models[token]));
			idx++;
		}
		//Load the spline curves to be used in the spline curve camera movement
		else if (token == "splinePoint")
		{
			float x, y, z;
			std::stringstream position(line.substr(line.find(delimiter) + 1, line.length()));
			position >> x >> y >> z;

			m_Camera->addPointToSpline(glm::vec3(x, y, z));
		}
		//Load procedural rock generation parameters
		else if (token == "rockDistribution")
		{
			float x, y, z;
			std::stringstream data(line.substr(line.find(delimiter) + 1, line.length()));
			data >> x >> y >> z;

			m_RockDistribution.push_back(x);
			m_RockDistribution.push_back(y);
			m_RockDistribution.push_back(z);
		}
		else if (token == "rockScaling")
		{
			float x, y;
			std::stringstream data(line.substr(line.find(delimiter) + 1, line.length()));
			data >> x >> y;

			m_RockScaling = make_pair(x, y);
		}
	}
}

void Application::toggleCameraLock()
{
	m_Camera->changeMode();
}

void Application::setCameraView(int value)
{
	m_Camera->setView(value);
}

