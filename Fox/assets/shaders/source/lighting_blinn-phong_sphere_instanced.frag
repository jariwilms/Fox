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

//layout(std140, set = 0, binding =  0) uniform Input
//{
//	vec2  resolution;
//	float time;
//	float deltaTime;
//	vec2  mousePosition;
//} u_Input;
layout(std140, set = 0, binding =  2) uniform Camera
{
	vec4 position;
} u_Camera;
layout(std140, set = 0, binding =  4) uniform LightBuffer
{
	Light lights[NR_LIGHTS];
} u_LightBuffer;

layout(binding = 0) uniform sampler2D t_Position;
layout(binding = 1) uniform sampler2D t_Albedo;
layout(binding = 2) uniform sampler2D t_Normal;
layout(binding = 3) uniform sampler2D t_ARM;

layout(location = 0)      in  vec3 v_Position;
layout(location = 1) flat in  int  v_InstanceIndex;

layout(location = 0)      out vec4 f_Color;

void main()
{
	const vec2 resolution = vec2(1280.0, 720.0);
	const vec2 uv         = gl_FragCoord.xy / resolution;
	
	
	
    const vec3  gPosition = texture(t_Position, uv).xyz;
	const vec3  gAlbedo   = texture(t_Albedo,   uv).rgb; //TODO: Alpha component
    const vec3  gNormal   = texture(t_Normal,   uv).rgb;
    const float gARM      = texture(t_ARM,      uv).b;   //Temporary usage of roughness component for specularity
    
	
	
	const vec3  lightPosition  = u_LightBuffer.lights[v_InstanceIndex].position.xyz;
	const vec3  lightColor     = u_LightBuffer.lights[v_InstanceIndex].color.rgb;
	const float lightRadius    = u_LightBuffer.lights[v_InstanceIndex].radius;
	const float lightLinear    = u_LightBuffer.lights[v_InstanceIndex].linear;
	const float lightQuadratic = u_LightBuffer.lights[v_InstanceIndex].quadratic;
	
	

	vec3 fragmentColor;
	// diffuse
	const vec3 lightDirection = normalize(lightPosition - gPosition);
	      vec3 diffuse        = max(dot(gNormal, lightDirection), 0.0) * gAlbedo * lightColor;
	
	// specular
	const vec3  viewDirection = normalize(u_Camera.position.xyz - gPosition);
	const vec3  bisector      = normalize(lightDirection + viewDirection);  
	      vec3  specular      = lightColor * pow(max(dot(gNormal, bisector), 0.0), 16.0) * gARM;
	
	// attenuation
	const float fragmentDistance = length(lightPosition - gPosition);	
	const float attenuation      = 1.0 / (1.0 + (lightLinear * fragmentDistance) + (lightQuadratic * pow(fragmentDistance, 2.0)));
	
	diffuse       *= attenuation;
	specular      *= attenuation;
	fragmentColor  = diffuse + specular;
	
	
	
	const float smoothingFactor = smoothstep(1.0, 0.6, fragmentDistance / lightRadius);



	//f_Color = vec4(fragmentColor * smoothingFactor, 1.0);
	if      (v_InstanceIndex == 0) discard;//f_Color = vec4(1.0, 0.0, 0.0, 1.0);
	else if (v_InstanceIndex == 1) f_Color = vec4(0.0, 1.0, 0.0, 1.0);
	else                           f_Color = vec4(0.0, 0.0, 1.0, 1.0);
}
