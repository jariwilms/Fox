#version 460 core

layout(set = 0, binding = 1) uniform UMatrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_Matrices;

layout(location = 0) in  vec3 a_Position;

layout(location = 0) out vec3 v_Position;

void main()
{
	gl_Position = u_Matrices.projection * u_Matrices.view * u_Matrices.model * vec4(a_Position, 1.0);
}
