#version 460

#include "uniform/context.unf"
#include "uniform/matrices.unf"
#include "uniform/ambient_occlusion.unf"

layout(binding = 0) uniform sampler2D gPosition;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D texNoise;

layout(location = 0) in  vec2  TexCoords;
layout(location = 0) out float FragColor;

// parameters (you'd probably want to use them as uniforms to more easily tweak the effect)
const int kernelSize = 64;
const float radius = 0.5;
const float bias = 0.025;

// tile noise texture over screen based on screen dimensions divided by noise size
const vec2 noiseScale = vec2(1280.0/4.0, 720.0/4.0); 

void main()
{
	const vec2  resolution                  = u_Context.resolution;
	const vec2  uv                          = gl_FragCoord.xy / resolution;



vec3 fragPos = vec3(u_Matrices.view * vec4(texture(gPosition, TexCoords).xyz, 1.0));
vec3 normal = mat3(u_Matrices.view) * texture(gNormal, TexCoords).rgb;
    // get input for SSAO algorithm
    //vec3 fragPos = texture(gPosition, TexCoords).xyz;
    //vec3 normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 randomVec = normalize(texture(texNoise, TexCoords * noiseScale).xyz);
    // create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    // iterate over the sample kernel and calculate occlusion factor
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; ++i)
    {
        // get sample position
        vec3 samplePos = TBN * u_AmbientOcclusion.samples[i].xyz; // from tangent to view-space
        samplePos = fragPos + samplePos * radius; 
        
        // project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(samplePos, 1.0);
        offset = u_Matrices.projection * offset; // from view to clip-space
        offset.xyz /= offset.w; // perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0
        
        // get sample depth
		vec3 sampleFragPos = vec3(u_Matrices.view * vec4(texture(gPosition, offset.xy).xyz, 1.0));
        float sampleDepth = sampleFragPos.z;
        
        // range check & accumulate
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;           
    }
    occlusion = 1.0 - (occlusion / kernelSize);
    
    FragColor = pow(occlusion, 2.0);
}