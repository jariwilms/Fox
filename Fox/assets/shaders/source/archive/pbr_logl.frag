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

layout(binding  = 4) uniform samplerCube t_Irradiance;

layout(location = 0) out vec4 f_Color;



const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
void main()
{
	const vec2  resolution                  = u_Context.resolution;
	const vec2  uv                          = gl_FragCoord.xy / resolution;

	vec3 WorldPos = texture(t_Position, uv).rgb;
	vec3 albedo = texture(t_Albedo, uv).rgb;
	vec3 Normal = texture(t_Normal, uv).rgb;
	
	vec3 ARM = texture(t_ARM, uv).rgb;
	float ao        = ARM.r;
	float roughness = ARM.g;
	float metallic  = ARM.b;
	
	vec3 camPos = u_Camera.position.xyz;
	
	
	
	
	
	

    vec3 N = normalize(Normal);
    vec3 V = normalize(camPos - WorldPos);
	vec3 R = reflect(-V, N); 
	
    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
        // calculate per-light radiance
	vec3 L = normalize(u_Light.position.xyz - WorldPos);
	vec3 H = normalize(V + L);
	float distance = length(u_Light.position.xyz - WorldPos);
	float attenuation = 1.0 / (distance * distance);
	vec3 radiance = u_Light.color.rgb * attenuation;

	// Cook-Torrance BRDF
	float NDF = DistributionGGX(N, H, roughness);   
	float G   = GeometrySmith(N, V, L, roughness);      
	vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0); 
	   
	vec3 numerator    = NDF * G * F; 
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
	vec3 specular = numerator / denominator;
	
    // ambient lighting (we now use IBL as the ambient term)

    vec3 kS = fresnelSchlick(max(dot(N, V), 0.0), F0);

    vec3 kD = 1.0 - kS;

    kD *= 1.0 - metallic;	  

    vec3 irradiance = texture(t_Irradiance, N).rgb;
	irradiance /= 10.0;

    vec3 diffuse      = irradiance * albedo;

    vec3 ambient = (kD * diffuse) * ao;

    // vec3 ambient = vec3(0.002);

    

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 


    f_Color = vec4(color, 1.0);
}