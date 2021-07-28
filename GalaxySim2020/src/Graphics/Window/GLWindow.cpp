#include "Corepch.h"
#include "GLWindow.h"
namespace Graphics {
	GLWindow::GLWindow(std::string title, std::shared_ptr<Application::EventDispatcher> dispatcher, int32_t sizeX, int32_t sizeY, bool fullscreen)
		:IWindow(sizeX, sizeY), dispatcher_ptr(dispatcher),IOpenglContext(sizeX, sizeY), title(title), m_fullscreen(fullscreen)
	{
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
		window = glfwCreateWindow (DEFAULT_SIZE_X, DEFAULT_SIZE_Y, title.c_str (), m_fullscreen ? glfwGetPrimaryMonitor () : NULL, NULL);
		makeOGLContextCurrent();
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