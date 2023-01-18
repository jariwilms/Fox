#version 460 

layout (binding = 0) uniform sampler2D u_Texture;
	   
layout (location = 0) in vec3 v_Color;
layout (location = 1) in vec2 v_TexCoord;
	   
layout (location = 0) out vec4 f_Color;

void main()
{
	f_Color = vec4(v_Color, 1.0) * texture(u_Texture, v_TexCoord);
}
