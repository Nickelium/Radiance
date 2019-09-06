#version 330 core

in vec3 v_Position;

uniform sampler2D u_Texture;

uniform mat4 V;
uniform mat4 P;

layout(location = 0) out vec4 o_Color;

void main()
{
	vec4 col = texture(u_Texture, v_Position.xy + vec2(0.5f, 0.5f));
	//o_Color = vec4(0.75f, 0.2f, 0.15f, 1.0f);
	//o_Color = vec4(v_TexCoords.xy, 0, 1);
	o_Color = col;//vec4(col.xyz, 1.0f);
	//o_Color = vec4(test, 0.0f, 0.0f, 1.0f);
}