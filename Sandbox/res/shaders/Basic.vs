#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
	
out vec4 v_Color;
out vec3 v_Position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
//uniform mat4 VP;


void main()
{
	gl_Position = P * V * M * vec4(a_Position, 1.0f);
	v_Color = a_Color;
	v_Position = a_Position;
}