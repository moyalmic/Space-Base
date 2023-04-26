#include "Fog.h"

Fog::Fog(float density, float gradient, float fogStart, float fogEnd, glm::vec3 color):
	m_Density(density), m_Gradient(gradient), m_FogStart(fogStart), m_FogEnd(fogEnd), color(color)
{

}

void Fog::setupFog(ObjectShaderProgram& shader)
{
	glUseProgram(shader.program);
	glUniform1f(shader.fogDensityLocation, m_Density);
	glUniform1f(shader.fogGradientLocation, m_Gradient);
	glUniform1f(shader.fogStartLocation, m_FogStart);
	glUniform1f(shader.fogEndLocation, m_FogEnd);
	glUniform3fv(shader.fogColorLocation, 1, glm::value_ptr(color));
	glUseProgram(0);
}
