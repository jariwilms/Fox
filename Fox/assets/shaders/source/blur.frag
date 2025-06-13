#version 460  core

#include "settings/settings.spl"

layout(binding  = 0) uniform sampler2D t_SSAO;

layout(location = 0) in  vec2  v_TexCoord;

layout(location = 0) out float f_Color;

void main() 
{
    const vec2 texelSize = 1.0 / vec2(textureSize(t_SSAO, 0));
    
	float result = 0.0;
    for (int x = -2; x < 2; ++x)
    {
        for (int y = -2; y < 2; ++y)
        {
			result += texture(t_SSAO, v_TexCoord + (vec2(x, y) * texelSize)).r;
        }
    }
	
    f_Color = result / pow(BLUR_FACTOR, 2.0);;
}  