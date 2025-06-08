#version 460 core

layout(binding  = 0) uniform sampler2D t_Source;

layout(location = 0) in  vec2 v_TexCoord;
layout(location = 0) out vec4 f_Color;

void main()
{
	f_Color = texture(t_Source, v_TexCoord);
}
