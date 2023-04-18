#pragma once
#include "pgr.h"
#include "ModelData.h"
#include "ShaderProgram.h"
#include <string>
#include <iostream>

enum SkyboxType
{
	Day,
	Night
};

///Class that holds texture information for skyboxes
/**
* This class contains the buffers needed for skybox drawing.
*/
class Skybox
{
private:
	GLuint texture, vbo, vao;
	int numberOfTriangles;
	SkyboxType m_Type;
	
public:
	Skybox(SkyboxShaderProgram& shader, const SkyboxType& type);
	void draw(SkyboxShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, float time);
	void loadImages();
	void setType(const SkyboxType& val);
};