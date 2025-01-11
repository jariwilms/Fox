#version 460 core

layout(binding = 0) uniform samplerCube t_Skybox;

layout(location = 0) in  vec3 v_TexCoord;

layout(location = 0) out vec4 f_Color;

void main()
{
	vec3 texCoord = v_TexCoord;
	texCoord.x *= -1.0;
	texCoord.y *= -1.0;
	
	f_Color	= texture(t_Skybox, texCoord);
}
