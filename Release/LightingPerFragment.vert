#version 140

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUV;

uniform mat4 PVM;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;

out vec3 fragmentNormal;
out vec3 fragmentPosition;
out vec2 fragmentUV;
out vec4 fragmentFog;


void main()
{
	gl_Position = PVM * vec4(vertexPosition, 1.0f);
	fragmentNormal = normalize((normalMatrix * vec4(vertexNormal, 0.0f)).xyz);
	fragmentPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0f));
	fragmentUV = vertexUV;
	fragmentFog = viewMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
}