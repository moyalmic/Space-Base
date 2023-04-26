#pragma once
#include "ShaderProgram.h"
#include "Skybox.h"
#include "ModelData.h"
#include "SceneObject.h"
#include "LightObject.h"
#include "Explosion.h"
#include "configure.h"
#include "Fog.h"
#include "pgr.h"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <sstream>

using namespace std;
///Class that holds information about the whole applicaton
/**
* This class contains all of the resources necessary for the application,
* for example models, objects, lights, shaders, etc.
*/
class Application
{
private:
	string m_WindowTitle;
	int m_WindowHeight;
	int m_WindowWidth;
	//Objects
	vector<string> m_ModelNames;
	map<string, ModelData*> m_Models;
	vector<SceneObject*> m_Objects;
	vector<SceneObject*> m_Plants;
	ObjectShaderProgram m_ObjectShader;
	//Keyboard
	std::map<unsigned char, bool> m_KeyStates;
	//Camera
	CameraObject* m_Camera;
	//Lighting
	DirectionalLightObject* m_Sun;
	vector<PointLightObject*> m_Lamps;
	vector<SpotLightObject*> m_Spotlights;
	//Skybox
	Skybox* m_Skybox;
	SkyboxShaderProgram m_SkyboxShader;
	//Billboards
	BillboardShaderProgram m_BillboardShader;
	//Fog
	Fog* m_Fog;
	//Timekeeping
	float m_ElapsedTime;
	//Explosions
	BillboardData* m_ExplosionData;
	vector<Explosion*> m_Explosions;
	//Config
	std::string m_ConfigFilename;
	//Menu
	int m_MenuOption;
	void addModelName(string modelName);
	void initializeModels();
	void initializeObjects();
	void initializeCamera();
	void initializeLights();
	void initializeSkybox();
	void initializeFog();
	void initializeBillboards();
	void initializeMenu();
	void updateModels(float currentTime);
	void updateSun();
	bool checkCollisions(CameraObject* camera, vector<SceneObject*> objects);
public:
	Application(int windowWidth, int windowHeight, string windowTitle);
	void initializeGlut(int argc, char** argv);
	void initializeResources();
	//TODO implement these as callbacks from the previous app
	void handlePassiveMouse(int x, int y);
	void handleMouse(int buttonPressed, int buttonState, int mouseX, int mouseY);
	void handleKeyboard();
	void addKeyActive(unsigned char activeKey);
	void handleSpecial(int keyPressed, int mouseX, int mouseY);
	void handleReshape(int width, int height);
	void updateDisplay();
	void handleTimer();
	void loadConfig();
	void toggleCameraLock();
	void setCameraView(int value);
};




