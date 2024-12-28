#version 460 core

layout(set = 0, binding = 1) uniform MatricesBuffer
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_MVP;

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = u_MVP.projection * u_MVP.view * u_MVP.model * vec4(a_Position, 1.0);
}
