#version 440 core

layout(location = 0) in vec3 a_position;

layout(location = 1) uniform mat4 u_projMatrix;

void main()
{
	gl_Position = u_projMatrix * vec4(a_position, 1.0);
}