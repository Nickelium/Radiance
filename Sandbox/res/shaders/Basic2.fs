#version 330 core

in vec3 v_Position;

layout(location = 0) out vec4 o_Color;

void main()
{
	//o_Color = v_Color;
	o_Color = vec4((v_Position * 0.5f + 0.5f).rg, 0.0f, 1.0f);
}