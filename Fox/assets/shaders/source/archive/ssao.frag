#version 460 core

#include "settings/settings.spl"
#include "uniform/context.unf"
#include "uniform/matrices.unf"
#include "uniform/ambient_occlusion.unf"

layout(binding  = 0) uniform sampler2D g_Depth;
layout(binding  = 2) uniform sampler2D g_Normal;
layout(binding  = 5) uniform sampler2D t_Noise;

layout(location = 0) in  vec2  v_TexCoord;

layout(location = 0) out float f_Color;

void main()
{
    const int   kernelSize = 64;
    const float radius     = 0.05;
    const float bias       = 0.025;

	const mat4  projection = u_Matrices.projection;
	const mat4  view       = u_Matrices.view;
	
	const vec2  resolution = u_Context.resolution;
	const vec2  uv         = gl_FragCoord.xy / resolution;

	const vec2  noiseScale = resolution.xy / 4.0; 
	
	f_Color = gl_FragCoord.z;






	//float depth = texture(g_Depth, uv).r;
	//
    //float AO = 0.0;
	//
    //for (int i = 0 ; i < 64u ; i++) 
	//{
    //    float sampleDepth = texture(g_Depth, uv + u_AmbientOcclusion.samples[i].xy / 50.0).r;
	//
    //    if (abs(depth - sampleDepth) < radius) 
	//	{
    //        AO += step(sampleDepth, depth);
    //    }
    //}
	//
    //AO = 1.0 - AO/64.0;
	//
    //f_Color = pow(AO, 2.0);
}