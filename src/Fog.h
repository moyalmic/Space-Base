#pragma once
#include "pgr.h"
#include "ShaderProgram.h"

class Fog
{
private:
	float density;
	float gradient;
	glm::vec3 color;
public:
	Fog(float min, float max, glm::vec3 color);
	void setupFog(ObjectShaderProgram& shader);
};