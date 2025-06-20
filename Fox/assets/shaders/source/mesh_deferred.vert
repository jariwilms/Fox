#version 460 core

#include "uniform/matrices.unf"

layout(location = 0) in  vec3 a_Position;
layout(location = 1) in  vec3 a_Normal;
layout(location = 2) in  vec3 a_Tangent;
layout(location = 3) in  vec2 a_TexCoord;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec2 v_TexCoord;
layout(location = 2) out mat3 v_TBN;

void main()
{
	const vec3 N = normalize(mat3(u_Matrices.model) * a_Normal);
	const vec3 T = normalize(mat3(u_Matrices.model) * a_Tangent);
	const vec3 B = cross(N, T);
	
	v_TBN  = mat3(T, B, N);

	

	const vec4 worldPosition = u_Matrices.model * vec4(a_Position, 1.0);

	v_Position = worldPosition.xyz;
	v_TexCoord = a_TexCoord;

	gl_Position = u_Matrices.projection * u_Matrices.view * worldPosition;
}
