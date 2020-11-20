#pragma once
#include <GL/glew.h>
#include <string>
namespace Graphics
{
	enum SHADER_TYPE
	{
		FRAG = GL_FRAGMENT_SHADER, VERT = GL_VERTEX_SHADER, GEOMETRY = GL_GEOMETRY_SHADER
	};
	class Shader
	{
	private:
		unsigned int m_id;
	public:
		Shader(const std::string source, SHADER_TYPE type);
		~Shader();
		inline unsigned int getID() { return m_id; }
	};
}
