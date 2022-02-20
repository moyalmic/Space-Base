#version 140

in vec3 texCoords;

uniform samplerCube skyboxSampler;

out vec4 fragColor;

void main()
{
	fragColor = texture(skyboxSampler, texCoords);
}