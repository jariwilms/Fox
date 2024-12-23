#version 460 core

layout(location = 0) in  vec3 a_Position;
layout(location = 1) in  vec3 a_Normal;
layout(location = 2) in  vec3 a_Tangent;
layout(location = 3) in  vec3 a_Bitangent;
layout(location = 4) in  vec2 a_TexCoord;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec3 v_Normal;
layout(location = 2) out vec2 v_TexCoord;

layout(set = 0, binding = 0) uniform MatricesBuffer
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_MatricesBuffer;

void main()
{
	vec4 worldPosition = u_MatricesBuffer.model * vec4(a_Position, 1.0);

	v_Position = worldPosition.xyz;
	v_TexCoord = a_TexCoord;

	gl_Position = u_MatricesBuffer.projection * u_MatricesBuffer.view * worldPosition;
}
