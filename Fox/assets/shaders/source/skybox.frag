#version 450 core

layout(set = 0, binding = 1) uniform samplerCube t_Skybox;

layout(location = 0) in vec3 v_TexCoord;
layout(location = 0) out vec4 f_Color;

void main() {
    vec3 texColor = texture(t_Skybox, v_TexCoord).rgb;
	
    f_Color = vec4(texColor, 1.0);
}
