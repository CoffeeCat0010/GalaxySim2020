#include "Corepch.h"
#include <GL/glew.h>
#include "ShaderProgram.h"


namespace Graphics
{
	ShaderProgram::ShaderProgram()
	{
		m_id = glCreateProgram();
	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}
	void ShaderProgram::addShader(Shader* s)
	{	
		m_shaders.insert(std::pair<int, Shader*>(s->getID(), s));
		GL_CHECK(glAttachShader(this->m_id, s->getID()));
	}
	void ShaderProgram::removeShader(Shader * s)
	{
		#ifdef GL_LOG_ERROR
			int err = 0;
			while ((err = glGetError()) != 0);
			glDetachShader(this->m_id, s->getID());
			err = glGetError();
			if (err == GL_INVALID_OPERATION)
			{
				LOG_ERROR(" OpenGL: INVALID OPERATION! Could not detach shader from program! ")
			}
			else
			{
				LOG_ERROR(" OpenGL: INVALID VALUE! Program or shader does not exist! ")
			}
		#else
			glDetachShader(this->m_id, s->getID());
		#endif
		m_shaders.erase(s->getID());
	}
	void ShaderProgram::prepareProgram()
	{
		GL_CHECK(glLinkProgram(m_id));
		char log[8192];
		int len;
		glGetProgramInfoLog(m_id, 8192, &len, log);
		LOG_INFO(log);
	}
}
