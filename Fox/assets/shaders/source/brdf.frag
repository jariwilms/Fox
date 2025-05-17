#version 460 core

layout(location = 0) in  vec2 v_TexCoord;

layout(location = 0) out vec2 f_Color;



const float PI           = 3.14159265359;
const float TAU          = PI * 2;
const uint  SAMPLE_COUNT = 1024u;

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
float geometry_schlick_ggx(float normalDotViewDirection, float roughness)
{
    const float geometryFactor = pow(roughness + 1.0, 2.0) / 8.0;

    const float numerator      = normalDotViewDirection;
    const float denominator    = normalDotViewDirection * (1.0 - geometryFactor) + geometryFactor;

    return numerator / denominator;
}
float geometry_smith(vec3 normal, vec3 viewDirection, vec3 lightDirection, float roughness)
{
    const float normalDotViewDirection  = max(dot(normal, viewDirection ), 0.0);
    const float normalDotLightDirection = max(dot(normal, lightDirection), 0.0);
	
    const float viewGeometryTerm  = geometry_schlick_ggx(normalDotViewDirection , roughness);
    const float lightGeometryTerm = geometry_schlick_ggx(normalDotLightDirection, roughness);

    return viewGeometryTerm * lightGeometryTerm;
}
vec2 integrate_brdf(float normalDotViewDirection, float roughness)
{
	const vec3  normal        = vec3(0.0, 0.0, 1.0);
    const vec3  viewDirection = vec3(sqrt(1.0 - pow(normalDotViewDirection, 2.0)), 0.0, normalDotViewDirection);

          float A             = 0.0;
          float B             = 0.0;
	
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
            float geometry   = geometry_smith(normal, viewDirection, lightDirection, roughness);
            float visibility = (geometry * viewDotHalfway) / (normalDotHalfway * normalDotViewDirection);
            float fresnel    = pow(1.0 - viewDotHalfway, 5.0);

            A           += (1.0 - fresnel) * visibility;
            B           +=        fresnel  * visibility;
        }
    }
	
    A /= float(SAMPLE_COUNT);
    B /= float(SAMPLE_COUNT);
	
    return vec2(A, B);
}

void main() 
{
    f_Color = integrate_brdf(v_TexCoord.x, v_TexCoord.y);
}
