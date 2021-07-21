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

		GLenum glewError = glewInit ();
		if ( glewError != GLEW_OK )
		{
			LOG_FATAL ("GLEW failed to intialize! Terminating GLFW!");
			glfwTerminate ();
			return false;
		}
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
	void GLWindow::close ()
	{
		// for now this is fine however it means that there really can only be one window
		// think about creating base class for managing glfw seperately from the window.
		glfwTerminate ();
	}
}