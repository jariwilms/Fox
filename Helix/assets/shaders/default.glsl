#version 460 core

uniform mat4 uModel;
layout(std140) uniform Matrices
{
	mat4 uView;
	mat4 uProjection;
}

layout(location = 0) in vec3 aPosition;
//layout(location = 1) in vec3 aNormal;
//layout(location = 2) in vec3 aTangent;
//layout(location = 3) in vec3 aBiTangent;
layout(location = 1) in vec2 aTexCoord;

//layout(location = 0) out vec3 vPosition;
//layout(location = 1) out vec3 vNormal;
layout(location = 0) out vec2 vTexCoord;

out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

void main()
{
	//vPosition = aPosition;
	vTexCoord = aTexCoord;

	gl_Position = vec4(aPosition, 1.0);
}
