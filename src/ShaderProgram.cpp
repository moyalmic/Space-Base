#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

void ObjectShaderProgram::initializeShaders()
{
	std::vector<GLuint> shaders;
	shaders.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "LightingPerFragment.vert"));
	shaders.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "LightingPerFragment.frag"));

	program = pgr::createProgram(shaders);
	CHECK_GL_ERROR();

	//Vertex attribute locations
	posLocation = glGetAttribLocation(program, "vertexPosition");
	//colorLocation = glGetUniformLocation(program, "fragmentColor"); Not needed anymore because of textures
	normalLocation = glGetAttribLocation(program, "vertexNormal");
	UVLocation = glGetAttribLocation(program, "vertexUV");
	//Matrix locations
	PVMmatrixLocation = glGetUniformLocation(program, "PVM");
	VmatrixLocation = glGetUniformLocation(program, "viewMatrix");
	MmatrixLocation = glGetUniformLocation(program, "modelMatrix");
	normalMatrixLocation = glGetUniformLocation(program, "normalMatrix");
	//Material Locations
	MambientLocation = glGetUniformLocation(program, "material.ambient");
	MdiffuseLocation = glGetUniformLocation(program, "material.diffuse");
	MspecularLocation = glGetUniformLocation(program, "material.specular");
	MshininessLocation = glGetUniformLocation(program, "material.shininess");
	//Directional Light locations
	DLpositionLocation = glGetUniformLocation(program, "sun.position");
	DLambientLocation = glGetUniformLocation(program, "sun.ambient");
	DLdiffuseLocation = glGetUniformLocation(program, "sun.diffuse");
	DLspecularLocation = glGetUniformLocation(program, "sun.specular");
	DLintensityLocation = glGetUniformLocation(program, "sun.intensity");
	//Point Light locations
	PLpositionLocation = glGetUniformLocation(program, "lamp.position");
	PLambientLocation = glGetUniformLocation(program, "lamp.ambient");
	PLdiffuseLocation = glGetUniformLocation(program, "lamp.diffuse");
	PLspecularLocation = glGetUniformLocation(program, "lamp.specular");
	PLintensityLocation = glGetUniformLocation(program, "lamp.intensity");
	PLconstantLocation = glGetUniformLocation(program, "lamp.constant");
	PLlinearLocation = glGetUniformLocation(program, "lamp.linear");
	PLquadraticLocation = glGetUniformLocation(program, "lamp.quadratic");
	PLonLocation = glGetUniformLocation(program, "lamp.on");
	//Spotlight Locations
	SLpositionLocation = glGetUniformLocation(program, "spotlight.position");
	SLambientLocation = glGetUniformLocation(program, "spotlight.ambient");
	SLdiffuseLocation = glGetUniformLocation(program, "spotlight.diffuse");
	SLspecularLocation = glGetUniformLocation(program, "spotlight.specular");
	SLintensityLocation = glGetUniformLocation(program, "spotlight.intensity");
	SLdirectionLocation = glGetUniformLocation(program, "spotlight.direction");
	SLinnerCutoffLocation = glGetUniformLocation(program, "spotlight.innerCutoff");
	SLouterCutoffLocation = glGetUniformLocation(program, "spotlight.outerCutoff");
	SLonLocation = glGetUniformLocation(program, "spotlight.on");
	//Texture sampler locations
	texSamplerLocation = glGetUniformLocation(program, "textureSampler");
	//Fog locations
	fogDensityLocation = glGetUniformLocation(program, "fog.density");
	fogGradientLocation = glGetUniformLocation(program, "fog.gradient");
	fogStartLocation = glGetUniformLocation(program, "fog.start");
	fogEndLocation = glGetUniformLocation(program, "fog.end");
	fogColorLocation = glGetUniformLocation(program, "fog.color");
	//Camera Locations
	cameraPositionLocation = glGetUniformLocation(program, "cameraPosition");
}

void SkyboxShaderProgram::initializeShaders()
{
	std::vector<GLuint> shaders;
	shaders.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "SkyboxShader.vert"));
	shaders.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "SkyboxShader.frag"));

	program = pgr::createProgram(shaders);
	CHECK_GL_ERROR();

	dayScreenCoordLocation = glGetAttribLocation(program, "dayScreenCoord");
	PVmatrixLocation = glGetUniformLocation(program, "PVmatrix");
	skyboxSamplerLocation = glGetUniformLocation(program, "skyboxSampler");
	timeLocation = glGetUniformLocation(program, "time");
}

void BillboardShaderProgram::initializeShaders()
{
	std::vector<GLuint> shaders;
	shaders.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "BillboardShader.vert"));
	shaders.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "BillboardShader.frag"));

	program = pgr::createProgram(shaders);
	CHECK_GL_ERROR();

	posLocation = glGetAttribLocation(program, "position");
	texCoordLocation = glGetAttribLocation(program, "texCoord");
	PVMmatrixLocation = glGetUniformLocation(program, "PVMmatrix");
	VmatrixLocation = glGetUniformLocation(program, "Vmatrix");
	timeLocation = glGetUniformLocation(program, "time");
	texSamplerLocation = glGetUniformLocation(program, "texSampler");
	frameDurationLocation = glGetUniformLocation(program, "frameDuration");
}
