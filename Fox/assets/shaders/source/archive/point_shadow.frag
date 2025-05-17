#version 460 core

layout(set = 0, binding = 6) uniform ULightShadow
{
	vec4  position;
	float farPlane;
} u_LightShadow;

layout(location = 0) in vec4 g_Position;

void main()
{
	//Get distance from fragment to light and then normalize to [0, 1] range
	const float lightDistance           = length(g_Position.xyz - u_LightShadow.position.xyz);
	const float lightDistanceNormalized = lightDistance / u_LightShadow.farPlane;
	
	gl_FragDepth = lightDistanceNormalized;
}
