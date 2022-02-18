#pragma once
#include"Corepch.h"
#include <vector>
#include <array>
#include "../../IO/Logger.h"
#include "CL/cl.hpp"
#include "Utility/Math/Bits.h"
#include "Compute/CLprim/ComputeContext.h"
namespace Compute
{
	enum BufferFlags
	{
		Read_Write = CL_MEM_READ_WRITE, 
		Write_Only = CL_MEM_WRITE_ONLY,
		Read_Only  = CL_MEM_READ_ONLY,

		Use_Host_Ptr   = CL_MEM_USE_HOST_PTR,
		Alloc_Host_Ptr = CL_MEM_ALLOC_HOST_PTR,
		Copy_Host_Ptr  = CL_MEM_COPY_HOST_PTR
	};
	template<class T>
	class MemBuffer
	{
	private:
		std::weak_ptr<Context> p_context;
		std::weak_ptr<CommandQueue> p_clcq;
		cl_mem m_memBuffer;
		size_t m_numElements;
	private:
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
		explicit MemBuffer (std::weak_ptr<Context> context, std::weak_ptr<CommandQueue> q , cl_mem memBuffer,  size_t numElements)
			:p_context(context), p_clcq(q), m_memBuffer(memBuffer), m_numElements(numElements)
		{
		}

	public:
		static MemBuffer* createMemBufferWithData (std::weak_ptr<Context> context, std::weak_ptr<CommandQueue> q, size_t numElements, T* data, uint32_t flags)
		{
			cl_int err;
			std::shared_ptr<Context> l_context = context.lock();
			cl_mem buffer = clCreateBuffer (l_context->getCLContext(), flags, sizeof (T) * numElements, data, &err);
			if(err != CL_SUCCESS){
				LOG_ERROR("Could not create memory buffer! OpenCL error: " + err);
				return nullptr;
			}
			return new MemBuffer(context,	q, buffer, numElements);
		}
		static MemBuffer* createMemBuffer (std::weak_ptr<Context> context, std::weak_ptr<CommandQueue> q, size_t numElements, uint32_t flags)
		{
			{
				cl_int err;
				std::shared_ptr<Context> l_context = context.lock ();
				cl_mem buffer = clCreateBuffer (l_context->getCLContext (), flags, sizeof (T) * numElements, NULL, &err);
				if ( err != CL_SUCCESS )
				{
					LOG_ERROR ("Could not create memory buffer! OpenCL error: " + err);
					return nullptr;
				}
				return new MemBuffer (context, q, buffer, numElements);
			}
		}
		~MemBuffer ()
		{
			clReleaseMemObject (m_memBuffer);
		}
		/// <summary>
		/// Pushes the given data to the buffer
		/// </summary>
		/// <param name="data"> The data to be pushed to the buffer</param>
		/// <param name="sizeInBytes">The amount of data in bytes to be pushed</param>
		/// <param name="offset">Offset in bytes in the buffer to write to. Default is 0</param>
		void pushToBuffer(T* data, size_t numElements, size_t offset = 0, bool blocking = true )
		{
			size_t sizeInBytes = sizeof (T) * numElements;
			std::shared_ptr<CommandQueue> l_cmdq = p_clcq.lock();
			cl_int err = clEnqueueWriteBuffer (l_cmdq->getQueue(), m_memBuffer, blocking ? CL_TRUE : CL_FALSE, offset, sizeInBytes, data, 0, NULL, NULL);
			LOG_FATAL_IF ("Unable to push memory to buffer!", err != 0);
		}
		/// <summary>
		/// Tries to pull the specified amount of data from the buffer
		/// </summary>
		/// <param name="sizeInBytes">The expected amount of data in bytes to be pulled from the buffer</param>
		/// <returns> An std::array of the data being pulled</returns>
		std::vector<T> pullFromBuffer (size_t maxElements, bool blocking = true)
		{
			size_t sizeInBytes = sizeof(T) * maxElements;
			T* data = new T[maxElements];
			std::shared_ptr<CommandQueue> l_cmdq = p_clcq.lock ();
			cl_int err = clEnqueueReadBuffer (l_cmdq->getQueue(), m_memBuffer, blocking ? CL_TRUE : CL_FALSE, 0, sizeInBytes, data, 0, NULL, NULL);
			LOG_FATAL_IF ("Unable to fetch memory from buffer!", err != 0);
			std::vector<T> result(data, data + maxElements);
			delete[] data;
			return result;
		}
		/// <summary>
		/// Tries to pull the specified amount of data from the buffer and put it into the specified array.
		/// This overload is espically useful when you have a large amount of data that you want to go into
		/// a pre-allocated array. The array must be of the same type as the objects stored in the memBuffer;
		/// </summary>
		/// <param name="maxElements">The expected amount of data in bytes to be pulled from the buffer</param>
		/// <param name="arrOut">A pointer to the array where the data will be put.</param>
		/// <param name="blocking"></param>
		void pullFromBuffer (size_t maxElements, float* arrOut, bool blocking = true)
		{
			size_t sizeInBytes = sizeof (T) * maxElements;
			std::shared_ptr<CommandQueue> l_cmdq = p_clcq.lock ();
			cl_int err = clEnqueueReadBuffer (l_cmdq->getQueue (), m_memBuffer, blocking ? CL_TRUE : CL_FALSE, 0, sizeInBytes, arrOut, 0, NULL, NULL);
			LOG_FATAL_IF ("Unable to fetch memory from buffer!", err != 0);
		}

		bool copyFromBuffer (const MemBuffer<T>* other, size_t numElements )
		{
			//TODO: Probably Breaks things if things go wrong ;D
			if ( p_clcq.expired () )
				return false;
			std::shared_ptr<CommandQueue> q = p_clcq.lock();
			cl_int err = clEnqueueCopyBuffer(q->getQueue(), other->getMemBuffer(), this->getMemBuffer(), 0, 0,
																				sizeof(T) * numElements, 0, NULL, NULL);
			if ( err != CL_SUCCESS )
			{
				LOG_ERROR("Unable to copy buffers!");
				return false;
			}
			return true;
		}

		inline const cl_mem getMemBuffer () const { return m_memBuffer; }
		inline cl_mem* getMemBufferPtr () const { return &m_memBuffer; }
	};
}

