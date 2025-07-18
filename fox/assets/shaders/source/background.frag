#version 460 core

layout(binding  = 0) uniform samplerCube c_Environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;
  
void main()
{
	const float gamma = 2.2;

    vec3 color  = texture(c_Environment, v_Position).rgb;
         color /= (color + vec3(1.0));
         color  = pow(color, vec3(1.0 / gamma));
	
    f_Color = vec4(color, 1.0);
}
