#include "LightObject.h"

LightObject::LightObject(glm::vec3 position, SceneObject* lightModel, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float intensity):
	position(position), lightModel(lightModel), ambient(ambient), diffuse(diffuse), specular(specular), intensity(intensity)
{
	if(lightModel != nullptr)
		lightModel->setPosition(position);
}

void LightObject::setIntensity(float newIntensity)
{
	intensity = newIntensity;
}

const int LightObject::getID()
{
	return lightModel->getID();
}

glm::vec3 LightObject::getPosition()
{
	return position;
}

void LightObject::updatePosition(ObjectShaderProgram& shader)
{
	glUniform3fv(shader.DLpositionLocation, 1, glm::value_ptr(position));
}

void DirectionalLightObject::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void DirectionalLightObject::setupLight(ObjectShaderProgram& shader)
{
	
	glUseProgram(shader.program);
	glUniform3fv(shader.DLpositionLocation, 1, glm::value_ptr(position));
	glUniform3fv(shader.DLambientLocation, 1, glm::value_ptr(ambient));
	glUniform3fv(shader.DLdiffuseLocation, 1, glm::value_ptr(diffuse));
	glUniform3fv(shader.DLspecularLocation, 1, glm::value_ptr(specular));
	glUniform1f(shader.DLintensityLocation, intensity);

	glUseProgram(0);
}

void PointLightObject::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
	lightModel->setPosition(newPosition);
}

void PointLightObject::setAttenuationConstants(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void PointLightObject::setupLight(ObjectShaderProgram& shader)
{
	on = false;
	glUseProgram(shader.program);
	glUniform3fv(shader.PLpositionLocation, 1, glm::value_ptr(position));
	glUniform3fv(shader.PLambientLocation, 1, glm::value_ptr(ambient));
	glUniform3fv(shader.PLdiffuseLocation, 1, glm::value_ptr(diffuse));
	glUniform3fv(shader.PLspecularLocation, 1, glm::value_ptr(specular));
	glUniform1f(shader.PLintensityLocation, intensity);
	glUniform1f(shader.PLconstantLocation, constant);
	glUniform1f(shader.PLlinearLocation, linear);
	glUniform1f(shader.PLquadraticLocation, quadratic);
	glUniform1i(shader.PLonLocation, on);
	glUseProgram(0);
}

void PointLightObject::drawLightModel(ObjectShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	lightModel->drawSceneObject(shader, viewMatrix, projectionMatrix);
}

void PointLightObject::toggleLight(ObjectShaderProgram& shader)
{
	on = !on;
	glUniform1i(shader.PLonLocation, on);
}

void SpotLightObject::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
	lightModel->setPosition(newPosition);
}

void SpotLightObject::setDirection(float pitch, float yaw)
{
	direction.x = position.x + glm::cos(pitch) * glm::cos(yaw);
	direction.y = position.y + glm::sin(pitch) * glm::cos(yaw);
	direction.z = position.z + glm::sin(yaw);
}

void SpotLightObject::setCutoffs(float innerCut, float outerCut)
{
	innerCutoff = innerCut;
	outerCutoff = outerCut;
}

void SpotLightObject::setupLight(ObjectShaderProgram& shader)
{
	on = false;
	glUseProgram(shader.program);
	glUniform3fv(shader.SLpositionLocation, 1, glm::value_ptr(position));
	glUniform3fv(shader.SLambientLocation, 1, glm::value_ptr(ambient));
	glUniform3fv(shader.SLdiffuseLocation, 1, glm::value_ptr(diffuse));
	glUniform3fv(shader.SLspecularLocation, 1, glm::value_ptr(specular));
	glUniform1f(shader.SLintensityLocation, intensity);
	glUniform3fv(shader.SLdirectionLocation, 1, glm::value_ptr(direction));
	glUniform1f(shader.SLinnerCutoffLocation, innerCutoff);
	glUniform1f(shader.SLouterCutoffLocation, outerCutoff);
	glUniform1i(shader.SLonLocation, on);
	glUseProgram(0);
}

void SpotLightObject::drawLightModel(ObjectShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	lightModel->drawSceneObject(shader, viewMatrix, projectionMatrix);
}

void SpotLightObject::toggleLight(ObjectShaderProgram& shader)
{
	on = !on;
	glUniform1i(shader.SLonLocation, on);
}
