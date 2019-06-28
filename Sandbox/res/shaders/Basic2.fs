#version 330 core

in vec3 v_Position;

uniform float u_Float;

layout(location = 0) out vec4 o_Color;

void main()
{
	//o_Color = v_Color;
	//o_Color = vec4((v_Position * 0.5f + 0.5f).rg, 0.0f, 1.0f);
	o_Color = vec4(u_Float, 0.0f, 0.0f, 1.0f);
}