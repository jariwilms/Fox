#version 460 core

layout(set = 0, binding = 2) uniform Matrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
} u_Matrices;

layout (location = 0) in  vec3 a_Position;

layout (location = 0) out vec3 v_Position;

void main()
{
    v_Position = a_Position;
	
    gl_Position =  u_Matrices.projection * u_Matrices.view * vec4(a_Position, 1.0);
}