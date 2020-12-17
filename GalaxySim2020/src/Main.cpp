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

cl_context& getOCLContext();
int main(void)
{
	/* Initialize the library */
	
	if (!glfwInit())
		return -1;

	cl_context con;
	con = getOCLContext();

	Graphics::GLWindow glWindow = Graphics::GLWindow("Test", false);
	glWindow.setCurrContext();

	// Init GLEW and check if init is sucessful 
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}
	


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

cl_context& getOCLContext()
{

	cl_int err = 0;
	cl_uint numPlatforms;
	cl_platform_id* platformIds;
	err = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (err) {
		std::cout << "Something went wrong! Error Number: " << err << std::endl;
	}
	platformIds = (cl_platform_id*)malloc(sizeof(cl_platform_id) * numPlatforms);
	err = clGetPlatformIDs(numPlatforms, platformIds, NULL);
	if (err)
	{
		std::cout << "Something went wrong! Error Number: " << err << std::endl;
	}
	std::cout << numPlatforms << " platforms found!" << std::endl;
	for (int i = 0; i < numPlatforms; i++)
	{
		size_t size;
		char* platformName;
		char* vendorName;
		err = clGetPlatformInfo(platformIds[i], CL_PLATFORM_NAME, 0, nullptr, &size);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		platformName = (char*)malloc(sizeof(char) * size);
		err = clGetPlatformInfo(platformIds[i], CL_PLATFORM_NAME, size, platformName, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		err = clGetPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, 0, nullptr, &size);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		vendorName = (char*)malloc(sizeof(char) * size);
		err = clGetPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, size, vendorName, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		std::cout << i + 1 << ":" << "Platform: " << platformName << "\nVendor: " << vendorName << std::endl;
		delete vendorName;
		delete platformName;
	}
	int selection;
	std::cout << "Please select the platform you would like to use:";
	std::cin >> selection;
	while (selection > numPlatforms || selection < 1)
	{
		std::cout << "Error! Invaild selection! Please try again.\n";
		std::cout << "Please select the platform you would like to use:";
		std::cin >> selection;
	}
	selection--;
	cl_device_type dType;
	std::string input;
	std::cout << "Would you like to use like to use all available compute devices? [y/N]";
	std::cin >> input;
	if (input == "y" || input == "Y")
	{
		dType = CL_DEVICE_TYPE_ALL;
	}
	else
	{
		int deviceSelection = 0;
		do
		{
			std::cout << "1: CPU \n";
			std::cout << "2: GPU \n";
			std::cout << "3: Accelerator \n";
			std::cout << "4: default \n";
			std::cout << "Please select the type of compute device you would like to use: ";
			std::cin >> deviceSelection;
			if (deviceSelection < 1 || deviceSelection > 4) std::cout << "Invalid Input!\n";
		} while (deviceSelection < 1 || deviceSelection > 4);
		switch (deviceSelection)
		{
			case 1:
				dType = CL_DEVICE_TYPE_CPU;
				break;
			case 2:
				dType = CL_DEVICE_TYPE_GPU;
				break;
			case 3:
				dType = CL_DEVICE_TYPE_ACCELERATOR;
				break;
			case 4:
				dType = CL_DEVICE_TYPE_DEFAULT;
				break;
		}
	}
	cl_uint numDevices = 0;
	cl_device_id* deviceIds;
	err = clGetDeviceIDs(platformIds[selection], dType, 0, nullptr, &numDevices);
	if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
	deviceIds = (cl_device_id*)malloc(sizeof(cl_device_id) * numDevices);
	err = clGetDeviceIDs(platformIds[selection], dType, numDevices, deviceIds, NULL);
	for (int i = 0; i < numDevices; i++)
	{
		size_t size;
		char* deviceName;
		char* deviceVendorName;
		char* deviceVersion;
		cl_uint computeUnits;
		cl_uint maxDiminsion;
		size_t* maxWorkItemSize;
		
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_NAME, 0, nullptr, &size);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		deviceName = (char*)malloc(sizeof(char) * size);
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_NAME, size, deviceName, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_VENDOR, 0, nullptr, &size);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		deviceVendorName = (char*)malloc(sizeof(char) * size);
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_VENDOR, size, deviceVendorName, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_VERSION, 0, nullptr, &size);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		deviceVersion = (char*)malloc(sizeof(char) * size);
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_VERSION, size, deviceVersion, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &computeUnits, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
	
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, size, &maxDiminsion, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		maxWorkItemSize = (size_t*)malloc(sizeof(size_t) * maxDiminsion);
		err = clGetDeviceInfo(deviceIds[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, size, maxWorkItemSize, NULL);
		if (err) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		
		std::cout << i + 1 << ":" << "Device: " << deviceName << " Vendor: " << deviceVendorName << std::endl;
		std::cout << "Version: " << deviceVersion << " \nCompute Units: " << computeUnits << " \nMax work items: ";
		for (int i = 0; i < maxDiminsion; i++)
			std::cout << maxWorkItemSize[i] << " ";
		std::cout << std::endl;
	}
	cl_context_properties properties[] =
	{
		CL_CONTEXT_PLATFORM, (cl_context_properties)platformIds[selection], 0
	};
	cl_context context;
	context = clCreateContext(properties, numDevices, deviceIds, NULL, NULL, NULL);
	return context;

}