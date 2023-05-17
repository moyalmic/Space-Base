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
#include <random>

using namespace std;
//-----------------------------------------------
/**
* 
* \file       Application.h
* \author     Michael Moyal
* \date       2023/17/05
* \brief      This class contains all of the resources necessary for the application
* 
*/
//-----------------------------------------------
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
	//Prodecural rock parameters
	vector<float> m_RockDistribution;
	pair<float, float> m_RockScaling;
	void addModelName(string modelName);
	void initializeModels();
	void initializeObjects();
	void initializeCamera();
	void initializeLights();
	void initializeSkybox();
	void initializeFog();
	void initializeBillboards();
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




