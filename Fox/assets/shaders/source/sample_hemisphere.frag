#version 460 core

layout(binding  = 0) uniform samplerCube environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;



const float PI = 3.14159265359;

void main()
{
    const vec3  normal     = normalize(v_Position);
	const vec3  right      = normalize(cross(vec3(0.0, 1.0, 0.0), normal));
	const vec3  up         = normalize(cross(normal, right));
	
	      float samples    = 0.0;
	const float delta      = 0.025;
          vec3  irradiance = vec3(0.0);

    for(float phi = 0.0; phi < 2.0 * PI; phi += delta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += delta)
        {
            const vec3 tangent   = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            const vec3 direction = tangent.x * right + tangent.y * up + tangent.z * normal;

            irradiance += texture(environment, direction).rgb * cos(theta) * sin(theta);
            ++samples;
        }
    }
	
    const vec3 average = PI * irradiance * (1.0 / samples);
    
    f_Color = vec4(average, 1.0);
}
