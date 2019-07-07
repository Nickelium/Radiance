#version 330 core
	
in vec4 v_Color;
in vec3 v_Position;

layout(location = 0) out vec4 o_Color;

uniform mat4 V;
uniform mat4 P;
uniform mat4 VP;

void main()
{
	o_Color = v_Color;
	//o_Color = vec4((v_Position * 0.5f + 0.5f).rg, 0.0f, 1.0f);
}