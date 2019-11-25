#version 330 core
	
in vec3 v_Position;

layout(location = 0) out vec4 o_Color;

uniform mat4 V;
uniform mat4 P;
uniform mat4 VP;

void main()
{
	o_Color = vec4((v_Position * 2.0f + 1.0f).rgb, 1.0f);
}