#include "Corepch.h"
#include "GLWindow.h"
namespace Graphics {
	GLWindow::GLWindow(std::string title, std::shared_ptr<Application::EventDispatcher> dispatcher, int32_t sizeX, int32_t sizeY, bool fullscreen)
		:IWindow(sizeX, sizeY, dispatcher), IOpenglContext(sizeX, sizeY), title(title)
	{
		window = glfwCreateWindow(DEFAULT_SIZE_X, DEFAULT_SIZE_Y, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	};

	GLFWwindow* GLWindow::getWindow() {
		return window;
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