#version 330 core
	
in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Albedo;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform vec3 CameraPos;

const float pi = 3.1415926535897932384626433832795f;
const float invPi = 0.31830988618379067153776752674503f;

void main()
{
	vec3 viewVec = normalize(CameraPos - v_Position);

	float gamma = 2.2f;
	vec3 albedo = pow(texture(u_Albedo, v_TexCoord).rgb, vec3(gamma));
	
	float ka = 0.25f;
	vec3 ambient = ka * albedo;
	
	float radianceScalingLight = 3.25f;
	vec3 lightRadiance = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightDir = normalize(vec3(0.0f, 0.0f, 1.0f));
	
	float kd = 0.85f;

	vec3 brdfDiffuse = kd * albedo * invPi;
	vec3 emittedRadiance = radianceScalingLight * lightRadiance;
	
	float nDotL = clamp(dot(lightDir, v_Normal), 0.5f, 1.0f);
	
	float ks = 1.0f - kd;
	float exp = 25.0f;
	vec3 halfVector = normalize(viewVec + lightDir);
	vec3 brdfSpecular = ks * pow(clamp(dot(halfVector, v_Normal), 0.0f, 1.0f), exp) * lightRadiance;
	
	
	vec3 radiance = ambient + 
	brdfDiffuse * emittedRadiance * nDotL + 
	brdfSpecular * emittedRadiance * nDotL;
	
	o_Color = vec4( radiance, 1.0f);
	//o_Color = vec4(v_TexCoord, 0.0f, 1.0f);
	//o_Color = vec4(viewVec, 1.0f);

}