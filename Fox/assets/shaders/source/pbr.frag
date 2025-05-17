#version 460 core

layout(set = 0, binding =  0) uniform Context
{
	vec2  resolution;
	vec2  mousePosition;
	float time;
	float deltaTime;
} u_Context;
layout(set = 0, binding =  1) uniform Camera
{
	vec4 position;
} u_Camera;
layout(set = 0, binding =  4) uniform Light
{
	vec4  position;
	vec4  color;
	
	float radius;
	float linear;
	float quadratic;
	
	float _padding;
} u_Light;

layout(binding  = 0) uniform sampler2D   t_Position;
layout(binding  = 1) uniform sampler2D   t_Albedo;
layout(binding  = 2) uniform sampler2D   t_Normal;
layout(binding  = 3) uniform sampler2D   t_ARM;

layout(binding  = 4) uniform samplerCube c_Irradiance;
layout(binding  = 5) uniform samplerCube c_PreFilter;
layout(binding  = 6) uniform sampler2D   t_BRDF;

layout(location = 0) out vec4 f_Color;



const float PI = 3.14159265359;

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
vec3 fresnel_schlick(float cosine, vec3 reflectance)
{
	const vec3  reflectanceFactor = 1.0 - reflectance;
	const float viewAngleFactor   = pow(clamp(1.0 - cosine, 0.0, 1.0), 5.0);
	
    return reflectance + reflectanceFactor * viewAngleFactor;
}
vec3 fresnel_schlick_roughness(float cosine, vec3 reflectance, float roughness)
{
	const vec3  reflectanceFactor = max(vec3(1.0 - roughness), reflectance) - reflectance;
	const float viewAngleFactor   = pow(clamp(1.0 - cosine, 0.0, 1.0), 5.0);

	return reflectance + reflectanceFactor * viewAngleFactor;
}   

void main()
{		
	const vec2  resolution                  = u_Context.resolution;
	const vec2  uv                          = gl_FragCoord.xy / resolution;
	const float gamma                       = 2.2;
	
	const vec3  gPosition                   =     texture(t_Position, uv).xyz;
    const vec3  gAlbedo                     = pow(texture(t_Albedo  , uv).rgb, vec3(gamma));
	const vec3  gNormal                     =     texture(t_Normal  , uv).xyz;
    const float gAmbient                    =     texture(t_ARM     , uv).r;
    const float gRoughness                  =     texture(t_ARM     , uv).g;
	const float gMetallic                   =     texture(t_ARM     , uv).b;
    
    const vec3  viewDirection               = normalize(u_Camera.position.xyz - gPosition);
	
	const vec3  baseReflectance             = vec3(0.04);
    const vec3  reflectance                 = mix(baseReflectance, gAlbedo, gMetallic);
	
	
	
          vec3  luminance                   = vec3(0.0);
	
    for(int i = 0; i < 1; ++i) 
    {
        const vec3  lightDirection          = normalize(u_Light.position.xyz - gPosition);
        const vec3  halfway                 = normalize(viewDirection + lightDirection);
        const float lightDistance           = length(u_Light.position.xyz - gPosition);
        const float lightAttenuation        = 1.0 / pow(lightDistance, 2.0);
        const vec3  lightRadiance           = u_Light.color.rgb * lightAttenuation;
		
        const float normalDistribution      = distribution_ggx(gNormal, halfway, gRoughness);
        const float geometry                = geometry_smith(gNormal, viewDirection, lightDirection, gRoughness);
        const vec3  fresnel                 = fresnel_schlick(max(dot(halfway, viewDirection), 0.0), reflectance);
        
        const vec3  numerator               = normalDistribution * geometry * fresnel;
        const float denominator             = 4.0 * max(dot(gNormal, viewDirection), 0.0) * max(dot(gNormal, lightDirection), 0.0) + 0.0001;
        const vec3  specular                = numerator / denominator;
		
        const vec3  fresnelSpecular         = fresnel;
        const vec3  fresnelDiffuse          = (1.0 - gMetallic) * (vec3(1.0) - fresnelSpecular);
		
        const float normalDotLightDirection = max(dot(gNormal, lightDirection), 0.0);

        luminance += (fresnelDiffuse * gAlbedo / PI + specular) * lightRadiance * normalDotLightDirection;
    }
    
	
	
    const vec3  fresnel                     = fresnel_schlick_roughness(max(dot(gNormal, viewDirection), 0.0), reflectance, gRoughness);
    const vec3  fresnelSpecular             = fresnel;
    const vec3  fresnelDiffuse              = (1.0 - fresnelSpecular) * (1.0 - gMetallic);
    
    const vec3  irradiance                  = texture(c_Irradiance, gNormal).rgb;
    const vec3  diffuse                     = irradiance * gAlbedo;
    
    const float maxReflectionLOD            = 4.0;
	const vec3  reflection                  = reflect(-viewDirection, gNormal);
    const vec3  preFilter                   = textureLod(c_PreFilter, reflection, gRoughness * maxReflectionLOD).rgb;
    const vec2  reflectanceDistribution     = texture(t_BRDF, vec2(max(dot(gNormal, viewDirection), 0.0), gRoughness)).rg;
    const vec3  specular                    = preFilter * (fresnel * reflectanceDistribution.x + reflectanceDistribution.y);
	
    const vec3  ambient                     = (fresnelDiffuse * diffuse + specular) * gAmbient;
    
	
	
          vec3  color                       = ambient + luminance;
                color                       = color / (color + vec3(1.0));
                color                       = pow(color, vec3(1.0 / gamma)); 
	
    f_Color = vec4(color , 1.0);
}
