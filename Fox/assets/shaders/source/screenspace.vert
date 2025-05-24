#version 460 core

layout(location = 0) in  vec3 a_Position;

layout(location = 0) out vec2 v_TexCoord;

void main()
{
	v_TexCoord = (a_Position.xy + 1.0) / 2.0;
	
	gl_Position = vec4(a_Position, 1.0);
}
