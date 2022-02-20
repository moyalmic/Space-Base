#include "Skybox.h"


Skybox::Skybox(SkyboxShaderProgram& shader, std::string type)
{
    static const float screenCoords[] = {
   -1.0f, -1.0f,
    1.0f, -1.0f,
   -1.0f,  1.0f,
    1.0f,  1.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenCoords), screenCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(shader.dayScreenCoordLocation);
    glVertexAttribPointer(shader.dayScreenCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glUseProgram(0);
    CHECK_GL_ERROR();

    numberOfTriangles = 2;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    std::vector<std::string> images = { "right", "left", "top", "bottom", "front", "back" };

    for (int i = 0; i < 6; i++)
    {
        std::string texName = "skybox/" + type + "/" + images[i] + ".png";
        std::cout << "Loading cube map texture: " << texName << std::endl;
        if (!pgr::loadTexImage2D(texName, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i)) {
            pgr::dieWithError("Skybox cube map loading failed!");
        }
    }

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    CHECK_GL_ERROR();
}

void Skybox::draw(SkyboxShaderProgram& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, float time)
{
    glUseProgram(shader.program);

    glm::mat4 PVmatrix = projectionMatrix * viewMatrix;

    glm::mat4 viewRotation = viewMatrix;
    viewRotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 inversePVmatrix = glm::inverse(projectionMatrix * viewRotation);

    glUniformMatrix4fv(shader.PVmatrixLocation, 1, GL_FALSE, glm::value_ptr(inversePVmatrix));
    glUniform1i(shader.skyboxSamplerLocation, 0);
    glUniform1f(shader.timeLocation, time);

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, numberOfTriangles + 2);

    glBindVertexArray(0);
    glUseProgram(0);
}
