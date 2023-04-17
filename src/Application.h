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

using namespace std;
///Class that holds information about the whole applicaton
/**
* This class contains all of the resources necessary for the application,
* for example models, objects, lights, shaders, etc.
*/
class Application
{
private:
	string windowTitle;
	int windowHeight;
	int windowWidth;
	//Objects
	vector<string> modelNames;
	map<string, ModelData*> models;
	vector<SceneObject*> objects;
	vector<SceneObject*> plants;
	ObjectShaderProgram objectShader;
	//Camera
	CameraObject* camera;
	//Lighting
	DirectionalLightObject* sun;
	vector<PointLightObject*> lamps;
	vector<SpotLightObject*> spotlights;
	//Skybox
	Skybox* skyboxDay;
	Skybox* skyboxNight;
	SkyboxShaderProgram skyboxShader;
	//Billboards
	BillboardShaderProgram billboardShader;
	//Fog
	Fog* fog;
	//Timekeeping
	float elapsedTime;
	//Explosions
	BillboardData* explosionData;
	vector<Explosion*> explosions;
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
	void handleKeyboard(unsigned char keyPressed, int mouseX, int mouseY);
	void handleSpecial(int keyPressed, int mouseX, int mouseY);
	void handleReshape(int width, int height);
	void updateDisplay();
	void handleTimer();
};




