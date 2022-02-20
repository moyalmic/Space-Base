#include "Explosion.h"

Explosion::Explosion(glm::vec3 position, BillboardData * data,float startTime, int textureFrames, float frameDuration, float size) :
	position(position), data(data), startTime(startTime), textureFrames(textureFrames), frameDuration(frameDuration), size(size)
{
	
}

void Explosion::drawExplosion(BillboardShaderProgram& shader, glm::mat4& viewMatrix, glm::mat4& projectionMatrix, float time)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glUseProgram(shader.program);

	// just take 3x3 rotation part of the view transform
	glm::mat4 billboardRotationMatrix = glm::mat4(
		viewMatrix[0],
		viewMatrix[1],
		viewMatrix[2],
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	// inverse view rotation
	billboardRotationMatrix = glm::transpose(billboardRotationMatrix);

	glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
	matrix = glm::scale(matrix, glm::vec3(size));
	matrix = matrix * billboardRotationMatrix; // make billboard to face the camera

	glm::mat4 PVMmatrix = projectionMatrix * viewMatrix * matrix;
	glUniformMatrix4fv(shader.PVMmatrixLocation, 1, GL_FALSE, glm::value_ptr(PVMmatrix));  // model-view-projection
	glUniformMatrix4fv(shader.VmatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));   // view
	glUniform1f(shader.timeLocation, time - startTime);
	glUniform1i(shader.texSamplerLocation, 0);
	glUniform1f(shader.frameDurationLocation, frameDuration);

	glBindVertexArray(data->vao);
	glBindTexture(GL_TEXTURE_2D, data->texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, data->numberOfVertices);

	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

float Explosion::getLifetime()
{
	return startTime + textureFrames*frameDuration;
}
