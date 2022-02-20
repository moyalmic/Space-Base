#pragma once
#include "pgr.h"
#include "ShaderProgram.h"

#define CAMERA_PITCH_MAX 85.0f
///Class that holds information about the camera
/**
* This class contains information necessary to move and update the camera, for example
* it's position, upVector and center. It also contains other utilities like speed, yaw and pitch
* and information about it's state (free mode or static)
*/
class CameraObject
{
private:
	glm::vec3 position;
	glm::vec3 upVector;
	glm::vec3 direction;
	glm::vec3 leftVector;
	float pitch;
	float yaw;
	float speed;

	bool freeMode;
	int view;
	void checkBounds();
public:
	CameraObject();
	CameraObject(glm::vec3 pos, glm::vec3 upVec, glm::vec3 dir, glm::vec3 leftVec, float pitch, float yaw, float speed, bool freeMode);
	void update(int x, int y, int winHeight, int winWidth);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPosition);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 newDirection);
	void setDirection(float pitch, float yaw);
	glm::vec3 getUpVector();
	void setUpVector(glm::vec3 newUpVector);
	glm::vec3 getLeftVector();
	void setLeftVector(glm::vec3 newLeftVector);
	float getPitch();
	void setPitch(float newPitch);
	float getYaw();
	void setYaw(float newYaw);
	float getSpeed();
	void setSpeed(float newSpeed);
	float getSize();
	void moveForward();
	void moveLeft();
	void moveRight();
	void moveBack();
	void moveUp();
	void moveDown();
	void updateShaderPosition(ObjectShaderProgram& shader);
	bool isFree();
	void changeMode();
	void changeView();
	
};