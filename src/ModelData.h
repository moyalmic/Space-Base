#pragma once
#include <iostream>
#include "Material.h"
#include "pgr.h"
#include "ShaderProgram.h"

///Class that holds and manipulates 3D model data
/**
* This class loads data from .obj (or C array) files and stores them along with
* their appropriate vbo, ebo and vao. Also contains information about the texture
*/
class ModelData
{
private:
	int numberOfTriangles;
	GLuint vbo, ebo, vao;
	// material
	Material* modelMaterial;
	// texture
	GLuint        texture;
public:
	ModelData();
	ModelData(std::string fileName, ObjectShaderProgram& shader);
	bool loadModelFromArray(ObjectShaderProgram& shader, std::string textureFile, const int numberOfVertices, const float* vertices, 
		const int numberOfTriangles = 0, const unsigned* triangles = nullptr);
	GLuint getVAO();
	GLuint getVBO();
	GLuint getTexture();
	Material* getMaterial();
	int getTringleCount();
};