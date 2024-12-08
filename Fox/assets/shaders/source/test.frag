#version 460 core

layout(location = 0) in vec3 v_Normal;
//layout(location = 1) in vec3 v_Tangent;
layout(location = 1) in vec2 v_TexCoord;

layout(location = 0) out vec4 f_Color;

layout(binding = 0) uniform sampler2D t_Albedo;
layout(binding = 1) uniform sampler2D t_Normal;
layout(binding = 2) uniform sampler2D t_ARM;

void main()
{
	vec4 col = texture(t_Albedo, v_TexCoord);
	f_Color = col;
}
