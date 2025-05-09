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
layout(set = 0, binding =  6) uniform LightShadow
{
	vec4  position;
	float farPlane;
} u_LightShadow;

layout(binding  = 0) uniform sampler2D   t_Position;
layout(binding  = 1) uniform sampler2D   t_Albedo;
layout(binding  = 2) uniform sampler2D   t_Normal;
layout(binding  = 3) uniform sampler2D   t_ARM;
layout(binding  = 4) uniform samplerCube t_Shadow;

layout(location = 0) out vec4 f_Color;

float calculate_shadow(vec4 shadowPosition, vec3 normal)
{
    //Get closest depth value from light's perspective using [0,1] range v_ShadowPosition as coords
	const vec3  lightDirection = vec4(shadowPosition - u_Light.position).xyz;
	const float bias           = max((1.0 - dot(normal, lightDirection)) * 0.05, 0.005);
    const float closestDepth   = texture(t_Shadow, lightDirection).r * u_LightShadow.farPlane;
	const float currentDepth   = length(lightDirection);
	const float shadow         = step(closestDepth, currentDepth - bias);
	
    return shadow;
}
float calculate_shadow_pcf(vec4 shadowPosition, vec3 normal)
{	
	const int  SAMPLES = 20;
	const vec3 sampleOffsetDirections[SAMPLES] = vec3[]
	(
	   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
	   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1), 
	   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0), 
	   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1), 
	   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)  
	);
	
	const float viewDistance = length(u_Camera.position.xyz - shadowPosition.xyz);
	const float diskRadius   = (1.0 + (viewDistance / u_LightShadow.farPlane)) / 100.0;
	
	const vec3  lightDirection = vec4(shadowPosition - u_LightShadow.position).xyz;
	const float bias           = max((1.0 - dot(normal, lightDirection)) * 0.05, 0.005);
    const float closestDepth   = texture(t_Shadow, lightDirection).r * u_LightShadow.farPlane;
	const float currentDepth   = length(lightDirection);

	float shadow = 0.0;	
	for (int i = 0; i < SAMPLES; ++i)
	{
		const vec3  resultingOffset = sampleOffsetDirections[i] * diskRadius;
		const float closestDepth    = texture(t_Shadow, lightDirection + resultingOffset).r * u_LightShadow.farPlane;
		
		shadow += step(closestDepth, currentDepth - bias);
	}
	
	shadow /= float(SAMPLES);
	
	return shadow;
}

void main()
{
	const vec2  resolution       = u_Context.resolution;
	const vec2  uv               = gl_FragCoord.xy / resolution;
	
    const vec3  gPosition        = texture(t_Position, uv).xyz;
	const vec3  gAlbedo          = texture(t_Albedo,   uv).rgb;
    const vec3  gNormal          = texture(t_Normal,   uv).rgb;
    const float gARM             = texture(t_ARM,      uv).g;
	
	const vec3  lightPosition    = u_Light.position.xyz;
	const vec3  lightColor       = u_Light.color.rgb;
	const float lightRadius      = u_Light.radius;
	const float lightLinear      = u_Light.linear;
	const float lightQuadratic   = u_Light.quadratic;
	
	

	//Attenuation
	const float fragmentDistance = length(lightPosition - gPosition);
	const float linearFactor     = lightLinear    *     fragmentDistance;
	const float quadraticFactor  = lightQuadratic * pow(fragmentDistance, 2.0);
	const float attenuation      = 1.0 / (1.0 + linearFactor + quadraticFactor);
	
	////Ambient
	//const float ambientFactor    = 0.05;
	//const vec3  ambient          = gAlbedo * ambientFactor;
	
	//Diffuse
	const vec3  lightDirection   = normalize(lightPosition - gPosition);
	const float diffuseFactor    = max(dot(gNormal, lightDirection), 0.0);
	const vec3  diffuse          = gAlbedo * lightColor * diffuseFactor;
	
	//Specular
	const vec3  viewDirection    = normalize(u_Camera.position.xyz - gPosition);
	const vec3  bisector         = normalize(lightDirection + viewDirection);  
	const float specularFactor   = pow(max(dot(gNormal, bisector), 0.0), 8.0);
	const vec3  specular         = gARM * lightColor * specularFactor;
	
	//Lighting
	const float smoothingFactor  = smoothstep(1.0, 0.8, fragmentDistance / lightRadius);
	const float shadow           = calculate_shadow_pcf(vec4(gPosition, 1.0), gNormal);
	const vec3  lighting         = ((diffuse * attenuation) + (specular * attenuation)) * (1.0 - shadow) * smoothingFactor;
	
	
	
	f_Color = vec4(lighting, 1.0);
}
