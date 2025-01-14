#version 460 core

layout(binding = 0) uniform sampler2D t_Albedo;
layout(binding = 1) uniform sampler2D t_Color;

layout(location = 0) in  vec2 v_TexCoord;

layout(location = 0) out vec4 f_Color;

void main()
{
	vec3 albedo   = texture(t_Albedo, v_TexCoord).rgb;
	vec3 lighting = texture(t_Color,  v_TexCoord).rgb;
	
	vec3 ambientColor = clamp((albedo * 0.2) + lighting, 0.0, 1.0);
	
	f_Color = vec4(ambientColor, 1.0);
}
