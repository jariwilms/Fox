#version 460 core

layout(binding = 0) uniform samplerCube environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;  
  
void main()
{
	const float gamma = 1.0 / 2.2;

    vec3 color = texture(environment, v_Position).rgb;
         color = color / (color + vec3(1.0));
         color = pow(color, vec3(gamma)); 
	
    f_Color = vec4(color, 1.0);
}