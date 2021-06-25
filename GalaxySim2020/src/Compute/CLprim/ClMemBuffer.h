#pragma once
#include <vector>
#include "CL/cl.hpp"
namespace Compute
{
	#define READ_ONLY CL_MEM_READ_ONLY
	#define WRITE_ONLY CL_MEM_WRITE_ONLY
	#define READ_WRITE CL_MEM_READ_WRITE
	#define HOST_READ_ONLY CL_MEM_HOST_READ_ONLY
	#define HOST_WRITE_ONLY CL_MEM_HOST_WRITE_ONLY
	#define COPY_HOST_DATA CL_MEM_COPY_HOST_PTR



	template<class T>
	class ClMemBuffer
	{
	private:
		std::vector<T> m_data;
		cl_mem m_memBuffer;
		size_t m_maxSize;
		size_t m_currSize;
		bool enabled;
	public:
		ClMemBuffer () = default;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="context">OpenCl context that the buffer should be created on</param>
		/// <param name="maxElements">Maximum allowable elements in the buffer</param>
		/// <param name="data">Pointer to the data array that will be written to the buffer</param>
		/// <param name="numElements">Number of elements in the data array</param>
		/// <param name="flags">These are the cl_mem flags that specifiy how the buffer should be accessed and used
		///	these can be the originally defined flags or READ_ONLY, WRITE_ONLY, READ_WRITE, HOST_READ_ONLY, HOST_WRITE_ONLY, and COPY_HOST_DATA
		/// </param>
		/// <param name="enable">Specifies if the buffer should be created immediately this is true by default</param>
		ClMemBuffer (cl_context context, int maxElements, T* data, size_t numElements, uint64_t flags, bool enable = true);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="context">OpenCl context that the buffer should be created on</param>
		/// <param name="maxElements">Maximum allowable elements in the buffer</param>
		/// <param name="data">Vector that will be copied</param>
		/// <param name="flags">These are the cl_mem flags that specifiy how the buffer should be accessed and used
		///	these can be the originally defined flags or READ_ONLY, WRITE_ONLY, READ_WRITE, HOST_READ_ONLY, HOST_WRITE_ONLY, and COPY_HOST_DATA</param>
		/// <param name="enable">Specifies if the buffer should be created immediately this is true by default</param>
		ClMemBuffer (cl_context context, int maxElements, std::vector<T>& data, uint64_t flags, bool enable = true);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="context">OpenCl context that the buffer should be created on</param>
		/// <param name="maxElements">Maximum allowable elements in the buffer</param>
		/// <param name="flags">These are the cl_mem flags that specifiy how the buffer should be accessed and used
		///	these can be the originally defined flags or READ_ONLY, WRITE_ONLY, READ_WRITE, HOST_READ_ONLY, HOST_WRITE_ONLY, and COPY_HOST_DATA</param>
		/// <param name="enable">Specifies if the buffer should be created immediately unlike other constructors this must be set</param>
		ClMemBuffer (cl_context context, int maxElements, uint64_t flags, bool enable);

	};
}

