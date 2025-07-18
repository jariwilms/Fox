#version 460 core

#include "shared/shared.spl"
#include "uniform/prefilter.unf"

layout(binding  = 0) uniform samplerCube c_Environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;

const uint SAMPLE_COUNT = 65536u;

void main()
{		
    const vec3  normal              = normalize(v_Position);
    const vec3  reflectionDirection = normal;
    const vec3  viewDirection       = reflectionDirection;
	
	
	
          vec3  prefilteredColor    = vec3(0.0);
          float totalWeight         = 0.0;
    
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        const vec2 Xi             = hammersley(i, SAMPLE_COUNT);
        const vec3 halfway        = importance_sample_ggx(Xi, normal, u_PreFilter.roughness);
        const vec3 lightDirection = normalize(halfway * dot(viewDirection, halfway) * 2.0 - viewDirection);
		
        float normalDotLightDirection = max(dot(normal, lightDirection), 0.0);
        if(normalDotLightDirection > 0.0)
        {
            const float distribution               = distribution_ggx(normal, halfway, u_PreFilter.roughness);
            const float normalDotHalfwayDirection  = max(dot(normal , halfway      ), 0.0);
            const float halfwayDotViewDirection    = max(dot(halfway, viewDirection), 0.0);
            const float probabilityDensity         = distribution * normalDotHalfwayDirection / (4.0 * halfwayDotViewDirection) + 0.0001;
			
            const float resolution                 = float(u_PreFilter.resolution);
            const float texelSolidAngle            = 4.0 * PI / (6.0 * pow(resolution, 2.0));
            const float sampleSolidAngle           = 1.0 / (float(SAMPLE_COUNT) * probabilityDensity + 0.0001);
			
            const float mipLevel                   = u_PreFilter.roughness == 0.0 ? 0.0 : 0.5 * log2(sampleSolidAngle / texelSolidAngle);
            
            prefilteredColor                      += textureLod(c_Environment, lightDirection, mipLevel).rgb * normalDotLightDirection;
            totalWeight                           += normalDotLightDirection;
        }
    }
	
    prefilteredColor /= totalWeight;
	
    f_Color = vec4(prefilteredColor, 1.0);
}
