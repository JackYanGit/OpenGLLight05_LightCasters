#version 330 core							   
//in vec4 vertexColor;
in vec2 TextCoord;
in vec3 FragPos;
//法向量
in vec3 Normal;

struct Material{
	vec3 ambient; 
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct LightPoint{
	float constant;
	float linear;
	float quadratic;
};


struct LightSpot{
	float cosPhyInner;
	float cosPhyOutter;
};

uniform LightPoint lightP;
uniform LightSpot lightS;
uniform Material material;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace; 	
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

out vec4 FragColor;	
void main()								   
{		
	vec3 lightColorReal;
	vec3 lightDirReal;
	//1、LightDirection 平行光
	//lightDirReal = lightDirUniform;
	//lightColorReal = lightColor;

	//2、LightPoint 点光源
//	lightDirReal = normalize(lightPos - FragPos);
//	float dist = length(lightPos - FragPos);
//	float attenuation = 1.0 / (lightP.constant + lightP.linear * dist + 
//                lightP.quadratic * (dist * dist));
//	lightColorReal = lightColor*attenuation;

	//3、LightSpot 聚光灯
	lightDirReal = normalize(lightPos - FragPos);
	float cosTheta = dot(normalize(FragPos - lightPos),-1*lightDirUniform);
	float spotRatio = (cosTheta-lightS.cosPhyOutter)/(lightS.cosPhyInner-lightS.cosPhyOutter);
	if(cosTheta>lightS.cosPhyInner){
		//inside
		lightColorReal = lightColor;
	}else if(cosTheta>lightS.cosPhyOutter){
		//middle
		lightColorReal = lightColor*spotRatio;
	}else{
		//outside
		lightColorReal = lightColor*0.0f;
	}

	//////////////光照模型//////////////////////
	vec3 reflectVec =reflect(lightDirReal,Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);
	//specular
	float specularAmount = pow(max(dot(reflectVec,cameraVec),0.0f),material.shininess);
	vec3 specular = texture(material.specular,TextCoord).rgb*specularAmount*lightColorReal;

	//deffuse
	//vec3 diffuse =material.diffuse * max(dot(lightDir,Normal),0.0f)*lightColor;
	vec3 diffuse = texture(material.diffuse,TextCoord).rgb* max(dot(lightDirReal,Normal),0.0f)*lightColorReal;

	//ambient
	vec3 ambient = texture(material.diffuse,TextCoord).rgb*ambientColor;

	//emission
	vec3 emission = texture(material.emission,TextCoord).rgb;

	//FragColor = vec4((ambient+diffuse+specular)*objColor,1.0f)+vec4(emission,1.0f);
	FragColor = vec4((ambient+diffuse+specular)*objColor,1.0f);
}											   