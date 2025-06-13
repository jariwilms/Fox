#version 460 core

#include "shared/shared.spl"

layout(binding  = 0) uniform sampler2D c_Environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;

void main()
{		
    const vec2 uv    = sample_spherical_map(normalize(v_Position));
    const vec3 color = texture(c_Environment, uv).rgb;
	
    f_Color = vec4(color, 1.0);
}
