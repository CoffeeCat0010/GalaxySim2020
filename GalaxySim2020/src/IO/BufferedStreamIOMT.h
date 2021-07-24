#pragma once
#include "Corepch.h"
namespace IO
{
	template<typename T>
	class BufferStreamReaderMT
	{
	private:
		std::queue<std::vector<T>> m_streamBuffers;
		std::shared_mutex m_readMutex;
		std::mutex m_threadControl;
		std::thread m_readThread;
		std::ifstream m_fileStream;
		std::string m_path;

		size_t m_elementsPerRead;
		uint32_t m_numBuffers;
		bool threadShouldEnd;
	public:
		BufferStreamReaderMT ()
			:m_path (""), m_elementsPerRead (0), m_numBuffers (0), threadShouldEnd (true)
		{}
		BufferStreamReaderMT (const std::string& path, size_t elementsPerRead, uint32_t numBuffers = 3, std::ios_base::openmode mode = std::ios::binary)
			:m_path(path), m_fileStream (ifstream (path, std::ios::in | mode)), m_elementsPerRead(elementsPerRead), m_numBuffers(numBuffers), threadShouldEnd(false)
		{}
		BufferStreamReaderMT (const std::string& path, size_t elementsPerRead, uint32_t numBuffers = 3, std::ios_base::openmode mode = std::ios::binary)
			:m_path (path), m_fileStream (ifstream (path, std::ios::in | mode)), m_elementsPerRead (elementsPerRead), m_numBuffers (numBuffers), threadShouldEnd(false)
		{}
		~BufferStreamReaderMT ()
		{
			if(m_readThread.joinable()){
				{
					std::lock_guard<std::mutex> guard(m_threadControl);
					threadShouldEnd = true;
				}
				m_readThread.join();
			}
		}
		void startRead ()
		{
			m_readThread = std::thread(runRead);
		}
		std::vector<T> readBuffer ()
		{
			std::shared_lock<std::shared_mutex> lock (m_readMutex);
			std::vector<T> result = m_streamBuffers.front();
			m_streamBuffers.pop();
			return result;
		}
	private:
		void writeBuffer (const std::vector<T>& data)
		{
			std::unique_lock lock(m_readMutex);
			m_streamBuffers.push(data);
		}
		auto runRead = []()
		{
			m_threadControl.lock();
			bool end = threadShouldEnd;
			m_threadControl.unlock();
			while (!m_fileStream.eof() && !end)
			{
				if(m_streamBuffers.size() < m_numBuffers)
				{
					std::vector<T> data;
					data.reserve(m_elementsPerRead * sizeof(T));
					m_fileStream.read(data.data(), data.size());
					writeBuffer(data);
				}
				m_threadControl.lock ();
				end = threadShouldEnd;
				m_threadControl.unlock ();
			}
		};
	};

	template<typename T>
	class BufferStreamWriterMT
	{
	private:
		std::queue<std::vector<T>> m_streamBuffers;
		std::mutex m_writeMutex;
		std::mutex m_threadControl;
		std::thread m_writeThread;
		std::string m_path;
		std::ofstream m_fileStream;

		size_t m_elementsPerWrite;
		uint32_t m_numBuffers;
		bool threadShouldEnd;
	public:
		BufferStreamWriterMT ()
			:m_path (""), m_elementsPerRead (0), m_numBuffers (0), threadShouldEnd (true)
		{}
		BufferStreamWriterMT (const BufferStreamWriter& BSW)
			:m_streamBuffers(BSW.m_streamBuffers), m_writeMutex(BSW.m_writeMutex), m_threadControl(BSW.m_threadcontrol),
			m_writeThread(BSW.m_writeThread), m_path (BSW.m_path), m_fileStream(BSW.m_fileStream)
			m_elementsPerWrite (BSW.m_elementsPerWrite), m_numBuffers (BSW.m_numbuffers),threadShouldEnd (BSW.m_numBuffers)
		{}
		BufferStreamWriterMT (const std::string& path, size_t elementsPerRead, uint32_t numBuffers = 3, std::ios_base::openmode mode = std::ios::binary)
			:m_path (path), m_fileStream(ifstream(path, std::ios::out | mode)), m_elementsPerRead (elementsPerRead), m_numBuffers (numBuffers), threadShouldEnd (false)
		{}
		BufferStreamWriterMT (const char* path, size_t sizeOfReads, uint32_t numBuffers = 3, std::ios_base::openmode mode = std::ios::binary)
			:m_path (path), m_fileStream (ifstream (path, std::ios::out | mode)),m_elementsPerRead (elementsPerRead), m_numBuffers (numBuffers), threadShouldEnd (false)
		{}
		~BufferStreamWriterMT ()
		{
			if ( m_writeThread.joinable () )
			{
				{
					std::lock_guard<std::mutex> guard (m_threadControl);
					threadShouldEnd = true;
				}
				m_writeThread.join ();
			}
		}
		BufferStreamWriterMT<T>& operator=(const BufferStreamWriterMT<T>& writer2)
		{
			BufferStreamWriterMT<T> result (writer2);
			return result;
		}
		void startWrite ()
		{
			m_writeThread = std::thread (runWrite);
		}
		bool writeBuffer (const std::vector<T>& data)
		{
			if ( m_streamBuffers.size () < m_numBuffers ){
				std::lock_guard<std::mutex> guard (m_writeMutex);
				m_streamBuffers.push (data);
				return true;
			}
			return false;
		}
	private:
		void readBufferToFile ()
		{
			std::lock_guard<std::mutex> guard (m_writeMutex);
			m_fileStream.write (m_streamBuffers.front ().data (), m_streamBuffers.front ().size ());
			m_streamBuffers.pop ();
		}
		auto runWrite = []()
		{
			m_threadControl.lock ();
			bool end = threadShouldEnd;
			m_threadControl.unlock ();
			while (!end)
			{
				readBufferToFile();
				m_threadControl.lock ();
				end = threadShouldEnd;
				m_threadControl.unlock ();
			}
		};
	};
}