#version 460 core

layout(std140, set = 0, binding =  0) uniform Context
{
	vec2  resolution;
	vec2  mousePosition;
	float time;
	float deltaTime;
} u_Context;
layout(std140, set = 0, binding =  1) uniform Camera
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

layout(binding  = 0) uniform sampler2D t_Position;
layout(binding  = 1) uniform sampler2D t_Albedo;
layout(binding  = 2) uniform sampler2D t_Normal;
layout(binding  = 3) uniform sampler2D t_ARM;

layout(location = 0) out vec4 f_Color;

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
	const float smoothingFactor = smoothstep(1.0, 0.6, fragmentDistance / lightRadius);
	const vec3  lighting        = ((diffuse * attenuation) + (specular * attenuation)) * smoothingFactor;



	f_Color = vec4(lighting, 1.0);
}
