#version 460 core

layout(location = 0) out float f_Color;

void main()
{
	f_Color = gl_FragCoord.z;
}
