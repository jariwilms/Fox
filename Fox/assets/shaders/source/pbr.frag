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

layout(binding  = 1) uniform samplerCube t_Irradiance;
layout(binding  = 2) uniform samplerCube t_PreFilter;
layout(binding  = 4) uniform sampler2D   t_BRDF;

layout(location = 0) out vec4 f_Color;



const float PI = 3.14159265359;
  
float distribution_ggx(vec3 gNormal, vec3 lightHalfway, float gRoughness)
{
    float a = gRoughness*gRoughness;
    float a2 = a*a;
    float NdotH = max(dot(gNormal, lightHalfway), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
float geometry_schlick_ggx(float NdotV, float gRoughness)
{
    float r = (gRoughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
float geometry_smith(vec3 gNormal, vec3 viewDirection, vec3 lightDirection, float gRoughness)
{
    float NdotV = max(dot(gNormal, viewDirection), 0.0);
    float normalDotLight = max(dot(gNormal, lightDirection), 0.0);
    float ggx2 = geometry_schlick_ggx(NdotV, gRoughness);
    float ggx1 = geometry_schlick_ggx(normalDotLight, gRoughness);

    return ggx1 * ggx2;
}
vec3 fresnel_schlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
vec3 fresnel_schlick_roughness(float cosTheta, vec3 F0, float gRoughness)
{
    return F0 + (max(vec3(1.0 - gRoughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{
	//Mapping
	//N => gNormal
	//V => viewDirection
	//R => reflectionDirection
	//L => lightDirection
	//H => lightHalfway
	//F => fresnelFactor

	const vec2  resolution          = u_Context.resolution;
	const vec2  uv                  = gl_FragCoord.xy / resolution;
	const float gamma               = 2.2;
	
	const vec3  gPosition           =     texture(t_Position, uv).xyz;
	const vec3  gAlbedo             = pow(texture(t_Albedo  , uv).rgb, vec3(gamma));
	const vec3  gNormal             =     texture(t_Normal  , uv).xyz;
	const vec3  gARM                =     texture(t_ARM     , uv).rgb;
	
	const float gAmbient            = gARM.r;
	const float gRoughness          = gARM.g;
	const float gMetallic           = gARM.b;
	
    const vec3  viewDirection       = normalize(u_Camera.position.xyz - gPosition);
    const vec3  reflectionDirection = reflect(-viewDirection, gNormal); 
	
	
	
    const float baseReflectivity    = 0.04;
    const vec3  F0                  = mix(vec3(baseReflectivity), gAlbedo, gMetallic);







    
//////////
	//Every variable here should be self-contained
	const vec3  lightPosition      = u_Light.position.xyz;
	const vec3  lightColor         = u_Light.color.rgb;
	const vec3  lightDirection     = normalize(lightPosition - gPosition);
	const vec3  lightHalfway       = normalize(viewDirection + lightDirection);
	const float lightDistance      = length(lightPosition - gPosition);
	const float lightAttenuation   = 1.0 / pow(lightDistance, 2.0);
	const vec3  lightRadiance      = lightColor * lightAttenuation;

	const float normalDistribution = distribution_ggx(gNormal, lightHalfway, gRoughness);   
	const float geometryOcclusion  = geometry_smith(gNormal, viewDirection, lightDirection, gRoughness);    
	const vec3  fresnelFactor      = fresnel_schlick(max(dot(lightHalfway, viewDirection), 0.0), F0);        
	
	const vec3  numerator          = normalDistribution * geometryOcclusion * fresnelFactor;
	const float denominator        = 4.0 * max(dot(gNormal, viewDirection), 0.0) * max(dot(gNormal, lightDirection), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
	const vec3  specular           = numerator / denominator;
	
	vec3 specularReflectance       = fresnelFactor;
	vec3 diffuseReflectance        = vec3(1.0) - specularReflectance;
	     diffuseReflectance       *= 1.0 - gMetallic;
	
	const float normalDotLight     = max(dot(gNormal, lightDirection), 0.0);        
	const vec3  outgoingLuminosity = (diffuseReflectance * gAlbedo / PI + specular) * lightRadiance * normalDotLight;
//////////









    vec3 F = fresnel_schlick_roughness(max(dot(gNormal, viewDirection), 0.0), F0, gRoughness);
    
    vec3 kS  = F;
    vec3 kD  = 1.0 - kS;
    kD      *= 1.0 - gMetallic;	  
    
    vec3 irradiance = texture(t_Irradiance, gNormal).rgb;
    vec3 diffuse    = irradiance * gAlbedo;
    
    
	
    const float maxReflectionLOD = 4.0;
    vec3 prefilteredColor = textureLod(t_PreFilter, reflectionDirection, gRoughness * maxReflectionLOD).rgb;
    vec2 brdf  = texture(t_BRDF, vec2(max(dot(gNormal, viewDirection), 0.0), gRoughness)).rg;
    vec3 specular2 = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular2) * gAmbient;
    
	
	
    vec3 color = ambient + outgoingLuminosity;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 



    f_Color = vec4(color , 1.0);
}