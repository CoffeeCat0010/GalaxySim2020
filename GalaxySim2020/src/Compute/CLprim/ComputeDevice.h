#pragma once
#include "CL/cl.hpp"
#include "IO/Logger.h"
namespace Compute
{
	enum class DeviceType
	{
		Device_GPU, Device_CPU, Device_Accelerator, Device_Default, Device_All
	};
	class Device
	{
	private:
		cl_device_id m_id;
		std::string m_deviceName;
		std::string m_deviceVendor;
		std::string m_deviceVersion;
		uint32_t m_numComputeUnits;
		uint32_t m_workItemDim;
		std::vector<size_t> m_workItemSizes;

	public:
		Device (cl_device_id id)
			:m_id (id), m_deviceName (""), m_deviceVendor (""), m_deviceVersion (""), m_numComputeUnits (0),
			m_workItemDim (0)
		{
			cl_int err;
			size_t size;
			char* deviceName;
			char* deviceVendorName;
			char* deviceVersion;
			size_t* maxWorkItemSize;

			err = clGetDeviceInfo (id, CL_DEVICE_NAME, 0, nullptr, &size);
			LOG_ERROR_IF ("Could not obtain OpenCL device name! Error Number" + err, err);
			deviceName = (char*)malloc (sizeof (char) * size);
			err = clGetDeviceInfo (id, CL_DEVICE_NAME, size, deviceName, NULL);
			LOG_ERROR_IF ("Could not obtain OpenCL device name! Error Number" + err, err);

			err = clGetDeviceInfo (id, CL_DEVICE_VENDOR, 0, nullptr, &size);
			LOG_ERROR_IF ("Could not obtain OpenCL device vendor! Error Number" + err, err);
			deviceVendorName = (char*)malloc (sizeof (char) * size);
			err = clGetDeviceInfo (id, CL_DEVICE_VENDOR, size, deviceVendorName, NULL);
			LOG_ERROR_IF ("Could not obtain OpenCL device vendor! Error Number" + err, err);

			err = clGetDeviceInfo (id, CL_DEVICE_VERSION, 0, nullptr, &size);
			LOG_ERROR_IF ("Could not obtain OpenCL device version! Error Number" + err, err);
			deviceVersion = (char*)malloc (sizeof (char) * size);
			err = clGetDeviceInfo (id, CL_DEVICE_VERSION, size, deviceVersion, NULL);
			LOG_ERROR_IF ("Could not obtain OpenCL device version! Error Number" + err, err);

			err = clGetDeviceInfo (id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof (uint32_t), &m_numComputeUnits, NULL);
			LOG_ERROR_IF ("Could not obtain OpenCL device's number of compute units! Error Number" + err, err);


			err = clGetDeviceInfo (id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof (uint32_t), &m_workItemDim, NULL);
			LOG_ERROR_IF ("Could not obtain OpenCL device's work item dimensions! Error Number" + err, err);

			maxWorkItemSize = (size_t*)malloc (sizeof (size_t) * m_workItemDim);
			err = clGetDeviceInfo (id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof (size_t) * m_workItemDim, maxWorkItemSize, NULL);
			LOG_ERROR_IF ("Could not obtain OpenCL device's work item sizes! Error Number" + err, err);
			
			if(deviceName != nullptr)
				m_deviceName = std::string (deviceName);
			if ( deviceVendorName != nullptr )
				m_deviceVendor = std::string (deviceVendorName);
			if ( deviceVersion != nullptr )
				m_deviceVersion = std::string (deviceVersion);

			m_workItemSizes = std::vector<size_t> (maxWorkItemSize, maxWorkItemSize + m_workItemDim);

			free (deviceName);
			free (deviceVendorName);
			free (deviceVersion);
			free (maxWorkItemSize);
		}
		~Device ()
		{
			clReleaseDevice (m_id);
		}
		inline const cl_device_id getId () const { return m_id; }
		inline std::string getDeviceName () { return m_deviceName; }
		inline std::string getDeviceVendor () { return m_deviceVendor; }
		inline std::string getDeviceVersion () { return m_deviceVersion; }
		inline uint32_t getNumComputeUnits () { return m_numComputeUnits; }
		inline uint32_t getWorkItemDiminsion () { return m_workItemDim; }
		inline std::vector<size_t> getWorkItemSizes () { return m_workItemSizes; }
	};
}