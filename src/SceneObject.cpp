#include "SceneObject.h"

SceneObject::SceneObject(const int id, glm::vec3 pos, float pitch, float yaw, float roll, float speed, float size, ModelData* geometry, glm::vec3 color) :
	id(id), position(pos), pitch(pitch), yaw(yaw), roll(roll), speed(speed), size(size), modelGeometry(geometry), color(color)
{
	circleRadius = 25;
	circleCenter = glm::vec2(position.x - circleRadius, position.z);
	destroyed = false;
}

void SceneObject::setModelGeometry(ModelData* geometry)
{
	modelGeometry = geometry;
}

void SceneObject::drawSceneObject(ObjectShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::scale(glm::mat4(1.0f), (glm::vec3(1.0f, 1.0f, 1.0f) * size));

	glUseProgram(shader.program);

	glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	//Matrix information
	glUniformMatrix4fv(shader.PVMmatrixLocation, 1, GL_FALSE, glm::value_ptr(PVM));
	glUniformMatrix4fv(shader.MmatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(shader.VmatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader.normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	//Texturing
	glUniform1i(shader.texSamplerLocation, 0);  
	glActiveTexture(GL_TEXTURE0 + 0);                  
	glBindTexture(GL_TEXTURE_2D, modelGeometry->getTexture());
	//Materials
	glUniform3fv(shader.MambientLocation, 1, glm::value_ptr(modelGeometry->getMaterial()->ambient));
	glUniform3fv(shader.MdiffuseLocation, 1, glm::value_ptr(modelGeometry->getMaterial()->diffuse));
	glUniform3fv(shader.MspecularLocation, 1, glm::value_ptr(modelGeometry->getMaterial()->specular));
	glUniform1f(shader.MshininessLocation, modelGeometry->getMaterial()->shininess);
	//Drawing
	glBindVertexArray(modelGeometry->getVAO());
	glDrawElements(GL_TRIANGLES, modelGeometry->getTringleCount() * 3, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	CHECK_GL_ERROR();
}

void SceneObject::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void SceneObject::moveAlongCircle(float elapsedTime)
{
	position.x = circleCenter.x + (float)circleRadius * cos(-elapsedTime);
	position.z = circleCenter.y + (float)circleRadius * sin(-elapsedTime);

	yaw = glm::degrees(elapsedTime) + 180.0f;
}

const int SceneObject::getID() 
{
	return id;
}

glm::vec3 SceneObject::getPosition()  
{
	return position;
}

float SceneObject::getSize()
{
	return size;
}

void SceneObject::destroy()
{
	destroyed = true;
}

bool SceneObject::isDestroyed()
{
	return destroyed;
}
