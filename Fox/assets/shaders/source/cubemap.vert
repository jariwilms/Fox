#version 460 core

#include "uniform/matrices.unf"

layout(location = 0) in  vec3 a_Position;

layout(location = 0) out vec3 v_Position;

void main()
{
    v_Position = a_Position;
	
    gl_Position =  u_Matrices.projection * u_Matrices.view * vec4(a_Position, 1.0);
}
