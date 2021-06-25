#pragma once
#include <GLFW/glfw3.h>
#include <string>
namespace Graphics {
#define DEFAULT_ASP_HORIZONTAL 16
#define DEFAULT_ASP_VERTICAL 9
#define DEFAULT_SIZE_X 1920
#define DEFAULT_SIZE_Y 1080
	class GLWindow {
	private:
		GLFWwindow* window;
		std::string title;
		int aspectRatioH, aspectRatioV;
		int currSizeX, currSizeY;
	public:
		GLWindow(std::string title, bool fullscreen);
		//void setAspectRatio(int horizontal, int vertical);
		bool setCurrContext();
		GLFWwindow* getWindow();
	};
}