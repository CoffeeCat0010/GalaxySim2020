#pragma once

#include "Corepch.h"
#include "../IO/GL_Logger.h"
#include "Shader.h"
namespace Graphics
{

	class ShaderProgram
	{
	private:
		std::map<int, Shader*> m_shaders;
		uint32_t m_id;
	public:
		ShaderProgram();
		~ShaderProgram();

		void addShader(Shader* s);
		void removeShader(Shader* s);

	//	void addShader(unsigned int shaderID);
	//	void removeShader(unsigned int shaderID);

		void prepareProgram();


		inline uint32_t getID() const { return m_id; };
		inline void bind() { GL_CHECK(glUseProgram(m_id)); }
		inline void unbind() { glUseProgram(0); }
	};
}

