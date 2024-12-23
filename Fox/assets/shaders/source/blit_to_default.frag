#version 460 core

layout(binding = 0) uniform sampler2D t_Position;
layout(binding = 1) uniform sampler2D t_Albedo;
layout(binding = 2) uniform sampler2D t_Normal;
layout(binding = 3) uniform sampler2D t_ARM;

layout(location = 0) in vec2 v_TexCoord;

layout(location = 0) out vec4 f_Color;

void main()
{
	f_Color = texture(t_Albedo, v_TexCoord);
}
