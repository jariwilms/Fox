#version 460 core

const int NR_LIGHTS = 32;

struct Light
{
	vec4 position;
	vec4 color;
	
	float radius;
	float linear;
	float quadratic;
	float _padding;
};

layout(std140, set = 0, binding =  0) uniform Input
{
	vec2  resolution;
	float time;
	float deltaTime;
	vec2  mousePosition;
} u_Input;
layout(std140, set = 0, binding =  2) uniform Camera
{
	vec4 position;
} u_Camera;
layout(std140, set = 0, binding =  4) uniform LightBuffer
{
	Light lights[NR_LIGHTS];
} u_LightBuffer;
layout(set = 0, binding = 5) uniform ULightSpace
{
	mat4 model;
	mat4 matrix;
} u_LightSpace;
layout(set = 0, binding = 6) uniform ULightShadow
{
	vec4  position;
	float farPlane;
} u_LightShadow;
layout(std140, set = 0, binding = 12) uniform LightIndex
{
	int index;
} u_LightIndex;

layout(binding = 0) uniform sampler2D   t_Position;
layout(binding = 1) uniform sampler2D   t_Albedo;
layout(binding = 2) uniform sampler2D   t_Normal;
layout(binding = 3) uniform sampler2D   t_ARM;
layout(binding = 4) uniform samplerCube t_Shadow;

layout(location = 0) out vec4 f_Color;

float calculate_shadow(vec4 shadowPosition, vec3 normal, vec3 lightDirection)
{
    //Get closest depth value from light's perspective using [0,1] range v_ShadowPosition as coords
	const vec3  ldr          = vec4(shadowPosition - u_LightShadow.position).xyz;
	const float bias         = max((1.0 - dot(normal, ldr)) * 0.05, 0.005);
    const float closestDepth = texture(t_Shadow, ldr).r * u_LightShadow.farPlane;
	const float currentDepth = length(ldr);
	const float shadow       = step(closestDepth, currentDepth - bias);
	
    return shadow;
}
float calculate_shadow_pcf(vec4 shadowPosition, vec3 normal, vec3 lightDirection)
{
	float shadow = 0.0;
	
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
	const float diskRadius   = 0.01;
	//const float diskRadius   = (1.0 + (viewDistance / u_LightShadow.farPlane)) / 10.0;  
	
	const vec3  ldr          = vec4(shadowPosition - u_LightShadow.position).xyz;
	const float bias         = max((1.0 - dot(normal, ldr)) * 0.05, 0.005);
    const float closestDepth = texture(t_Shadow, ldr).r * u_LightShadow.farPlane;
	const float currentDepth = length(ldr);
	
	for (int i = 0; i < SAMPLES; ++i)
	{
		const vec3  resultingOffset = sampleOffsetDirections[i] * diskRadius;
		const float closestDepth    = texture(t_Shadow, ldr + resultingOffset).r * u_LightShadow.farPlane;
		
		shadow += step(closestDepth, currentDepth - bias);
	}
	
	shadow /= float(SAMPLES);
	
	return shadow;
}

void main()
{
	const vec2 resolution = vec2(1280.0, 720.0);
	const vec2 uv         = gl_FragCoord.xy / resolution;
	
	
	
    const vec3  gPosition = texture(t_Position, uv).xyz;
	const vec3  gAlbedo   = texture(t_Albedo,   uv).rgb; //TODO: Alpha component
    const vec3  gNormal   = texture(t_Normal,   uv).rgb;
    const float gARM      = texture(t_ARM,      uv).g;   //Temporary usage of roughness component for specularity
    
	
	
	const int   index          = u_LightIndex.index;	  
	const vec3  lightPosition  = u_LightBuffer.lights[index].position.xyz;
	const vec3  lightColor     = u_LightBuffer.lights[index].color.rgb;
	const float lightRadius    = u_LightBuffer.lights[index].radius;
	const float lightLinear    = u_LightBuffer.lights[index].linear;
	const float lightQuadratic = u_LightBuffer.lights[index].quadratic;
	
	

	// diffuse
	const vec3 lightDirection = normalize(lightPosition - gPosition);
	      vec3 diffuse        = max(dot(gNormal, lightDirection), 0.0) * gAlbedo * lightColor;
	
	// specular
	const vec3  viewDirection = normalize(u_Camera.position.xyz - gPosition);
	const vec3  bisector      = normalize(lightDirection + viewDirection);  
	      vec3  specular      = lightColor * pow(max(dot(gNormal, bisector), 0.0), 8.0) * gARM;
	
	// attenuation
	const float fragmentDistance = length(lightPosition - gPosition);	
	const float attenuation      = 1.0 / (1.0 + (lightLinear * fragmentDistance) + (lightQuadratic * pow(fragmentDistance, 2.0)));
	
	diffuse  *= attenuation;
	specular *= attenuation;
	
	
	const vec4  shadowPosition  = u_LightSpace.matrix * vec4(gPosition, 1.0);
	const float shadow          = calculate_shadow_pcf(vec4(gPosition, 1.0), gNormal, lightDirection);
	const vec3  lighting        = diffuse + specular * (1.0 - shadow);
	const float smoothingFactor = smoothstep(1.0, 0.6, fragmentDistance / lightRadius);



	f_Color = vec4(lighting * smoothingFactor, 1.0);
}
