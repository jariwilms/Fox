#version 460 core

layout(binding = 0) uniform sampler2D t_Position;
layout(binding = 1) uniform sampler2D t_Albedo;
layout(binding = 2) uniform sampler2D t_Normal;
layout(binding = 3) uniform sampler2D t_ARM;

layout(location = 0) in vec2 v_TexCoord;

layout(location = 0) out vec4 f_Color;

struct Light
{
	vec4 position;
	vec4 color;
	
	float radius;
	float linear;
	float quadratic;
	float _padding;
};

const int NR_LIGHTS = 32;
layout(std140, set = 0, binding = 3) uniform LightBuffer
{
	Light lights[NR_LIGHTS];
} u_LightBuffer;

layout(std140, set = 0, binding = 4) uniform Camera
{
	vec4 position;
} u_Camera;

void main()
{
    vec3  gPosition = texture(t_Position, v_TexCoord).xyz;
	vec3  gAlbedo   = texture(t_Albedo,   v_TexCoord).rgb; //TODO: Alpha component
    vec3  gNormal   = texture(t_Normal,   v_TexCoord).rgb;
    float gARM      = texture(t_ARM,      v_TexCoord).g;   //Temporary usage of roughness component for specularity
    
	
	
	const vec3 viewDirection   = normalize(u_Camera.position.xyz - gPosition);
	const vec3 ambientLighting = gAlbedo * 0.1;
          vec3 lighting        = ambientLighting;
		  
		  
		  
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
		 vec3 lightPosition  = u_LightBuffer.lights[i].position.xyz;
		 vec3 lightColor     = u_LightBuffer.lights[i].color.rgb;
		float lightRadius    = u_LightBuffer.lights[i].radius;
		float lightLinear    = u_LightBuffer.lights[i].linear;
		float lightQuadratic = u_LightBuffer.lights[i].quadratic;
		
        float distance = length(lightPosition - gPosition);
        if(distance < lightRadius)
        {
            // diffuse
            vec3 lightDirection = normalize(lightPosition - gPosition);
            vec3 diffuse        = max(dot(gNormal, lightDirection), 0.0) * gAlbedo * lightColor;
			
            // specular
            vec3 bisector = normalize(lightDirection + viewDirection);  
            float spec    = pow(max(dot(gNormal, bisector), 0.0), 16.0);
            vec3 specular = lightColor * spec * gARM;
			
            // attenuation
            float attenuation = 1.0 / (1.0 + (lightLinear * distance) + (lightQuadratic * pow(distance, 2.0)));
			
            diffuse  *= attenuation;
            specular *= attenuation;
            lighting += diffuse + specular;
        }
    }
	
    f_Color = vec4(lighting, 1.0);
}
