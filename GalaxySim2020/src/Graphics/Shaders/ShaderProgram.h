#pragma once
#include <map>
#include "Shader.h"
namespace Graphics
{

	class ShaderProgram
	{
	private:
		std::map<int, Shader> shaders;
	public:
		ShaderProgram();
		~ShaderProgram();

		void addShader(Shader* s);
		void removeShader(Shader* s);

		void addShader(unsigned int shaderID);
		void removeShader(unsigned int shaderID);

	};
}

