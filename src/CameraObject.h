#pragma once
#include "pgr.h"
#include "ShaderProgram.h"
#include <vector>

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

	float m_FOV;

	bool freeMode;
	bool m_AttachedToPlane;
	//Spline movement stuff
	bool m_MovingAlongSpline;
	std::vector<glm::vec3> m_SplinePoints;

	int view;
	void checkBounds();
public:
	CameraObject();
	CameraObject(glm::vec3 pos, glm::vec3 upVec, glm::vec3 dir, glm::vec3 leftVec, float pitch, float yaw, float speed, bool freeMode);
	void updateMouseMovement(int x, int y, int winHeight, int winWidth);
	//Getters and Setters
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
	float getFOV();
	void setFOV(float fov);
	float getSize();
	//Movement commands
	void moveForward();
	void moveLeft();
	void moveRight();
	void moveBack();
	void moveUp();
	void moveDown();
	//Utilities
	void updateShaderPosition(ObjectShaderProgram& shader);
	bool isFree();
	void changeMode();
	void changeView();
	//Plane attachment stuff
	void togglePlaneAttach();
	bool attachedToPlane();
	//Spline stuff
	void toggleMoveAlongSpline();
	bool movingAlongSpline();
  void updateSplineMovement(float t);
	void addPointToSpline(const glm::vec3& point);
};