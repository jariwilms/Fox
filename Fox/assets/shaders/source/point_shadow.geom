#version 460 core

const int FACE_COUNT = 6;

layout(triangles)                         in;
layout(triangle_strip, max_vertices = 18) out;

layout(set = 0, binding = 13) uniform UShadowMatrices
{
	mat4 matrices[FACE_COUNT];
} u_ShadowMatrices;

layout(location = 0) out vec4 g_position;

void main()
{
	for(int face = 0; face < FACE_COUNT; ++face)
    {
		//Set face to render to
        gl_Layer = face; 
		
		//Iterate over each triangle vertex
        for(int i = 0; i < 3; ++i) 
        {
            g_position = gl_in[i].gl_Position;
            gl_Position = u_ShadowMatrices.matrices[face] * g_position;
			
            EmitVertex();
        }
		
        EndPrimitive();
    }
}
