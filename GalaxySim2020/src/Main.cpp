#include "Corepch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Application/Application.h>

#define NUM_OF_STARS 49152 // 1024
//49152
#define NUM_TIME_STEPS 10000 //5000
//10000


int main() {
	Application::App* entry = Application::App::getInstance();
	entry->init();
	
	entry->cleanUp();
	return 0;
}