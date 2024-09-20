#version 450 core

struct Light 
{
    vec3 Position;
    vec3 Color;
};

const int NR_LIGHTS = 32;
layout(set = 0, binding = 3) uniform LightsBlock
{
	Light lights[NR_LIGHTS];
	uniform vec3 viewPosition;
};

layout(location = 0) in vec2 v_TexCoords;

layout(location = 0) out vec4 f_Color;

layout(binding = 0) uniform sampler2D g_Position;
layout(binding = 1) uniform sampler2D g_Normal;
layout(binding = 2) uniform sampler2D g_AlbedoSpecular;

void main()
{             
    // retrieve data from G-buffer
    vec3  fragmentPosition = texture(g_Position,   v_TexCoords).rgb;
    vec3  normal           = texture(g_Normal,     v_TexCoords).rgb;
    vec3  albedo           = texture(g_AlbedoSpecular, v_TexCoords).rgb;
    float specular         = texture(g_AlbedoSpecular,  v_TexCoords).a;
    
    // then calculate lighting as usual
    vec3 lighting = albedo * 0.2; // hard-coded ambient component
    vec3 viewDirection = normalize(viewPosition - fragmentPosition);
	
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // diffuse
        vec3 lightDirection = normalize(lights[i].Position - fragmentPosition);
        vec3 diffuse = max(dot(normal, lightDirection), 0.0) * albedo * lights[i].Color;
        lighting += diffuse;
    }
    
    f_Color = vec4(lighting, 1.0);
}
