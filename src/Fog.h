#pragma once
#include "pgr.h"
#include "ShaderProgram.h"

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