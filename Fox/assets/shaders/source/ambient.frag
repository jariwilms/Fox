#version 460 core

layout(binding = 0) uniform sampler2D t_Albedo;
layout(binding = 1) uniform sampler2D t_Color;

layout(location = 0) in  vec2 v_TexCoord;

layout(location = 0) out vec4 f_Color;

void main()
{
	const vec3  albedo        = texture(t_Albedo, v_TexCoord).rgb;
	const vec3  lighting      = texture(t_Color,  v_TexCoord).rgb;
	
	
	
	const vec3  ambientColor  = vec3(1.0, 1.0, 1.0);
	const float ambientFactor = 0.05;
	const vec3  ambient       = clamp((albedo * (ambientColor * ambientFactor)) + lighting, 0.0, 1.0);
	
	
	
	f_Color = vec4(ambient, 1.0);
}
