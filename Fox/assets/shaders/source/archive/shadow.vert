#version 450

struct ViewProjection
{
    mat4 u_view;
    mat4 u_projection;
};

uniform ViewProjection u_ViewProjection;

in vec3 position;

out vec3 v_position;

void main()
{
	v_position = position; //projection * view * model * position
}