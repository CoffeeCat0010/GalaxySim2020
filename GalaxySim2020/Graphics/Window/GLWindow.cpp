#include "GLWindow.h"
namespace Graphics {
	GLWindow::GLWindow(std::string title, bool fullscreen)
		:title(title)
	{
		window = glfwCreateWindow(DEFAULT_SIZE_X, DEFAULT_SIZE_Y, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	};

	bool GLWindow::setCurrContext() {
		if (!window) return false;
		glfwMakeContextCurrent(window);
	};

	GLFWwindow* GLWindow::getWindow() {
		return window;
	}
}