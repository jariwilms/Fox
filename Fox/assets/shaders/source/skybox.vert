#version 460 core

layout(set = 0, binding = 1) uniform UMatrices
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_Matrices;

layout(location = 0) in  vec3 a_Position;

layout(location = 0) out vec3 v_TexCoord;

void main()
{
	v_TexCoord = a_Position;
	
	vec4 worldPosition = u_Matrices.projection * mat4(mat3(u_Matrices.view)) * vec4(a_Position, 1.0);
	gl_Position = worldPosition.xyww;
}
