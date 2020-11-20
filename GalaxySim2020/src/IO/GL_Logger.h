#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <string>

#include "logger.h"		
		
#define GL_CHECK(x) \
	while(glGetError() !=0); \
	x; \
  { int err; \
	if((err = glGetError()) != 0){ \
		IO::logger* l = l->getInstance(); \
		l->printMessage("Opengl error " + std::to_string(err) +" in " + (std::string)__FILE__ + " at line " + std::to_string(__LINE__), IO::FATAL); \
		exit(EXIT_FAILURE); }}