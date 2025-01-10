#version 460 core

layout(binding = 0) uniform samplerCube t_Skybox;

layout(location = 0) in  vec3 v_TexCoord;

layout(location = 0) out vec4 f_Color;

void main()
{
	f_Color	= texture(t_Skybox, v_TexCoord);
}
