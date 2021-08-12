#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
#include "ComputeDevice.h"
#include "ComputePlatform.h"
namespace Compute
{
	class Context
	{
	private:
		std::vector<std::shared_ptr<Device>> m_devices;
		cl_context m_context;
	public:
		explicit Context (Platform platform, DeviceType deviceType)
		{
			cl_device_type dType;
			switch ( deviceType )
			{
				case DeviceType::Device_CPU:
					dType = CL_DEVICE_TYPE_CPU;
					break;
				case DeviceType::Device_GPU:
					dType = CL_DEVICE_TYPE_GPU;
					break;
				case DeviceType::Device_Accelerator:
					dType = CL_DEVICE_TYPE_ACCELERATOR;
					break;
				case DeviceType::Device_Default:
					dType = CL_DEVICE_TYPE_DEFAULT;
					break;
				case DeviceType::Device_All:
					dType = CL_DEVICE_TYPE_ALL;
					break;
				default:
					dType = CL_DEVICE_TYPE_ALL;
					break;
			}
			cl_context_properties properties[] =
			{
				CL_CONTEXT_PLATFORM, (cl_context_properties)platform.getPlatformId (), 0
			};
			m_context = clCreateContextFromType (properties, dType, NULL, NULL, nullptr);

			cl_int err;
			size_t retSize = 0;
			cl_device_id* deviceIds;
			//numDevices is actually the size of the list in bytes 
			err = clGetContextInfo (m_context, CL_CONTEXT_DEVICES, 0, NULL, &retSize);
			LOG_ERROR_IF ("Could not obtain OpenCL devices from context! Error Number" + err, err);
			size_t numDevices = retSize / sizeof (cl_device_id);
			deviceIds = new cl_device_id[numDevices];
			err = clGetContextInfo (m_context, CL_CONTEXT_DEVICES, retSize, deviceIds, NULL);

			for ( int i = 0; i < numDevices; ++i )
			{
				m_devices.emplace_back(std::make_shared<Device>(deviceIds[i]));
			}
			delete[](deviceIds);
		}
		Context() = default;
		~Context ()
		{
			clReleaseContext (m_context);
		}
		inline std::vector<std::shared_ptr<Device>> getDevices () const { return m_devices; }
		inline const cl_context getCLContext() const {return m_context;}
	};
}