#version 330 core

in vec3 v_Position;
in vec2 v_TexCoords;

uniform float u_Float;
uniform sampler2D u_Texture;

uniform mat4 V;
uniform mat4 P;
uniform mat4 VP;


layout(location = 0) out vec4 o_Color;

void main()
{
	//o_Color = v_Color;
	//o_Color = vec4((v_Position * 0.5f + 0.5f).rg, 0.0f, 1.0f);
	vec4 col = texture(u_Texture, v_TexCoords);
	o_Color = vec4(u_Float, 0.0f, 0.0f, 1.0f);
	o_Color = col;
}