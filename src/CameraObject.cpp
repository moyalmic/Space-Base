#include "CameraObject.h"

CameraObject::CameraObject() :
    position(glm::vec3(0.0f, 0.0f, 0.0f)), upVector(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), direction(glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f))),
    leftVector(glm::normalize(glm::vec3(-1.0f, 0.0f, 0.0f))), pitch(0), yaw(-90.0f), speed(2), m_FOV(60.0f), freeMode(false), m_AttachedToPlane(false), m_MovingAlongSpline(false)
{
    view = 1;
}

CameraObject::CameraObject(glm::vec3 pos, glm::vec3 upVec, glm::vec3 dir, glm::vec3 leftVec, float pitch, float yaw, float speed, bool freeMode) :
  position(pos), upVector(glm::normalize(upVec)), direction(glm::normalize(dir)), leftVector(glm::normalize(leftVec)),
  pitch(pitch), yaw(yaw), speed(speed), m_FOV(60.0f), freeMode(freeMode), m_AttachedToPlane(false), m_MovingAlongSpline(false)
{
    view = 1;
}

void CameraObject::updateMouseMovement(int x, int y, int winHeight, int winWidth)
{
	float mouseSpeed = 0.1f;
	int xScreenCenter = winHeight / 2;
	int yScreenCenter = winWidth / 2;

	// Calculate pitch of camera after mouse movement
	float newPitch = this->pitch;
	newPitch -= mouseSpeed * (y - yScreenCenter);
	if (newPitch > CAMERA_PITCH_MAX)
	{
		newPitch = CAMERA_PITCH_MAX;
	}
	this->pitch = newPitch;
	// Calculate yaw of camera after mouse movement
	float newYaw = this->yaw;
	newYaw -= mouseSpeed * (xScreenCenter - x);
	this->yaw = newYaw;
	// Use the new pitch and yaw to calculate the center vector (direction) for the camera
	this->direction = glm::vec3(cos(glm::radians(newYaw)) * cos(glm::radians(newPitch)), sin(glm::radians(newPitch)), sin(glm::radians(newYaw)) * cos(glm::radians(newPitch)));
	// Calculate the left vector
	this->leftVector = glm::vec3(cos(glm::radians(newYaw) - glm::half_pi<float>()), 0, sin(glm::radians(newYaw) - glm::half_pi<float>()));
	// Calculate the new upVector
	this->upVector = glm::cross(direction, leftVector);
}

glm::vec3 CameraObject::getPosition()
{
    return position;
}

void CameraObject::setPosition(glm::vec3 newPosition)
{
    position = newPosition;
}

glm::vec3 CameraObject::getDirection()
{
    return direction;
}

void CameraObject::setDirection(glm::vec3 newDirection)
{
    direction = newDirection;
}

void CameraObject::setDirection(float pitch, float yaw)
{
    direction = glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    // Calculate the left vector
    leftVector = glm::vec3(cos(glm::radians(yaw) - glm::half_pi<float>()), 0, sin(glm::radians(yaw) - glm::half_pi<float>()));
    // Calculate the new upVector
    upVector = glm::cross(direction, leftVector);
}

glm::vec3 CameraObject::getUpVector()
{
    return upVector;
}

void CameraObject::setUpVector(glm::vec3 newUpVector)
{
    upVector = newUpVector;
}

glm::vec3 CameraObject::getLeftVector()
{
    return leftVector;
}

void CameraObject::setLeftVector(glm::vec3 newLeftVector)
{
    leftVector = newLeftVector;
}

float CameraObject::getPitch()
{
    return pitch;
}

void CameraObject::setPitch(float newPitch)
{
    pitch = newPitch;
}

float CameraObject::getYaw()
{
    return yaw;
}

void CameraObject::setYaw(float newYaw)
{
    yaw = newYaw;
}

float CameraObject::getSpeed()
{
    return speed;
}

void CameraObject::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

float CameraObject::getFOV()
{
  return m_FOV;
}

void CameraObject::setFOV(float fov)
{
  m_FOV = fov;
}

float CameraObject::getSize()
{
    return 1.0f;
}

void CameraObject::moveForward()
{
    position += direction * speed;
    checkBounds();
}

void CameraObject::moveLeft()
{
    position += leftVector * speed;
    checkBounds();
}

void CameraObject::moveRight()
{
    position -= leftVector * speed;
    checkBounds();
}

void CameraObject::moveBack()
{
    position -= direction * speed;
    checkBounds();
}

void CameraObject::moveUp()
{
    position.y += speed;
    checkBounds();
}

void CameraObject::moveDown()
{
    position.y -= speed;
    checkBounds();
}

void CameraObject::updateShaderPosition(ObjectShaderProgram& shader)
{
    glUseProgram(shader.program);
    glUniform3fv(shader.cameraPositionLocation, 1, glm::value_ptr(position));
    glUseProgram(0);
}

bool CameraObject::isFree()
{
    return freeMode;
}

void CameraObject::changeMode()
{
    freeMode = !freeMode;
}

void CameraObject::setView(int value)
{
  switch (value)
  {
    case 1:
      setPosition(glm::vec3(50.0f, 10.0f, -20.0f));
      setDirection(-10.0f, 135.0f);
      setPitch(-10.0f);
      setYaw(135.0f);
      break;
    case 2:
      setPosition(glm::vec3(-15.0f, 5.0f, -5.0f));
      setDirection(0.0f, 45.0f);
      setPitch(0.0f);
      setYaw(-45.0f);
      break;
    case 3:
      setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
      setDirection(0.0f, -45.0f);
      setPitch(-30.0f);
      setYaw(0.0f);
      break;
    default:
      break;
  }
  view = value;
}

void CameraObject::cycleView()
{
  view = ((view + 1) % 3) + 1;
  setView(view);
}

void CameraObject::togglePlaneAttach()
{
  m_AttachedToPlane = !m_AttachedToPlane;
}

bool CameraObject::attachedToPlane()
{
  return m_AttachedToPlane;
}

void CameraObject::checkBounds()
{
    if (position.x > 67.0f)
        position.x = 67.0f;
    else if (position.x < -67.0f)
        position.x = -67.0f;
    if (position.y < 0.0f)
        position.y = 0.0f;
    else if (position.y > 30.0f)
        position.y = 30.0f;
    if (position.z > 73.0f)
        position.z = 73.0f;
    else if (position.z < -73.0f)
        position.z = -73.0f;
}

void CameraObject::updateSplineMovement(float t)
{
  // Add two extra control points at the end to smoothly approach the end point
  glm::vec3 P1 = m_SplinePoints[m_SplinePoints.size() - 2];
  glm::vec3 P2 = m_SplinePoints[m_SplinePoints.size() - 1];
  glm::vec3 Q1 = 2.0f * P2 - P1;
  glm::vec3 Q2 = 2.0f * Q1 - P2;
  std::vector<glm::vec3> extendedControlPoints = m_SplinePoints;
  extendedControlPoints.push_back(Q1);
  extendedControlPoints.push_back(Q2);

  // Calculate the index of the control point corresponding to t
  int p = int(t * float(extendedControlPoints.size() - 3));
  t = t * float(extendedControlPoints.size() - 3) - float(p);

  // Calculate the position on the spline curve corresponding to t
  glm::vec3 A = extendedControlPoints[p];
  glm::vec3 B = extendedControlPoints[p + 1];
  glm::vec3 C = extendedControlPoints[p + 2];
  glm::vec3 D = extendedControlPoints[p + 3];

  glm::vec3 P = 0.5f * (
    (-A + 3.0f * B - 3.0f * C + D) * (t * t * t)
    + (2.0f * A - 5.0f * B + 4.0f * C - D) * (t * t)
    + (-A + C) * t
    + 2.0f * B);

  setPosition(P);
}

void CameraObject::toggleMoveAlongSpline()
{
  m_MovingAlongSpline = !m_MovingAlongSpline;
}

bool CameraObject::movingAlongSpline()
{
  return m_MovingAlongSpline;
}

void CameraObject::addPointToSpline(const glm::vec3& point)
{
  m_SplinePoints.push_back(point);
}
