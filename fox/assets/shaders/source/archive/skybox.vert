#version 450 core

layout(set = 0, binding = 0) uniform MatricesBuffer
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 normal;
} u_MVP;

layout(location = 0) in vec3 a_Position;

layout(location = 0) out vec3 v_TexCoord;

void main() 
{
    // Remove translation from view matrix
    mat4 viewRot = mat4(mat3(u_MVP.view));

    v_TexCoord = a_Position;

    // Project vertex positions to clip space
    gl_Position = u_MVP.projection * viewRot * vec4(a_Position, 1.0);
    gl_Position = gl_Position.xyww; // Keep the w component to prevent depth clipping
}
