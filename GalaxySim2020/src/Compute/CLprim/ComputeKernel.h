#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
#include "IO/Logger.h"
#include "Compute/CLprim/ComputeMemBuffer.h"
#include "Compute/CLprim/ComputeCommandQueue.h"
#include "Compute/CLprim/ComputeDevice.h"
#include "Compute/CLprim/ComputeProgram.h"

namespace Compute
{
	/// <summary>
	/// Kernel wrapper for the OpenCl Kernel
	/// </summary>
	class Kernel
	{
	private:
		cl_kernel m_kernel;
		std::weak_ptr<CommandQueue> p_cmdq;
		Kernel (cl_kernel kern, std::weak_ptr<CommandQueue> cmdq)
			: m_kernel(kern), p_cmdq(cmdq)
		{}
	public:
		/// <summary>
		/// A factory method for Kernels
		/// </summary>
		/// <param name="program"> The program that the Kernel needs</param>
		/// <param name="name"> The name of the Kernel function in the OpenCl program</param>
		/// <returns>A unique_ptr object to the Kernel object. If creationg fails it returns an empty unique_ptr object</returns>
		static Kernel* createKernel (Program* program, std::weak_ptr<CommandQueue> cmdq, const char* name)
		{
			cl_int err;
			cl_kernel result = clCreateKernel (program->getProgramID(), name, &err);
			if ( err != CL_SUCCESS )
			{
				LOG_ERROR ("Kernel could not be created! The following opencl error code was given" + err);
				return nullptr;
			}
			return new Kernel (result, cmdq);
		}
		~Kernel ()
		{
			clReleaseKernel (m_kernel);
		}
		template <typename T>
		inline bool setKernelArg (uint32_t pos, const T* data)
		{
			int err = clSetKernelArg(m_kernel, pos, sizeof(T), &data);
			LOG_ERROR_IF("Could not set kernal argument! " + std::to_string(err), err != CL_SUCCESS );
			return err != CL_SUCCESS;
		}

		template<typename T>
		inline bool setKernelMemBufferArg (uint32_t pos, const MemBuffer<T>* data)
		{
			int err = clSetKernelArg (m_kernel, pos, sizeof (cl_mem), data->getMemBufferRef());
			LOG_ERROR_IF ("Could not set kernal argument! " + std::to_string (err), err != CL_SUCCESS);
			return err != CL_SUCCESS;
		}
		/// <summary>
		/// Getter for the opencl kernel
		/// </summary>
		/// <returns> returns the associated cl_kernel object</returns>
		inline const cl_kernel getKernel () const { return m_kernel; }
		inline bool runKernel (size_t workDim, size_t globalWorkSize, size_t localWorkSize) const
		{
			uint32_t err;
			if(!p_cmdq.expired()){
				std::shared_ptr<CommandQueue> q = p_cmdq.lock();
				err = clEnqueueNDRangeKernel(q->getQueue(), m_kernel, workDim, NULL, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
			}
			else 
			{
				LOG_ERROR("Command Queue has expired! Cannot run the kernel!");
				return false;
			}
		}

		inline size_t getPreferredWorkGroupSize (const Device* device)
		{
			size_t result;
			uint32_t err;
			err = clGetKernelWorkGroupInfo (m_kernel, device->getId(), CL_KERNEL_WORK_GROUP_SIZE, sizeof (size_t), &result, NULL);
			LOG_INFO_IF ("Could not obtain OpenCL Kernel's preferred work size! Error Number" + err, err);
			return result;
		}
	};
}

