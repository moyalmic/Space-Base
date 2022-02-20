#include "SkyboxShaderProgram.h"

SkyboxShaderProgram::SkyboxShaderProgram()
{
}

void SkyboxShaderProgram::initializeShaders()
{
	std::vector<GLuint> shaders;
	shaders.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "SkyboxShader.vert"));
	shaders.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "SkyboxShader.frag"));

	program = pgr::createProgram(shaders);
	CHECK_GL_ERROR();

	screenCoordLocation = glGetAttribLocation(program, "screenCoord");
	PVmatrixLocation = glGetUniformLocation(program, "PVmatrix");
	skyboxSamplerLocation = glGetUniformLocation(program, "skyboxSampler");
}
