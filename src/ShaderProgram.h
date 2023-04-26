#pragma once
#include "pgr.h"
///Class holds all information necessary for a shader program
/**
* This class has three subclasses, each with it's own attributes
* depending on what is needed in the specific type.
* All subclasses share a virtual method called initializeShaders which
* loads the shader code, compiles it into a program and readies the locations
* of all attributes and uniforms.
*/
class ShaderProgram 
{
public:
	ShaderProgram();
	virtual void initializeShaders() = 0;
};

class ObjectShaderProgram : public ShaderProgram 
{
public:
	//Shader program identifier
	GLuint program;
	// Vertex attributes locations
	GLint posLocation;
	GLint colorLocation;    
	GLint normalLocation;    
	GLint UVLocation;  
	// Matrix locations
	GLint PVMmatrixLocation;    
	GLint VmatrixLocation;      
	GLint MmatrixLocation;      
	GLint normalMatrixLocation; 
	//Material locations
	GLint MambientLocation;
	GLint MdiffuseLocation;
	GLint MspecularLocation;
	GLint MshininessLocation;
	//Directional light locations
	GLint DLpositionLocation;
	GLint DLambientLocation;
	GLint DLdiffuseLocation;    
	GLint DLspecularLocation;  
	GLint DLintensityLocation;
	//Point light locations
	GLint PLpositionLocation;
	GLint PLambientLocation;
	GLint PLdiffuseLocation;
	GLint PLspecularLocation;
	GLint PLintensityLocation;
	GLint PLconstantLocation;
	GLint PLlinearLocation;
	GLint PLquadraticLocation;
	GLint PLonLocation;
	//Spot light locations
	GLint SLpositionLocation;
	GLint SLambientLocation;
	GLint SLdiffuseLocation;
	GLint SLspecularLocation;
	GLint SLintensityLocation;
	GLint SLdirectionLocation;
	GLint SLinnerCutoffLocation;
	GLint SLouterCutoffLocation;
	GLint SLonLocation;
	//Texture locations
	GLint texSamplerLocation; 
	//Fog locations
	GLint fogDensityLocation;
	GLint fogGradientLocation;
	GLint fogStartLocation;
	GLint fogEndLocation;
	GLint fogColorLocation;
	//Camera position
	GLint cameraPositionLocation;

	using ShaderProgram::ShaderProgram;
	void initializeShaders();
};

class SkyboxShaderProgram : public ShaderProgram
{
public:
	GLuint program;

	GLint dayScreenCoordLocation;
	GLint nightScreenCoordLocation;

	GLint PVmatrixLocation;
	GLint skyboxSamplerLocation;
	GLint timeLocation;

	using ShaderProgram::ShaderProgram;
	void initializeShaders();
};

class BillboardShaderProgram : public ShaderProgram
{
public:
	GLuint program;
	GLint posLocation;
	GLint texCoordLocation;
	GLint PVMmatrixLocation;
	GLint VmatrixLocation;
	GLint timeLocation;
	GLint texSamplerLocation;
	GLint frameDurationLocation;

	using ShaderProgram::ShaderProgram;
	void initializeShaders();
};