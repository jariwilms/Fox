#version 450 core

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec2 v_TexCoords;
layout(location = 2) in vec3 v_Normal;

layout(location = 0) out vec3 g_Position;
layout(location = 1) out vec3 g_Normal;
layout(location = 2) out vec4 g_AlbedoSpecular;

layout(binding = 0) uniform sampler2D t_Diffuse;
layout(binding = 1) uniform sampler2D t_Specular;

void main()
{
    g_Position = v_Position;
	g_Normal = normalize(v_Normal);
	g_AlbedoSpecular.rgb = texture(t_Diffuse, v_TexCoords).rgb;
	g_AlbedoSpecular.a = texture(t_Specular, v_TexCoords).r;
}
