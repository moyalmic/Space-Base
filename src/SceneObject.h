#pragma once
#include "pgr.h"
#include "ShaderProgram.h"
#include "ModelData.h"
#include "CameraObject.h"

///Class that holds all information about a scene object
/**
* This class contains information about individual scene objects
* It holds their position, rotation represented as three angles,
* their speed, size, hitbox data and data of the model that belongs
* to this scene object
*/

class SceneObject
{
private:
	glm::vec3 position;
	float pitch;
	float yaw;
	float roll;
	float speed;
	float size;
	ModelData* modelGeometry;
	glm::vec3 color;
	glm::vec2 circleCenter;
	int circleRadius;
	const int id;
	bool destroyed;
public:
	SceneObject(const int id, glm::vec3 pos, float pitch = 0, float yaw = 0, float roll = 0, float speed = 0.0f, float size = 1.0f,
		ModelData* geometry = nullptr, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void setModelGeometry(ModelData* geometry);
	void drawSceneObject(ObjectShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void setPosition(glm::vec3 newPosition);
	void moveAlongCircle(float elapsedTime);
	const int getID();
	glm::vec3 getPosition();
	float getSize();
	void destroy();
	bool isDestroyed();
};
