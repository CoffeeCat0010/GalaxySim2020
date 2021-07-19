#include "Corepch.h"
#include "GLWindow.h"
namespace Graphics {
	GLWindow::GLWindow(std::string title, int32_t sizeX, int32_t sizeY, bool fullscreen)
		:IWindow(sizeX, sizeY), IOpenglContext(sizeX, sizeY), title(title)
	{
		window = glfwCreateWindow(DEFAULT_SIZE_X, DEFAULT_SIZE_Y, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	};

	GLFWwindow* GLWindow::getWindow() {
		return window;
	}
	bool GLWindow::init ()
	{
		if ( !glfwInit () )
		{
			LOG_FATAL ("GLFW failed to intialize!");
			return false;
		}
		LOG_INFO ("Intializing GLFW...");
		return true;
	}
	void GLWindow::pollEvents ()
	{
		glfwPollEvents ();
	}
	void GLWindow::makeOGLContextCurrent ()
	{
		if ( !window ) return;
		glfwMakeContextCurrent (window); 
	}
	void GLWindow::paint()
	{
		glfwSwapBuffers (window);
	}
}