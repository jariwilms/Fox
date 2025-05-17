#version 460 core

layout(set = 0, binding = 14) uniform PreFilter
{
	uint  resolution;
	float roughness;
} u_PreFilter;

layout(binding  = 0) uniform samplerCube c_Environment;

layout(location = 0) in  vec3 v_Position;

layout(location = 0) out vec4 f_Color;



const float PI           = 3.14159265359;
const float TAU          = PI * 2;
const uint  SAMPLE_COUNT = 65536u;

float distribution_ggx(vec3 normal, vec3 halfway, float roughness)
{
    const float halfwayNormalDot        = max(dot(normal, halfway), 0.0);
    const float halfwayNormalDotSquared = pow(halfwayNormalDot, 2.0);
	
	const float alpha                   = pow(roughness, 2.0);
    const float alphaSquared            = pow(alpha    , 2.0);
	const float alphaFactor             = halfwayNormalDotSquared * (alphaSquared - 1.0) + 1.0;
	
    const float numerator               = alphaSquared;
    const float denominator             = pow(alphaFactor, 2.0) * PI;
	
    return numerator / denominator;
}
float radical_inverse_vdc(uint bits)
{
	bits = (bits << 16u) | (bits >> 16u);
	
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	
    return float(bits) * 2.3283064365386963e-10; //0x100000000
}
vec2 hammersley(uint i, uint samples)
{
	return vec2(float(i)/float(samples), radical_inverse_vdc(i));
}
vec3 importance_sample_ggx(vec2 Xi, vec3 normal, float roughness)
{
	const float alpha        = pow(roughness, 2.0);
	const float alphaSquared = pow(alpha    , 2.0);
	
	const float phi          = TAU * Xi.x;
	const float cosine       = sqrt((1.0 - Xi.y) / (1.0 + (alphaSquared - 1.0) * Xi.y));
	const float sine         = sqrt(1.0 - pow(cosine, 2.0));
	
	const vec3  halfway      = vec3(cos(phi) * sine, sin(phi) * sine, cosine);
	
	const vec3  up           = abs(normal.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	const vec3  tangent      = normalize(cross(up, normal));
	const vec3  bitangent    = cross(normal, tangent);
	
	const vec3  vector       = tangent   * halfway.x 
	                         + bitangent * halfway.y 
							 + normal    * halfway.z;
	
	return normalize(vector);
}

void main()
{		
    const vec3  normal              = normalize(v_Position);
    const vec3  reflectionDirection = normal;
    const vec3  viewDirection       = reflectionDirection;
	
	
	
          vec3  prefilteredColor    = vec3(0.0);
          float totalWeight         = 0.0;
    
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        const vec2 Xi = hammersley(i, SAMPLE_COUNT);
        const vec3 halfway = importance_sample_ggx(Xi, normal, u_PreFilter.roughness);
        const vec3 L  = normalize(halfway * dot(viewDirection, halfway) * 2.0 - viewDirection);
		
        float normalDotLightDirection = max(dot(normal, L), 0.0);
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
            
            prefilteredColor                      += textureLod(c_Environment, L, mipLevel).rgb * normalDotLightDirection;
            totalWeight                           += normalDotLightDirection;
        }
    }
	
    prefilteredColor /= totalWeight;
	
    f_Color = vec4(prefilteredColor, 1.0);
}
