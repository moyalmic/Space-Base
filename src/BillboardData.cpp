#include "BillboardData.h"

BillboardData::BillboardData(std::string fileName, BillboardShaderProgram& shader)
{
	numberOfVertices = 4;
	const float explosionVertexData[4 * 5] = {
		  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		   1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		  -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		   1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	};

	texture = pgr::createTexture(fileName);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(explosionVertexData), explosionVertexData, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(shader.posLocation);
	glVertexAttribPointer(shader.posLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	CHECK_GL_ERROR();
	glEnableVertexAttribArray(shader.texCoordLocation);
	glVertexAttribPointer(shader.texCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glBindVertexArray(0);
}
