#version 460 core

layout(std140, set = 0, binding = 1) uniform UMatrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_Matrices;

layout(location = 0)      in  vec3 a_Position;

layout(location = 0)      out vec3 v_Position;
layout(location = 1) flat out int  v_InstanceIndex;

void main()
{
	v_Position      = a_Position;
	v_InstanceIndex = gl_InstanceIndex;
	
	gl_Position = u_Matrices.projection * u_Matrices.view * u_Matrices.model * (vec4(a_Position, 1.0) + ((v_InstanceIndex + 1) * vec4(0.5, 0.2, 0.2, 0.0)));
}
