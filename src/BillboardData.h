#pragma once
#include "pgr.h"
#include "ShaderProgram.h"
#include <string>

///Class that holds texture information for billboards
/**
* This class contains the buffers needed for billboard drawing.
*/
class BillboardData
{
public:
	GLuint vbo, vao, texture;
	unsigned int numberOfVertices;

	BillboardData(std::string fileName, BillboardShaderProgram& shader);
};