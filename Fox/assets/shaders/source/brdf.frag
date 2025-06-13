#version 460 core

//#include "shared/shared.spl"
#include "shared/hammersley.spl"
#include "shared/importance_sample_ggx.spl"

layout(location = 0) in  vec2 v_TexCoord;

layout(location = 0) out vec2 f_Color;

const uint SAMPLE_COUNT = 1024u;

//THIS FUNCTION IS DIFFERENT FROM GEOMETRY_SCHLICK_GGX !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
float geometry_schlick(float NdotV, float roughness)
{
    // note that we use a different k for IBL
    float a = roughness;
    float k = (a * a) / 2.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float geometry_smith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = geometry_schlick(NdotV, roughness);
    float ggx1 = geometry_schlick(NdotL, roughness);

    return ggx1 * ggx2;
}

vec2 integrate_brdf(float normalDotViewDirection, float roughness)
{
	const vec3  normal        = vec3(0.0, 0.0, 1.0);
    const vec3  viewDirection = vec3(sqrt(1.0 - pow(normalDotViewDirection, 2.0)), 0.0, normalDotViewDirection);
	
          float F0            = 0.0;
          float F90           = 0.0;
	
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        const vec2  Xi                      = hammersley(i, SAMPLE_COUNT);
        const vec3  halfway                 = importance_sample_ggx(Xi, normal, roughness);
        const vec3  lightDirection          = normalize(2.0 * dot(viewDirection, halfway) * halfway - viewDirection);
	
        const float normalDotLightDirection = max(lightDirection.z, 0.0);
        const float normalDotHalfway        = max(halfway.z, 0.0);
        const float viewDotHalfway          = max(dot(viewDirection, halfway), 0.0);
	
        if(normalDotLightDirection > 0.0)
        {
            float geometry     = geometry_smith(normal, viewDirection, lightDirection, roughness);
            float visibility   = (geometry * viewDotHalfway) / (normalDotHalfway * normalDotViewDirection);
            float coefficient  = pow(1.0 - viewDotHalfway, 5.0);
	
            F0                += (1.0 - coefficient) * visibility;
            F90               +=        coefficient  * visibility;
        }
    }
	
    F0  /= float(SAMPLE_COUNT);
    F90 /= float(SAMPLE_COUNT);
	
    return vec2(F0, F90);
}

void main() 
{
    f_Color = integrate_brdf(v_TexCoord.x, v_TexCoord.y);
}
