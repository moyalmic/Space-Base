#include "Fog.h"

Fog::Fog(float min, float max, glm::vec3 color):
	density(min), gradient(max), color(color)
{

}

void Fog::setupFog(ObjectShaderProgram& shader)
{
	glUseProgram(shader.program);
	glUniform1f(shader.fogDensityLocation, density);
	glUniform1f(shader.fogGradientLocation, gradient);
	glUniform3fv(shader.fogColorLocation, 1, glm::value_ptr(color));
	glUseProgram(0);
}
