#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
#include "IO/Logger.h"
#include "IO/GSIO.h"
#include "Compute/CLprim/ComputeContext.h"
#include "Compute/CLprim/ComputeDevice.h"
// Todo: consider making a logger and IO interface and then passing the logger through the layer or event messaging system
namespace Compute
{
	class Program
	{
		/// <summary>
		/// Program wrapper for an opencl program
		/// </summary>
	private:
		cl_program m_programID;
		Program (cl_program program)
			:m_programID (program)
		{}

	public:
		/// <summary>
		/// A Program creation factory
		/// </summary>
		/// <param name="filePath">The file path to the opencl program</param>
		/// <param name="context"> The context that you want the program to run in</param>
		/// <param name="device"> The device that you would like the program to run on</param>
		/// <returns> A unique pointer to a program. If program creation fails it returns an empty unique_ptr object</returns>
		static Program* createProgram (const char* filePath, const Context& context, const Device& device)
		{
			// todo: define opencl versions
			cl_int err = CL_SUCCESS;
			cl_program result;
			std::string srcStr = IO::sourceToCStr (filePath);
			const char* src = srcStr.c_str ();
			result = clCreateProgramWithSource (context.getCLContext(), 1, &src, NULL, NULL);
			if ( result == NULL )
			{
				LOG_FATAL ("Failed to create opencl Program!");
				// return essentially nullptr
				return nullptr;
			}
			err = clBuildProgram (result, 0, NULL, "-cl-std=CL1.2", NULL, NULL);
			if ( err != CL_SUCCESS )
			{
				char log[8192];
				size_t sizeRet;
				clGetProgramBuildInfo (result, device.getId(), CL_PROGRAM_BUILD_LOG, sizeof (log), log, &sizeRet);
				// Intellisense noted that the log might not be null terminated. I could not find anything in the specification
				// that says that it must be so I assume that it is implementation dependant. I constructed a string and gave it the 
				// size returned to be safe.
				std::string logStr = std::string (log, sizeRet);
				LOG_ERROR (logStr);
				clReleaseProgram (result);
				// return essentially nullptr
				return nullptr;
			}
			return new Program (result);
		}
		~Program ()
		{
			clReleaseProgram (m_programID);
		}
		/// <summary>
		/// A getter for the associated opencl program
		/// </summary>
		/// <returns> The associated cl_program object</returns>
		inline const cl_program getProgramID () const { return m_programID; }
	};
}
