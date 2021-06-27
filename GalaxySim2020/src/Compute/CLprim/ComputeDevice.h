#pragma once
#include "CL/cl.hpp"
namespace Compute
{
	class Device
	{
	private:
		cl_device_id m_id;
	public:
		Device (cl_device_id id)
			:m_id(id)
		{}
		~Device() {
			clReleaseDevice (m_id);
		}
		inline cl_device_id getId () { return m_id; }
	};
}