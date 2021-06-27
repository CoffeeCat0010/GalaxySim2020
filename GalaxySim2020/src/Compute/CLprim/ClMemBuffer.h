#pragma once
#include <vector>
#include <array>
#include "../../IO/Logger.h"
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
//		std::array<T> m_data;
		cl_context* p_context;
		cl_command_queue* p_clcq;
		cl_mem* m_memBuffer;
		size_t m_Size;
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
		ClMemBuffer (cl_context* context, T* data, size_t numElements, uint64_t flags, bool enable = true)
			:p_context(context), 
		{

		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="context">OpenCl context that the buffer should be created on</param>
		/// <param name="maxElements">Maximum allowable elements in the buffer</param>
		/// <param name="data">Vector that will be copied</param>
		/// <param name="flags">These are the cl_mem flags that specifiy how the buffer should be accessed and used
		///	these can be the originally defined flags or READ_ONLY, WRITE_ONLY, READ_WRITE, HOST_READ_ONLY, HOST_WRITE_ONLY, and COPY_HOST_DATA</param>
		/// <param name="enable">Specifies if the buffer should be created immediately this is true by default</param>
		ClMemBuffer (cl_context* context, int maxElements, std::vector<T>& data, uint64_t flags, bool enable = true);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="context">OpenCl context that the buffer should be created on</param>
		/// <param name="maxElements">Maximum allowable elements in the buffer</param>
		/// <param name="flags">These are the cl_mem flags that specifiy how the buffer should be accessed and used
		///	these can be the originally defined flags or READ_ONLY, WRITE_ONLY, READ_WRITE, HOST_READ_ONLY, HOST_WRITE_ONLY, and COPY_HOST_DATA</param>
		/// <param name="enable">Specifies if the buffer should be created immediately unlike other constructors this must be set</param>
		ClMemBuffer (cl_context* context, int maxElements, uint64_t flags, bool enable)
			:m_data(std::array<T>(maxElements)), p_context(context), enabled(enabled)
		{

		}
		
		~ClMemBuffer ()
		{
			clReleaseMemObject (m_memBuffer);
		}
		/// <summary>
		/// Pushes the given data to the buffer
		/// </summary>
		/// <param name="data"> The data to be pushed to the buffer</param>
		/// <param name="sizeInBytes">The amount of data in bytes to be pushed</param>
		/// <param name="offset">Offset in bytes in the buffer to write to. Default is 0</param>
		void pushToBuffer_block (T* data, size_t sizeInBytes, size_t offset = 0, bool blocking = true )
		{
			cl_int err = clEnqueueWriteBuffer (*p_clcq, m_memBuffer, blocking ? CL_TRUE : CL_FALSE, offset, sizeInBytes, data, 0, NULL, NULL);
			LOG_FATAL_IF ("Unable to push memory to buffer!", err != 0);
		}
		/// <summary>
		/// Tries to pull the specified amount of data from the buffer
		/// </summary>
		/// <param name="sizeInBytes">The expected amount of data in bytes to be pulled from the buffer</param>
		/// <returns> An std::array of the data being pulled</returns>
		std::array<T>* pullFromBuffer (size_t sizeInBytesMax)
		{
			cl_int err = clEnqueueWriteBuffer (*p_clcq, m_memBuffer, blocking ? CL_TRUE : CL_FALSE, offset, sizeInBytes, m_data.data(), 0, NULL, NULL);
			LOG_FATAL_IF ("Unable to fetch memory from buffer!", err != 0);
			return &m_data;
		}
	};
}

