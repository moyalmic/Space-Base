#pragma once
#include "pgr.h"
#include "BillboardData.h"
#include "ShaderProgram.h"
#include "ModelData.h"
#include "CameraObject.h"

//-----------------------------------------------
/**
*
* \file       Explosion.h
* \author     Michael Moyal
* \date       2023/17/05
* \brief      Class that constains information about the Explosion data for explosion billboards
*
*/
//-----------------------------------------------
class Explosion
{
private:
	glm::vec3 position;
	BillboardData* data;
	int textureFrames;
	float frameDuration;
	float size;
	float startTime;
public:
	Explosion(glm::vec3 position, BillboardData* data, float startTime, int textureFrames, float frameDuration = 0.05f, float size = 1.5f);
	void drawExplosion(BillboardShaderProgram& shader, glm::mat4& viewMatrix, glm::mat4& projectionMatrix, float time);
	float getLifetime();
};