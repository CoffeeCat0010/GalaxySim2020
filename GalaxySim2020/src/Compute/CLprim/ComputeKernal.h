#pragma once
#include "CL/cl.hpp"
#include "IO/Logger.h"
#include <memory>

namespace Compute
{
	/// <summary>
	/// Kernel wrapper for the OpenCl Kernel
	/// </summary>
	class Kernel
	{
	private:
		cl_kernel m_kernel;
		Kernel (cl_kernel kern)
			: m_kernel(kern)
		{}
	public:
		/// <summary>
		/// A factory method for Kernels
		/// </summary>
		/// <param name="program"> The program that the Kernel needs</param>
		/// <param name="name"> The name of the Kernel function in the OpenCl program</param>
		/// <returns>A unique_ptr object to the Kernel object. If creationg fails it returns an empty unique_ptr object</returns>
		static std::unique_ptr<Kernel> createKernel (cl_program program, const char* name)
		{
			cl_int err;
			cl_kernel result = clCreateKernel (program, name, &err);
			if ( err != CL_SUCCESS )
			{
				LOG_ERROR ("Kernel could not be created! The following opencl error code was given" + err);
				return nullptr;
			}
			return std::unique_ptr<Kernel> (new Kernel (result));
		}
		~Kernel ()
		{
			clReleaseKernel (m_kernel);
		}
		/// <summary>
		/// Getter for the opencl kernel
		/// </summary>
		/// <returns> returns the associated cl_kernel object</returns>
		inline cl_kernel getKernel () { return m_kernel; }
	};
}

