#version 460 core

layout(set = 0, binding = 0) uniform Context
{
	vec2  resolution;
	vec2  mousePosition;
	float time;
	float deltaTime;
} u_Context;
layout(set = 0, binding = 1) uniform Camera
{
	vec4 position;
} u_Camera;
layout(set = 0, binding = 4) uniform Light
{
	vec4  position;
	vec4  color;
	
	float radius;
	float linear;
	float quadratic;
	
	float _padding;
} u_Light;

layout(binding  = 0) uniform sampler2D t_Position;
layout(binding  = 1) uniform sampler2D t_Albedo;
layout(binding  = 2) uniform sampler2D t_Normal;
layout(binding  = 3) uniform sampler2D t_ARM;

layout(location = 0) out vec4 f_Color;



const float PI = 3.14159265359;
  
float distribution_ggx(vec3 normal, vec3 halfway, float roughness)
{
    const float cosine      = pow(max(dot(normal, halfway), 0.0), 2.0);
    const float numerator   = pow(roughness, 4.0);
    const float denominator = pow((cosine * (numerator - 1.0) + 1.0), 2.0) * PI;

    return numerator / denominator;
}
float geometry_schlick_ggx(float cosine, float roughness)
{
    const float remap       = pow(roughness + 1.0, 2.0) / 8.0;
    const float numerator   = cosine;
    const float denominator = cosine * remap + (1.0 - remap);

    return numerator / denominator;
}
float geometry_smith(vec3 surfaceNormal, vec3 viewDirection, vec3 lightDirection, float roughness)
{
    const float viewAngleCosine  = max(dot(surfaceNormal, viewDirection ), 0.0);
    const float lightAngleCosine = max(dot(surfaceNormal, lightDirection), 0.0);
    const float viewOcclusion    = geometry_schlick_ggx(viewAngleCosine , roughness);
    const float lightOcclusion   = geometry_schlick_ggx(lightAngleCosine, roughness);

    return viewOcclusion * lightOcclusion;
}
vec3 fresnel_schlick(float cosine, vec3 reflectance)
{
	const vec3  factor    = 1.0 - reflectance;
	const float incidence = 1.0 - cosine;
	const float power     = pow(clamp(incidence, 0.0, 1.0), 5.0);
	
    return reflectance + factor * power;
}

void main()
{
	const vec2  resolution                  = u_Context.resolution;
	const vec2  uv                          = gl_FragCoord.xy / resolution;

    const vec3  gPosition                   =     texture(t_Position, uv).xyz;
	const vec3  gAlbedo                     = pow(texture(t_Albedo,   uv).rgb, vec3(2.2));
    const vec3  gNormal                     =     texture(t_Normal,   uv).rgb;
    const vec3  gARM                        =     texture(t_ARM,      uv).rgb;
	
	const float gAmbient                    = gARM.r;
	const float gRoughness                  = gARM.g;
	const float gMetallic                   = gARM.b;

	const vec3  cameraPosition              = u_Camera.position.xyz;
	const vec3  lightPosition               = u_Light.position.xyz;
	const vec3  lightColor                  = u_Light.color.xyz;



    const vec3  directionToCamera           = normalize(cameraPosition - gPosition);
	const vec3  directionToLight            = normalize(lightPosition  - gPosition);
	
	const vec3  dielectricReflectanceFactor = vec3(0.04); 
	const vec3  metallicReflectanceFactor   = gAlbedo;
    const vec3  reflectanceFactor           = mix(dielectricReflectanceFactor, metallicReflectanceFactor, gMetallic);
	
	const vec3  halfwayVector               = normalize(directionToCamera + directionToLight);
	const float geometryShadow              = geometry_smith(gNormal, directionToCamera, directionToLight, gRoughness);
	const vec3  fresnelReflectance          = fresnel_schlick(max(dot(halfwayVector, directionToCamera), 0.0), reflectanceFactor);       
	
	const float normalDistribution          = distribution_ggx(gNormal, halfwayVector, gRoughness);
	const vec3  specularNumerator           = normalDistribution * geometryShadow * fresnelReflectance;
	const float specularDenominator         = 4.0 * max(dot(gNormal, directionToCamera), 0.0) * max(dot(gNormal, directionToLight), 0.0) + 0.0001;
	const vec3  specular                    = specularNumerator / specularDenominator;
	
	const float normalDotLightDirection     = max(dot(gNormal, directionToLight), 0.0);
	const float fragmentDistance            = length(lightPosition - gPosition);
	const float attenuation                 = 1.0 / pow(fragmentDistance, 2.0);
	const vec3  reflectanceCoefficient      = (vec3(1.0) - fresnelReflectance) * (1.0 - gMetallic);
	const vec3  radianceFactor              = lightColor * attenuation;
	const vec3  radiance                    = (reflectanceCoefficient * gAlbedo / PI + specular) * normalDotLightDirection * radianceFactor; 

    const vec3  ambientFactor               = vec3(0.0);//vec3(0.005) * gAlbedo * gAmbient;
    
	
	
	const float gamma                       = 1.0 / 2.2;
	      vec3  color                       = ambientFactor + radiance;
		        color                       = color / (color + vec3(1.0));
				color                       = pow(color, vec3(gamma));
	
	
	
    f_Color = vec4(color, 1.0);
}  