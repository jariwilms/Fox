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

layout(set = 0, binding =  0) uniform Context
{
	vec2  resolution;
	vec2  mousePosition;
	float time;
	float deltaTime;
} u_Context;
layout(set = 0, binding =  2) uniform Camera
{
	vec4 position;
} u_Camera;
layout(set = 0, binding =  4) uniform LightBuffer
{
	Light lights[NR_LIGHTS];
} u_LightBuffer;
layout(set = 0, binding =  5) uniform LightSpace
{
	mat4 model;
	mat4 matrix;
} u_LightSpace;
layout(set = 0, binding = 12) uniform LightIndex
{
	int index;
} u_LightIndex;

layout(binding = 0) uniform sampler2D t_Position;
layout(binding = 1) uniform sampler2D t_Albedo;
layout(binding = 2) uniform sampler2D t_Normal;
layout(binding = 3) uniform sampler2D t_ARM;
layout(binding = 4) uniform sampler2D t_Shadow;

layout(location = 0) out vec4 f_Color;

float calculate_shadow(vec4 shadowPosition, vec3 normal, vec3 lightDirection)
{
	//Perspective divide and normalization [-1, 1]
    vec3 coordinates = shadowPosition.xyz / shadowPosition.w;
         coordinates = (coordinates * 0.5) + 0.5;
	
	//Return 0.0 if the coordinate is outside the lights far plane
	if (coordinates.z > 1.0) return 0.0;
	
    //Get closest depth value from light's perspective using [0,1] range v_ShadowPosition as coords
	const float bias         = max((1.0 - dot(normal, lightDirection)) * 0.05, 0.005);
    const float closestDepth = texture(t_Shadow, coordinates.xy).r;
	const float shadow       = step(closestDepth, coordinates.z - bias);

    return shadow;
}
float calculate_shadow_pcf(vec4 shadowPosition, vec3 normal, vec3 lightDirection)
{
	float shadow = 0.0;
	
	//Perspective divide and normalization [-1, 1]
    vec3 coordinates = shadowPosition.xyz / shadowPosition.w;
         coordinates = (coordinates * 0.5) + 0.5;
	
	//Return 0.0 if the coordinate is outside the lights far plane
	if (coordinates.z > 1.0) return 0.0;
	
    //Get closest depth value from light's perspective using [0,1] range v_ShadowPosition as coords
	const float bias         = max((1.0 - dot(normal, lightDirection)) * 0.05, 0.005);
    const float closestDepth = texture(t_Shadow, coordinates.xy).r;
	      //float shadow       = step(closestDepth, coordinates.z - bias);
	
	//Sample surrounding texels for softer shadows
	const vec2 texelSize = 1.0 / textureSize(t_Shadow, 0);
	for(int x = -1; x <= 2; ++x)
	{
		for(int y = -1; y <= 2; ++y)
		{
			const vec2  sampleOffset = coordinates.xy + vec2(x, y) * texelSize;
			const float pcfDepth     = texture(t_Shadow, sampleOffset).r;
			
			shadow += coordinates.z - bias > pcfDepth ? 1.0 : 0.0;        
		}
	}
	shadow /= 9.0;
	
    return shadow;
}

void main()
{
	const vec2 resolution = u_Context.resolution;
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
	const float shadow          = calculate_shadow_pcf(shadowPosition, gNormal, lightDirection);
	const vec3  lighting        = diffuse + specular * (1.0 - shadow);
	const float smoothingFactor = smoothstep(1.0, 0.6, fragmentDistance / lightRadius);



	f_Color = vec4(lighting * smoothingFactor, 1.0);
}
