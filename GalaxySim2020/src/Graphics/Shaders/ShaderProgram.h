#pragma once
#include <map>
#include "../IO/GL_Logger.h"
#include "Shader.h"
namespace Graphics
{

	class ShaderProgram
	{
	private:
		std::map<int, Shader*> m_shaders;
		unsigned int m_id;
	public:
		ShaderProgram();
		~ShaderProgram();

		void addShader(Shader* s);
		void removeShader(Shader* s);

		void addShader(unsigned int shaderID);
		void removeShader(unsigned int shaderID);

		void prepareProgram();

		void bind() { GL_CHECK(glUseProgram(m_id)); }
		void unbind() { glUseProgram(0); }
	};
}

