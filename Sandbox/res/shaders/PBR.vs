#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

//World space position
out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main()
{
	gl_Position = P * V * M * vec4(a_Position, 1.0f);
	v_Position = (M * vec4(a_Position, 1.0f)).xyz;
	v_Normal = mat3(M) * a_Normal;
	v_TexCoord = a_TexCoord;
}