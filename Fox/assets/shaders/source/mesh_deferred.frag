#version 460 core

layout(binding = 0) uniform sampler2D t_Albedo;
layout(binding = 1) uniform sampler2D t_Normal;
layout(binding = 2) uniform sampler2D t_ARM;

layout(location = 0) in vec3 v_Normal;
layout(location = 1) in vec3 v_Tangent;
layout(location = 2) in vec2 v_TexCoord;

layout(location = 0) out vec4 g_Albedo;
layout(location = 1) out vec4 g_Normal;
layout(location = 2) out vec4 g_ARM;

void main()
{
	g_Albedo = texture(t_Albedo, v_TexCoord);
	g_Normal = texture(t_Normal, v_TexCoord);
	g_ARM    = texture(t_ARM,    v_TexCoord);
}
