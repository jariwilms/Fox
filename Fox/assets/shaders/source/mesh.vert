#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec2 v_TexCoords;
layout(location = 2) out vec3 v_Normal;

layout(set = 0, binding = 0) uniform MatricesBuffer
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_MVP;
layout(set = 0, binding = 1) uniform MaterialBuffer
{
	vec4 color;
	float roughness;
	float metallic;
} u_Material;
layout(set = 0, binding = 2) uniform CameraBuffer
{
	vec4 position;
} u_Camera;

void main()
{
	vec4 WorldPosition = u_MVP.model * vec4(a_Position, 1.0);
	
	v_Position = WorldPosition.xyz;
	v_TexCoords = a_TexCoords;
	
	mat3 normalMatrix = transpose(inverse(mat3(u_MVP.model)));
	v_Normal = normalMatrix * a_Normal;
	
	gl_Position = u_MVP.projection * u_MVP.view * WorldPosition;
}
