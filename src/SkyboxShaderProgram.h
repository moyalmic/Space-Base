#pragma once
#include "pgr.h"

class SkyboxShaderProgram
{
private:
	GLuint program;

	GLint screenCoordLocation;
	GLint PVmatrixLocation;
	GLint skyboxSamplerLocation;
public:
	SkyboxShaderProgram();
	void initializeShaders();
};