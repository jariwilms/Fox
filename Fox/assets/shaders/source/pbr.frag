#version 460 core

#include "shared/shared.spl"
#include "uniform/context.unf"
#include "uniform/camera.unf"
#include "uniform/light.unf"

layout(binding  = 0) uniform sampler2D   t_Position;
layout(binding  = 1) uniform sampler2D   t_Albedo;
layout(binding  = 2) uniform sampler2D   t_Normal;
layout(binding  = 3) uniform sampler2D   t_ARM;

layout(binding  = 4) uniform samplerCube c_Irradiance;
layout(binding  = 5) uniform samplerCube c_PreFilter;
layout(binding  = 6) uniform sampler2D   t_BRDF;

layout(location = 0) out vec4 f_Color;

void main()
{
    const float MAX_REFLECTION_LOD = 4.0;
	
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
    

	const vec3  reflection                  = reflect(-viewDirection, gNormal);
    const vec3  preFilter                   = textureLod(c_PreFilter, reflection, gRoughness * MAX_REFLECTION_LOD).rgb;
    const vec2  reflectanceDistribution     = texture(t_BRDF, vec2(max(dot(gNormal, viewDirection), 0.0), gRoughness)).rg;
    const vec3  specular                    = preFilter * (fresnel * reflectanceDistribution.x + reflectanceDistribution.y);
	
    const vec3  ambient                     = (fresnelDiffuse * diffuse + specular) * gAmbient;
    
	
	
          vec3  color                       = ambient + luminance;
                color                       = color / (color + vec3(1.0));
                color                       = pow(color, vec3(1.0 / gamma)); 
	
    f_Color = vec4(color , 1.0);
}
