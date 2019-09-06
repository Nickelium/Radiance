#version 330 core
	
in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Albedo;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

const float pi = 3.1415926535897932384626433832795f;
const float invPi = 0.31830988618379067153776752674503f;

void main()
{
	mat4 invV = inverse(V);
	vec3 eye = invV[3].xyz;
	vec3 viewVec = eye - v_Position;

	float ka = 0.02f;
	vec3 ambient = ka * vec3(0.25f, 0.12f, 5.0f);
	vec3 albedo = texture(u_Albedo, v_TexCoord).rgb;
	vec3 lightDir = normalize(vec3(0.0f, 0.0f, 1.0f));
	vec3 brdf = vec3(1.0f, 1.0f, 1.0f) * invPi * 2.5f;
	vec3 emittedRadiance = 1.0f * vec3(1.0f, 1.0f, 1.0f);
	vec3 radiance = ambient + albedo * brdf * emittedRadiance * clamp(dot(lightDir, v_Normal), 0.5f, 1.0f);
	
	o_Color = vec4( radiance, 1.0f);
	//o_Color = vec4(v_TexCoord, 0.0f, 1.0f);
}