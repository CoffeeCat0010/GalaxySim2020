#include <GL/glew.h>
#include <iostream>
#include "../IO/Logger.h"
#include "Shader.h"

namespace Graphics
{
	Shader::Shader(const std::string source, SHADER_TYPE type)
	{
    const char* c_source = source.c_str();
    m_id = glCreateShader(type);
    glShaderSource(m_id, 1, &c_source, NULL);
    glCompileShader(m_id);
    int status;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
      GLsizei log_len = 0;
      char message[1024];
      glGetShaderInfoLog(m_id, 1024, &log_len, message);
      LOG_ERROR("Opengl compiler error " + (std::string)message);
    }
	}
  Shader::~Shader()
  {
    glDeleteShader(m_id);
  }
}

