#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
#include "IO/Logger.h"
namespace Compute
{
	class Platform
	{	
	private:
		cl_platform_id m_id;
		std::string m_platformName;
		std::string m_platformVendor;
	public:
		Platform (cl_platform_id id)
			:m_id(id), m_platformName(""), m_platformVendor("")
		{
			cl_int err = 0;
			cl_uint numPlatforms;
			cl_platform_id* platformIds;
			err = clGetPlatformIDs (0, NULL, &numPlatforms);
			if ( err )
			{
				std::cout << "Something went wrong! Error Number: " << err << std::endl;
			}
			platformIds = (cl_platform_id*)malloc (sizeof (cl_platform_id) * numPlatforms);
			err = clGetPlatformIDs (numPlatforms, platformIds, NULL);
			if ( err )
			{
				std::cout << "Something went wrong! Error Number: " << err << std::endl;
			}
			for ( int i = 0; i < numPlatforms; i++ )
			{
				size_t size;
				char* platformName;
				char* vendorName;

				err = clGetPlatformInfo (platformIds[i], CL_PLATFORM_NAME, 0, nullptr, &size);
				LOG_ERROR_IF ("Could not obtain OpenCL platform name! Error Number" + err, err);
				platformName = (char*)malloc (sizeof (char) * size);
				err = clGetPlatformInfo (platformIds[i], CL_PLATFORM_NAME, size, platformName, NULL);
				LOG_ERROR_IF ("Could not obtain OpenCL platform name! Error Number" + err, err);

				err = clGetPlatformInfo (platformIds[i], CL_PLATFORM_VENDOR, 0, nullptr, &size);
				LOG_ERROR_IF ("Could not obtain OpenCL platform vendor! Error Number" + err, err);
				vendorName = (char*)malloc (sizeof (char) * size);
				err = clGetPlatformInfo (platformIds[i], CL_PLATFORM_VENDOR, size, vendorName, NULL);
				LOG_ERROR_IF ("Could not obtain OpenCL platform vendor! Error Number" + err, err);


				if(platformName != nullptr)
					m_platformName = std::string(platformName);
				if(vendorName != nullptr)
					m_platformVendor = std::string(vendorName);

				free (vendorName);
				free (platformName);
			}
		}
		inline std::string getPlatformName () { return m_platformName; }
		inline std::string getPlatformVendor () { return m_platformVendor; }
		inline cl_platform_id getPlatformId() {return m_id;}

		inline static std::vector<Platform> getPlatforms() 
		{
			cl_int err = 0;
			cl_uint numPlatforms;
			cl_platform_id* platformIds;
			std::vector<Platform> result;
			err = clGetPlatformIDs (0, NULL, &numPlatforms);
			if ( err )
			{
				std::cout << "Something went wrong! Error Number: " << err << std::endl;
			}
			platformIds = new cl_platform_id[numPlatforms];
			err = clGetPlatformIDs (numPlatforms, platformIds, NULL);
			if ( err )
			{
				std::cout << "Something went wrong! Error Number: " << err << std::endl;
			}
			for ( int i = 0; i < numPlatforms; i++ )
			{
				result.emplace_back(platformIds[i]);
			}
			delete[] platformIds;
			return result;
		}
	};
}