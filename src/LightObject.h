#pragma once
#include "pgr.h"
#include "SceneObject.h"
#include "ShaderProgram.h"

///Class that holds information about lights
/**
* This class contains information about light objects.
* It has three subclasses: 
* DirectionalLightObject, SpotLightObject and PointLightObject.
* Each of these have different attributes and functionality
* based on what is expected of the light type.
* 
* @author		Michael Moyal
*/

//-----------------------------------------------
/**
*
* \file       LightObject.h
* \author     Michael Moyal
* \date       2023/17/05
* \brief      Class that holds information about lights. This is a Base class for DirectionalLightObject,
*							SpotLightObject and PointLightObject.
*
*/
//-----------------------------------------------
class LightObject
{
protected:
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float intensity;
	SceneObject* lightModel;
public:
	LightObject(glm::vec3 position = glm::vec3(-30.0f, 50.0f, 20.0f), SceneObject* lightModel = nullptr, glm::vec3 ambient = glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
	
	void setIntensity(float newIntensity);
	const int getID();
	glm::vec3 getPosition();
	void updatePosition(ObjectShaderProgram& shader);
	virtual void setupLight(ObjectShaderProgram& shader) = 0;
};

class DirectionalLightObject : public LightObject
{
public:
	using LightObject::LightObject;
	void setPosition(glm::vec3 newPosition);
	void setupLight(ObjectShaderProgram& shader);
};

class PointLightObject : public LightObject
{
protected:
	float constant;
	float linear;
	float quadratic;
	bool on;
public:
	using LightObject::LightObject;
	void setPosition(glm::vec3 newPosition);
	void setAttenuationConstants(float constant, float linear, float quadratic);
	void setupLight(ObjectShaderProgram& shader);
	void drawLightModel(ObjectShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void toggleLight(ObjectShaderProgram& shader);
};

class SpotLightObject : public LightObject
{
protected:
	glm::vec3 direction;
	float innerCutoff;
	float outerCutoff;
	bool on;
public:
	using LightObject::LightObject;
	void setPosition(glm::vec3 newPosition);
	void setDirection(float pitch, float yaw);
	void setCutoffs(float innerCut, float outerCut);
	void setupLight(ObjectShaderProgram& shader);
	void drawLightModel(ObjectShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void toggleLight(ObjectShaderProgram& shader);
};
