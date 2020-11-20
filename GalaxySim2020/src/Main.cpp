#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <CL/cl.hpp>
#include "IO/Logger.h"
#include "IO/GL_Logger.h"
#include "Graphics/Window/GLWindow.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Shaders/Shader.h"
#include "IO/GSIO.h"


int main(void)
{
	/* Initialize the library */
	
	if (!glfwInit())
		return -1;

	Graphics::GLWindow glWindow = Graphics::GLWindow("Test", false);
	glWindow.setCurrContext();

	// Init GLEW and check if init is sucessful 
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}
	float vertices[] = {
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	unsigned int elements[]{
		0, 1, 2,
		2, 3, 0
	};


	std::string source = IO::sourceToCStr("src/Graphics/GLSL/myshader.frag");
	Graphics::Shader fragShader(source, Graphics::FRAG);

	source = IO::sourceToCStr("src/Graphics/GLSL/myshader.mesh");
	Graphics::Shader vertShader(source, Graphics::VERT);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertShader.getID());
	glAttachShader(program, fragShader.getID());
	glLinkProgram(program);
	Graphics::VertexBuffer vbo(vertices, 8 * sizeof(float));
	Graphics::IndexBuffer ibo(elements, sizeof(elements));
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vbo.bind();
	ibo.bind();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(glWindow.getWindow()))
	{
		/* Render here */
	 // ibo.bind();
		//while (glGetError() != 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GL_CHECK(glUseProgram(program));
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		/* Swap front and back buffers */
		glfwSwapBuffers(glWindow.getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}