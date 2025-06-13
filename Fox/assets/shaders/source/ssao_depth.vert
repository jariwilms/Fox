#version 460 core

#include "uniform/matrices.unf"

layout(location = 0) in  vec3 a_Position;

void main()
{
	gl_Position = u_Matrices.projection * u_Matrices.view * u_Matrices.model * vec4(a_Position, 1.0);
}
