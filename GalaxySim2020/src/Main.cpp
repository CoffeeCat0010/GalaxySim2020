#include "Corepch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <CL/cl.hpp>
#include "glm/glm.hpp"
#include "Graphics/Graphics.h"
#include "IO/Logger.h"
#include "IO/GL_Logger.h"
#include "IO/GSIO.h" 
#include "IO/DataFileType/StarFile.h"
#include "Generation/Galaxy.h"
#include <chrono>
#include "Compute/CLprim/ComputeKernal.h"
#include "Compute/CLprim/ComputeProgram.h"

#define NUM_OF_STARS 49152 // 1024
//49152
#define NUM_TIME_STEPS 10000 //5000
//10000

cl_context getOCLContext();
cl_device_id getDeviceId (cl_context& context); 
cl_command_queue createCommandQueue (cl_context& context, cl_device_id dID);
cl_program createProgram (cl_context& context, cl_device_id dID, const char* fileName);

int main ()
{
	/* Initialize the library */

	if ( !glfwInit () )
		return -1;
	std::cout << "Show previous simulations?[Y/n]: ";
	char response;
	std::cin >> response;
	if ( response == 'n' || response == 'N' ) {
		cl_context con;
		con = getOCLContext ();

		cl_device_id dID = getDeviceId (con);

		cl_command_queue clcq = createCommandQueue (con, dID);
		
		//cl_program clProgram = createProgram (con, dID, "src/Compute/Kernels/PhysKernel.cl");
		std::unique_ptr<Compute::Program> program = Compute::Program::createProgram ("src/Compute/Kernels/PhysKernel.cl", con, dID);
		std::unique_ptr<Compute::Kernel> kern = Compute::Kernel::createKernel (program->getProgramID (), "calcPos");
		cl_int err;
		//cl_kernel kern = clCreateKernel (program->getProgramID(), "calcPos", &err);

		Physics::Galaxy galaxy1 (NUM_OF_STARS / 2, cl_float3{ 0.0f, -3000.0f, -5000.0f }, glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f ), 2000.f, 150000000.f);
		Physics::Galaxy galaxy2 (NUM_OF_STARS / 2, cl_float3{ 0.0f, 3000.0f, -5000.0f }, glm::vec3 (0.0f, 0.5f, 0.0f), glm::vec3 (5.0f, -5.0f, 0.0f), 2000.f, 150000000.f);


		cl_float3* stars = new cl_float3[NUM_OF_STARS];
		/*{ { 0.0f, 0.0f, -15.0f }, { 1.0f, 0.0f, -15.0f },
																			{0.0f, 1.0f, -15.0f}, {0.0f, 0.0f, -16.0f},
																			
																			{1.0f, 1.0f, -15.0f}, {1.0f, 0.0f, -16.0f},
																			{0.0f, 1.0f, -16.0f}, {1.0f, 1.0f, -16.0f} };*/
		cl_float3* starVelocities = new cl_float3[NUM_OF_STARS];
		/*{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
																							 {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
																							 {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
																							 {0.0f, 0.0f, 2.0f}, {0.0f, 4.0f, 0.0f} };*/
		float* starMasses = new float[NUM_OF_STARS]; /*= { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };*/
		for ( int i = 0; i < NUM_OF_STARS / 2; i++ ) {
			stars[i] = galaxy1.getStarPos ()[i];
			starVelocities[i] = galaxy1.getStarVelocities ()[i];
			starMasses[i] = galaxy1.getStarMasses ()[i];
		}
		for ( int i = 0; i < NUM_OF_STARS / 2; i++ ) {
			stars[i + NUM_OF_STARS / 2] = galaxy2.getStarPos ()[i];
			starVelocities[i + NUM_OF_STARS / 2] = galaxy2.getStarVelocities ()[i];
			starMasses[i + NUM_OF_STARS / 2] = galaxy2.getStarMasses ()[i];
		}

		cl_float3* result = new cl_float3[NUM_OF_STARS];
		cl_float3* resultVelocities = new cl_float3[NUM_OF_STARS];
		cl_mem buffers[4];

		buffers[0] = clCreateBuffer (con, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof (cl_float3) * NUM_OF_STARS, stars, &err);
		buffers[1] = clCreateBuffer (con, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof (float) * NUM_OF_STARS, starMasses, &err);
		buffers[2] = clCreateBuffer (con, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof (cl_float3) * NUM_OF_STARS, starVelocities, &err);
		buffers[3] = clCreateBuffer (con, CL_MEM_READ_WRITE, sizeof (cl_float3) * NUM_OF_STARS, NULL, &err);

		float softeningFactor = 100.0f;
		float timeStep = 75000 * 3.154e+07;
		IO::StarFile* file = IO::StarFile::createFile ("Simulations/testFile.STAR", NUM_OF_STARS);
		for ( int i = 0; i < NUM_TIME_STEPS; i++ ) {
			err = clSetKernelArg (kern->getKernel(), 0, sizeof (cl_mem), &buffers[0]);
			err |= clSetKernelArg (kern->getKernel (), 1, sizeof (cl_mem), &buffers[1]);
			err |= clSetKernelArg (kern->getKernel(), 2, sizeof (float), &softeningFactor);
			err |= clSetKernelArg (kern->getKernel(), 3, sizeof (float), &timeStep);
			err |= clSetKernelArg (kern->getKernel(), 4, sizeof (cl_mem), &buffers[2]);
			err |= clSetKernelArg (kern->getKernel(), 5, sizeof (cl_mem), &buffers[3]);

			if ( err != CL_SUCCESS ) {
				std::cout << "Couldn't upload kernel args!" << std::endl;
				std::cout << err << std::endl;
			}
			size_t globalWorkSize = NUM_OF_STARS;
			size_t localWorkSize = 1;

			err = clEnqueueNDRangeKernel (clcq, kern->getKernel (), 1, 0, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
			if ( err != CL_SUCCESS ) {
				std::cout << "Couldn't execute Kernel!" << std::endl;
			}

			err |= clEnqueueReadBuffer (clcq, buffers[3], CL_TRUE, 0, NUM_OF_STARS * sizeof (cl_float3), result, 0, NULL, NULL);
			err |= clEnqueueReadBuffer (clcq, buffers[2], CL_TRUE, 0, NUM_OF_STARS * sizeof (cl_float3), resultVelocities, 0, NULL, NULL);

			for ( int j = 0; j < NUM_OF_STARS; ++j) {
				/*std::cout << "Position: " << result[j].x << " " << result[j].y << " " << result[j].z << " "
					<< "Velocities(km/s): " << resultVelocities[j].x << " " << resultVelocities[j].y << " " << resultVelocities[j].z << std::endl;*/
				stars[j] = result[j];
				starVelocities[j] = resultVelocities[j];
			}
			file->writeTimeStep (result);
			//std::cout << std::endl;
			err |= clEnqueueWriteBuffer (clcq, buffers[0], CL_TRUE, 0, NUM_OF_STARS * sizeof (cl_float3), stars, 0, NULL, NULL);
			err |= clEnqueueWriteBuffer (clcq, buffers[2], CL_TRUE, 0, NUM_OF_STARS * sizeof (cl_float3), starVelocities, 0, NULL, NULL);
		}
		delete file;
		clReleaseMemObject (buffers[0]);
		clReleaseMemObject (buffers[1]);
		clReleaseMemObject (buffers[2]);
		clReleaseMemObject (buffers[3]);
		//clReleaseProgram (clProgram);
		clReleaseCommandQueue (clcq);
		clReleaseDevice (dID);
		clReleaseContext (con);
	}
	IO::StarFile* rFile = IO::StarFile::readFile ("C:/Users/justi/Simulations/testFile.STAR");
	Graphics::GLWindow glWindow = Graphics::GLWindow ("Test", false);
	glfwSetInputMode (glWindow.getWindow (), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glWindow.makeOGLContextCurrent ();
	{
		// Init GLEW and check if init is sucessful 
		GLenum glewError = glewInit ();
		if ( glewError != GLEW_OK ) {
			glfwTerminate ();
			return -1;
		}


		std::string source = IO::sourceToCStr ("src/Graphics/GLSL/myshader.frag");
		Graphics::Shader fragShader (source, Graphics::FRAG);

		source = IO::sourceToCStr ("src/Graphics/GLSL/myshader.vert");
		Graphics::Shader vertShader (source, Graphics::VERT);

		Graphics::ShaderProgram program;
		program.addShader (&vertShader);
		program.addShader (&fragShader);
		program.prepareProgram ();



		Graphics::BatchRenderer renderer (program);
		Graphics::Texture2D texture ("Res/Test.png");
		//Graphics::square2D testSquare(program.getID(), 1.0f, 0.0f, 0.0f, 0.0f, &texture);
		LOG_INFO (std::to_string(renderer.getMaxTextureUnits ()));
		int max;
		glGetIntegerv (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
		std::cout << max << std::endl;

		glm::vec3* test = new glm::vec3[NUM_OF_STARS];
		Graphics::Star* gStars = new Graphics::Star[NUM_OF_STARS];
		for ( int i = 0; i < NUM_OF_STARS; i++ ) {
			gStars[i] = Graphics::Star (program.getID (), glm::vec3 (0, 0, 0), 30.f);
		};
		double lastTime = glfwGetTime ();
		double dt = 0;
		int gTimeStep = 0;
		/* Loop until the user closes the window */
		while ( !glfwWindowShouldClose (glWindow.getWindow ()) && gTimeStep < NUM_TIME_STEPS ) {
			double now = glfwGetTime ();
			dt = now - lastTime;
			//std::cout << dt << std::endl;
				/* Render here */
			if ( dt >= 1.0f / 60.0f ) {
				lastTime = now;
				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				rFile->readTimeStep (test, NUM_OF_STARS);
				for ( int j = 0; j < NUM_OF_STARS; j++ ) {
					gStars[j].setPos (test[j]);
					renderer.addMesh (gStars[j]);
				}
				renderer.render ();
				/* Swap front and back buffers */
				glWindow.paint();

				/* Poll for and process events */
				glWindow.pollEvents ();
				dt = 0;
				gTimeStep++;
			}
		}
	}
	glfwTerminate();
	return 0;
}

cl_context getOCLContext()
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
		free(vendorName);
		free(platformName);
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
	cl_context_properties properties[] =
	{
		CL_CONTEXT_PLATFORM, (cl_context_properties)platformIds[selection], 0
	};
	cl_context context;
	context = clCreateContextFromType(properties, dType, NULL, NULL, nullptr);
	free (platformIds);
	return context;

}

cl_device_id getDeviceId (cl_context& context)
{
	cl_int err;
	size_t numDevices = 0;
	cl_device_id* deviceIds;
	err = clGetContextInfo (context, CL_CONTEXT_DEVICES, 0, NULL, &numDevices);
	if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;
	deviceIds = new cl_device_id[sizeof (cl_device_id) * numDevices];
	err = clGetContextInfo (context, CL_CONTEXT_DEVICES, numDevices, deviceIds, NULL);
	cl_uint maxDiminsion;
	for ( int i = 0; i < numDevices / sizeof(cl_device_id); i++ ) {
		size_t size;
		char* deviceName;
		char* deviceVendorName;
		char* deviceVersion;
		cl_uint computeUnits;
		size_t* maxWorkItemSize;

		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_NAME, 0, nullptr, &size);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		deviceName = (char*)malloc (sizeof (char) * size);
		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_NAME, size, deviceName, NULL);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_VENDOR, 0, nullptr, &size);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		deviceVendorName = (char*)malloc (sizeof (char) * size);
		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_VENDOR, size, deviceVendorName, NULL);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_VERSION, 0, nullptr, &size);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;
		deviceVersion = (char*)malloc (sizeof (char) * size);
		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_VERSION, size, deviceVersion, NULL);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof (cl_uint), &computeUnits, NULL);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &maxDiminsion, NULL);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		maxWorkItemSize = (size_t*)malloc (sizeof (size_t) * maxDiminsion);
		err = clGetDeviceInfo (deviceIds[i], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof (size_t) * maxDiminsion, maxWorkItemSize, NULL);
		if ( err ) std::cout << "Something went wrong! Error Number: " << err << std::endl;

		std::cout << i + 1 << ":" << "Device: " << deviceName << " Vendor: " << deviceVendorName << std::endl;
		std::cout << "Version: " << deviceVersion << " \nCompute Units: " << computeUnits << " \nMax work items: ";
		for ( int i = 0; i < maxDiminsion; i++ )
			std::cout << maxWorkItemSize[i] << " ";
		std::cout << std::endl;
		free (deviceName);
		free (deviceVendorName);
		free (deviceVersion);
		free (maxWorkItemSize);
	}
	int selection;
	std::cout << "Please select the device you would like to use:";
	std::cin >> selection;
	while ( selection > numDevices || selection < 1 ) {
		std::cout << "Error! Invaild selection! Please try again.\n";
		std::cout << "Please select the device you would like to use:";
		std::cin >> selection;
	}
	selection--;
	cl_device_id deviceSelection = deviceIds[selection];
	delete[] deviceIds;
	return deviceSelection;
}


cl_command_queue createCommandQueue(cl_context& context, cl_device_id dID)
{
	cl_command_queue result = clCreateCommandQueue (context, dID, 0, nullptr);
	return result;
}

cl_program createProgram (cl_context& context, cl_device_id dID, const char* fileName)
{
	cl_int err = CL_SUCCESS;
	cl_program program;
	std::string srcStr = IO::sourceToCStr (fileName);
	const char* src = srcStr.c_str();
	program = clCreateProgramWithSource (context, 1, &src, NULL, NULL);
	if ( program == NULL ) {
		std::cout << "Failed to create Program!" << std::endl;
		return NULL;
	}
	err = clBuildProgram (program, 0, NULL, "-cl-std=CL1.2", NULL, NULL);
	if ( err != CL_SUCCESS ) {
		char log[8192];
		size_t sizeRet;
		clGetProgramBuildInfo (program, dID, CL_PROGRAM_BUILD_LOG, sizeof (log), log, &sizeRet);
		// Intellisense noted that the log might not be null terminated. I could not find anything in the specification
		// that says that it must be so I assume that it is implementation dependant. I constructed a string and gave it the 
		// size returned to be safe.
		std::string logStr = std::string (log, sizeRet);
		LOG_ERROR (logStr);
		std::cout << logStr << std::endl;
		clReleaseProgram (program);
	}
	return program;
}