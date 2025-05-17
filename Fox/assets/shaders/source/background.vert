#version 460 core

#include "uniform/matrices.unf"

layout (location = 0) in  vec3 a_Position;

layout (location = 0) out vec3 v_Position;

void main()
{
    v_Position = a_Position;

    vec4 position = u_Matrices.projection * mat4(mat3(u_Matrices.view)) * vec4(v_Position, 1.0);

    gl_Position = position.xyww;
}
