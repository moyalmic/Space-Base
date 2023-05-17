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

//-----------------------------------------------
/**
*
* \file       Skybox.h
* \author     Michael Moyal
* \date       2023/17/05
* \brief      Class that holds information about the skybox, including texture and buffers
*/
//-----------------------------------------------
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