#version 460 core

const int NR_TRANSFORMS = 32;

layout(std140, set = 0, binding = 1) uniform UMatrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_Matrices;
layout(std140, set = 0, binding = 13) uniform ModelTransforms
{
	mat4 transform[NR_TRANSFORMS];
} u_ModelTransforms;

layout(location = 0)      in  vec3 a_Position;

layout(location = 0)      out vec3 v_Position;
layout(location = 1) flat out int  v_instanceIndex;

void main()
{
	v_Position      = a_Position;
	v_instanceIndex = gl_InstanceIndex;
	
	mat4 modelTransform = u_ModelTransforms.transform[gl_InstanceIndex];
	gl_Position = u_Matrices.projection * u_Matrices.view * modelTransform * vec4(a_Position, 1.0);
}
