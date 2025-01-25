#version 460 core

layout(set = 0, binding = 1) uniform Matrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
} u_Matrices;

layout(location = 0) in  vec3 a_Position;

void main()
{
	gl_Position = u_Matrices.projection * u_Matrices.view * u_Matrices.model * vec4(a_Position, 1.0);
}
