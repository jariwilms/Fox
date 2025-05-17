#version 460 core

layout(set = 0, binding = 5) uniform ULightSpace
{
	mat4 model;
	mat4 matrix;
} u_LightSpace;

layout (location = 0) in vec3 a_Position;

void main()
{
    gl_Position = u_LightSpace.matrix * u_LightSpace.model * vec4(a_Position, 1.0);
}  