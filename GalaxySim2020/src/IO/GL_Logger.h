#pragma once
#include "Corepch.h"
#include <GL/glew.h>

#include "logger.h"		
		

#ifdef GL_LOG_ERROR
	#define GL_CHECK(x) \
		while(glGetError() !=0); \
		x; \
		{ int err; \
		if((err = glGetError()) != 0){ \
			IO::logger* l = l->getInstance(); \
			l->printMessage("Opengl error " + std::to_string(err) +" in " + (std::string)__FILE__ + " at line " + std::to_string(__LINE__), IO::FATAL); \
			std::cout << "Opengl error " + std::to_string(err) +" in " + (std::string)__FILE__ + " at line " + std::to_string(__LINE__) << std::endl; \
			exit(EXIT_FAILURE); }}
#else
	#define GL_CHECK(x) x;
#endif
