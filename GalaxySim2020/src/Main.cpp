#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <CL/cl.hpp>
#include "glm/glm.hpp"
#include "IO/Logger.h"
#include "IO/GL_Logger.h"
#include "Graphics/Window/GLWindow.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "IO/GSIO.h"
#include "Graphics/Renderers/BatchRenderer.h"
#include "Graphics/Shapes/square2D.h"
#include "Graphics/Buffers/Texture2D.h"


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

	uint32_t elements[] = {
		0, 1, 2,
		2, 3, 0
	};


	std::string source = IO::sourceToCStr("src/Graphics/GLSL/myshader.frag");
	Graphics::Shader fragShader(source, Graphics::FRAG);

	source = IO::sourceToCStr("src/Graphics/GLSL/myshader.vert");
	Graphics::Shader vertShader(source, Graphics::VERT);

	Graphics::ShaderProgram program;
	program.addShader(&vertShader);
	program.addShader(&fragShader);
	program.prepareProgram();



	Graphics::BatchRenderer renderer(program);
	Graphics::Texture2D texture("C:/Users/Justin/source/repos/GalaxySim2020/GalaxySim2020/Res/Test.png");
	Graphics::square2D testSquare(program.getID(), 1.0f, 0.0f, 0.0f, 0.0f, &texture);

	int max;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
	std::cout << max << std::endl;
	//Graphics::VertexBuffer vbo(vertices, 8 * sizeof(float));
	//Graphics::IndexBuffer ibo(elements, sizeof(elements));
	//unsigned int vao;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//vbo.bind();
	//ibo.bind();
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(glWindow.getWindow()))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*	program.bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);*/

		renderer.addMesh(testSquare);
		renderer.render();

		/* Swap front and back buffers */
		glfwSwapBuffers(glWindow.getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}