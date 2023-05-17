#pragma once
#include "pgr.h"
#include "ShaderProgram.h"


//-----------------------------------------------
/**
*
* \file       Fog.h
* \author     Michael Moyal
* \date       2023/17/05
* \brief      Class that holds information about the fog settings
*
*/
//-----------------------------------------------
class Fog
{
private:
	float m_Density;
	float m_Gradient;
	float m_FogStart;
	float m_FogEnd;
	glm::vec3 color;
public:
	Fog(float density, float gradient, float fogStart, float fogEnd, glm::vec3 color);
	void setupFog(ObjectShaderProgram& shader);
};