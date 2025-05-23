#version 460 core

layout(binding  = 0) uniform sampler2D t_Albedo;
layout(binding  = 1) uniform sampler2D t_Normal;
layout(binding  = 2) uniform sampler2D t_ARM;

layout(location = 0) in  vec3 v_Position;
layout(location = 1) in  vec2 v_TexCoord;
layout(location = 2) in  mat3 v_TBN;

layout(location = 0) out vec3 g_Position;
layout(location = 1) out vec4 g_Albedo;
layout(location = 2) out vec3 g_Normal;
layout(location = 3) out vec3 g_ARM;

void main()
{
	vec3 normal = texture(t_Normal, v_TexCoord).rgb;
	     normal = (normal * 2.0) - 1.0;
	     normal = normalize(v_TBN * normal);
	
	g_Position  = v_Position;
	g_Albedo    = texture(t_Albedo, v_TexCoord);
	g_Normal    = normal;
	g_ARM       = texture(t_ARM,    v_TexCoord).rgb;
}
