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

    vec4 position = u_Matrices.projection * mat4(mat3(u_Matrices.view)) * vec4(v_Position, 1.0);

    gl_Position = position.xyww;
}
