#version 460 core

layout(binding  = 0) uniform samplerCube c_Environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;



const float PI  = 3.14159265359;
const float TAU = PI * 2;

void main()
{
    const vec3  forward    = normalize(v_Position);
	const vec3  right      = normalize(cross(vec3(0.0, 1.0, 0.0), forward));
	const vec3  up         = normalize(cross(forward, right));
	
	      uint  samples    = 0u;
          vec3  irradiance = vec3(0.0);
	const float delta      = TAU / 1024;
	
    for(float phi = 0.0; phi < TAU; phi += delta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += delta)
        {
            const vec3 tangent   = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            const vec3 direction = tangent.x * right 
			                     + tangent.y * up 
								 + tangent.z * forward;
			
            irradiance += texture(c_Environment, direction).rgb * cos(theta) * sin(theta);
            ++samples;
        }
    }
	
    const vec3 average = PI * irradiance / samples;
    
    f_Color = vec4(average, 1.0);
}
