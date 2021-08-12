#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
#include "Compute/CLprim/ComputeDevice.h"
#include "Compute/CLprim/ComputeContext.h"

namespace Compute
{
	class CommandQueue
	{
	private:
		cl_command_queue queue;
	public:
		explicit CommandQueue (const Context* con, const Device* device)
		{
			queue = clCreateCommandQueue(con->getCLContext(), device->getId(), 0, nullptr);
		}
		~CommandQueue ()
		{
			clReleaseCommandQueue(queue);
		}
		const cl_command_queue getQueue() const {return queue;}
	};
}