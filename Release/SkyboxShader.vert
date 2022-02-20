# version 140

in vec2 dayScreenCoord;

out vec3 texCoords;

uniform mat4 PVmatrix;
uniform float time;

void main()
{
	vec4 farplaneCoord = vec4(dayScreenCoord, 0.9999, 1.0);
	vec4 worldViewCoord = PVmatrix * farplaneCoord;
	texCoords = worldViewCoord.xyz / worldViewCoord.w;
	texCoords += (time * 1.1f);
	gl_Position = farplaneCoord;
}