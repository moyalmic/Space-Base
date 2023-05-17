#pragma once
#include "pgr.h"
#include "ShaderProgram.h"
#include <string>

//-----------------------------------------------
/**
*
* \file       BillboardData.h
* \author     Michael Moyal
* \date       2023/17/05
* \brief      Class that holds texture information for billboards
*
*/
//-----------------------------------------------
class BillboardData
{
public:
	GLuint vbo, vao, texture;
	unsigned int numberOfVertices;

	BillboardData(std::string fileName, BillboardShaderProgram& shader);
};