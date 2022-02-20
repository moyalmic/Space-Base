#version 140

struct DirectionalLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float intensity;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float intensity;

	float constant;
	float linear;
	float quadratic;
	bool on;
};

struct SpotLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float intensity;

	vec3 direction;
	float innerCutoff;
	float outerCutoff;
	bool on;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Fog
{
	float density;
	float gradient;
	vec3 color;
};

in vec3 fragmentNormal;
in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec4 fragmentFog;

uniform sampler2D textureSampler;
uniform vec3 cameraPosition;

uniform DirectionalLight sun;
uniform PointLight lamp;
uniform SpotLight spotlight;
uniform Material material;
uniform Fog fog;

out vec4 fragColor;

//Right now calculates diffuse and ambient part of the sun
vec3 directionalLight(DirectionalLight light, Material material, vec3 fragmentNormal, vec3 fragmentPosition, vec3 cameraPosition)
{
	//Ambient calculation
	vec3 ambient = light.ambient * material.ambient;
	//Diffuse calculation
	vec3 normal = normalize(fragmentNormal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float diffuseCoef = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseCoef * material.diffuse);
	//Specular calculation
	vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);	  
	float specularCoef = pow(max(dot(cameraDirection, reflectionDirection), 0.0f), 32);
	vec3 specular = light.specular * (specularCoef * material.specular);

	vec3 resultingLight = (ambient + diffuse + specular) * light.intensity;

	return resultingLight;
}
	
vec3 pointLight(PointLight light, Material material, vec3 fragmentNormal, vec3 fragmentPosition, vec3 cameraPosition)
{
	if (!light.on)
		return vec3(0.0f, 0.0f, 0.0f);

	float distance = length(light.position - fragmentPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

	//Ambient calculation
	vec3 ambient = light.ambient * material.ambient;
	ambient *= attenuation;
	//Diffuse calculation
	vec3 normal = normalize(fragmentNormal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float diffuseCoef = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseCoef * material.diffuse);
	diffuse *= attenuation;
	//Specular calculation
	vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);	  
	float specularCoef = pow(max(dot(cameraDirection, reflectionDirection), 0.0f), 32);
	vec3 specular = light.specular * (specularCoef * material.specular);
	specular *= attenuation;

	vec3 resultingLight = (ambient + diffuse + specular) * light.intensity;
	return resultingLight;
}

vec3 spotLight(SpotLight light, Material material, vec3 fragmentNormal, vec3 fragmentPosition, vec3 cameraPosition)
{
	if (!light.on)
		return vec3(0.0f, 0.0f, 0.0f);
	//Ambient calculation
	vec3 ambient = light.ambient * material.ambient;
	//Diffuse calculation
	vec3 normal = normalize(fragmentNormal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float diffuseCoef = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseCoef * material.diffuse);
	//Specular calculation
	vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);	  //toto je shininess
	float specularCoef = pow(max(dot(cameraDirection, reflectionDirection), 0.0f), 32);
	vec3 specular = light.specular * (specularCoef * material.specular);

	float theta = dot(lightDirection, normalize(light.position-light.direction)); 
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);
	
	ambient *= intensity;
	diffuse *= intensity;
	specular *= intensity;
	
	vec3 resultingLight = (ambient + diffuse + specular) * light.intensity;
	return resultingLight;
}

float FogFunc(vec4 fragFogPosition, Fog fog)
{
	float distance = length(fragFogPosition.xyz);
	float visibility = exp(-pow((distance*fog.density), fog.gradient));
	visibility = clamp(visibility, 0.0f, 1.0f);

	return visibility;
}

void main()
{
	vec3 fragmentColor = texture(textureSampler, fragmentUV).rgb;
	//Lights
	vec3 sunlight = directionalLight(sun, material, fragmentNormal, fragmentPosition, cameraPosition);
	vec3 lampLight = pointLight(lamp, material, fragmentNormal, fragmentPosition, cameraPosition);
	vec3 spot = spotLight(spotlight, material, fragmentNormal, fragmentPosition, cameraPosition);
	vec3 lighting = sunlight + lampLight + spot;
	//Coloring
	vec4 outcolor = vec4(lighting * fragmentColor, 1.0f);
	//Fog
	float fogCoef = FogFunc(fragmentFog, fog);
	fragColor = mix(vec4(fog.color, 1.0f), outcolor, fogCoef);
}