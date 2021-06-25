#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textureCoords;
layout(location = 3) in int a_textureID;

layout(location = 4) uniform mat4 u_projMatrix;

out vec2 v_textureCoords;
out int v_textureID;

void main()
{
	v_textureCoords = a_textureCoords;
	v_textureID = a_textureID;
	gl_Position = u_projMatrix * vec4(a_position, 1.0);
}
