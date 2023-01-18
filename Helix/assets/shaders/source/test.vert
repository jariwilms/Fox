#version 460 

layout (std140, binding = 0) uniform Matrices
{
	mat4 u_View;
	mat4 u_Projection;
};

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;
	   
layout (location = 0) out vec3 v_Color;
layout (location = 1) out vec2 v_TexCoord;

void main()
{
	gl_Position = u_Projection * u_View * vec4(a_Position, 0.0, 1.0);
	
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
}
