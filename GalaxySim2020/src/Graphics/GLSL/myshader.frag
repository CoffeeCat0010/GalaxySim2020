#version 440 core

layout (location = 0) out vec4 outcolor;

in vec2 v_textureCoords;
in flat int v_textureID;

layout (location = 5) uniform sampler2D u_textures[256];

void main()
{
	if(v_textureID == 0)
	{
		outcolor = vec4(0.5, 1.0, 0.5, 1.0);
	}
	else
	{
		int index = v_textureID;
		outcolor = texture(u_textures[index], v_textureCoords);
	}
}