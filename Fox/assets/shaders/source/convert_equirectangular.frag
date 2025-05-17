#version 460 core

layout(binding  = 0) uniform sampler2D c_Environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;

const vec2 ATAN_INV = vec2(0.1591, 0.3183);

vec2 sample_spherical_map(vec3 v)
{
    vec2 uv  = vec2(atan(v.z, v.x), asin(v.y));
         uv *= ATAN_INV;
         uv += 0.5;
	
    return uv;
}

void main()
{		
    const vec2 uv    = sample_spherical_map(normalize(v_Position));
    const vec3 color = texture(c_Environment, uv).rgb;
	
    f_Color = vec4(color, 1.0);
}
