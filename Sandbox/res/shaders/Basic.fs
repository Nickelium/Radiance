#version 330 core
	
in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Albedo;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	mat4 invV = inverse(V);
	vec3 eye = invV[3].xyz;
	vec3 viewVec = eye - v_Position;



	vec3 albedo = texture(u_Albedo, v_TexCoord).rgb;
	vec3 lightDir = normalize(vec3(0.0f, 0.0f, 1.0f));
	vec3 brdf = vec3(1.0f, 1.0f, 1.0f);
	vec3 emittedRadiance = 1.0f * vec3(1.0f, 1.0f, 1.0f);
	vec3 radiance = brdf * emittedRadiance * clamp(dot(lightDir, v_Normal), 0.0f, 1.0f);
	
	o_Color = vec4( radiance * albedo, 1.0f);
}