#version 460 core

layout(set = 0, binding = 1) uniform UMatrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_Matrices;
layout(set = 0, binding = 5) uniform ULightSpace
{
	mat4 model;
	mat4 matrix;
} u_LightSpace;

layout(location = 0) in  vec3 a_Position;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec4 v_ShadowPosition;

void main()
{
	v_Position = a_Position;
	
	v_ShadowPosition = u_LightSpace.matrix * vec4(a_Position, 1.0);
	
	gl_Position = u_Matrices.projection * u_Matrices.view * u_Matrices.model * vec4(a_Position, 1.0);
}
