#pragma once
#include "Corepch.h"
namespace IO
{
	template<typename T>
	class BufferStreamReaderMT
	{
	private:
		std::queue<std::vector<T>> m_streamBuffers;
		std::mutex m_readMutex;
		std::mutex m_threadControl;
		std::thread m_readThread;
		std::ifstream m_fileStream;
		std::string m_path;
		

		size_t m_sizePerReadinBytes;
		size_t m_offsetInBytes;
		uint32_t m_numBuffers;
		bool threadShouldEnd;
	public:
		BufferStreamReaderMT ()
			:m_path (""), m_offsetInBytes (0), m_sizePerReadinBytes (0), m_numBuffers (0), threadShouldEnd (true)
		{}
		BufferStreamReaderMT (const std::string& path,size_t offsetInBytes, size_t sizePerReadinBytes, uint32_t numBuffers = 3, std::ios_base::openmode mode = std::ios::binary)
			:m_path(path), m_offsetInBytes(offsetInBytes),  m_fileStream (std::ifstream (path, std::ios::in | mode)), m_sizePerReadinBytes (sizePerReadinBytes), m_numBuffers(numBuffers), threadShouldEnd(false)
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
		/*BufferStreamReaderMT<T>& operator=(BufferStreamReaderMT<T>&& reader2)
		{
			m_path = reader2.m_path;
			m_fileStream = reader2.m_fileStream;
			m_elementsPerRead = reader2.m_elementsPerRead;
			m_numBuffers = reader2.m_numBuffers;
			m_readMutex = std::shared_mutex()
			m_readThread = std::thread(reader2.m_readThread);
			m_threadControl = std::mutex(reader2.m_threadControl);
			m_streamBuffers = reader2.m_streamBuffers;

			return *this;
		}*/
		void startRead ()
		{
			threadShouldEnd = false;
			m_readThread = std::thread(runRead);
		}
		std::vector<T> readBuffer ()
		{
			std::lock_guard<std::mutex> lock (m_readMutex);
			// occasional problem here caused by streambuffers not being checked if empty
			std::vector<T> result = m_streamBuffers.front();
			m_streamBuffers.pop();
			return result;
		}
	private:
		void writeBuffer (const std::vector<T>& data)
		{
			std::lock_guard<std::mutex> lock(m_readMutex);
			m_streamBuffers.push(data);
		}
		std::function<void ()> runRead = [=]()
		{
			m_threadControl.lock();
			bool end = threadShouldEnd;
			m_threadControl.unlock();
			T* buff = (T*)malloc(m_sizePerReadinBytes);
			m_fileStream.seekg(m_offsetInBytes);
			while (!m_fileStream.eof() && !end)
			{
				if(m_streamBuffers.size() < m_numBuffers)
				{
					std::vector<T> data;
					data.reserve(m_sizePerReadinBytes);
					m_fileStream.read((char*)buff, m_sizePerReadinBytes);
					data.insert(data.begin(), buff, buff +( m_sizePerReadinBytes/sizeof(T)));
					writeBuffer(data);
				}
				m_threadControl.lock ();
				end = threadShouldEnd;
				m_threadControl.unlock ();
			}
			delete[] buff;
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
		std::ofstream::openmode m_mode;

		size_t m_sizeWriteInBytes;
		uint32_t m_numBuffers;
		bool threadShouldEnd;
	public:
		BufferStreamWriterMT ()
			:m_path (""), m_sizeWriteInBytes (0), m_numBuffers (0), threadShouldEnd (true)
		{}
		BufferStreamWriterMT (BufferStreamWriterMT&& BSW)
			:m_streamBuffers(BSW.m_streamBuffers), m_writeMutex(BSW.m_writeMutex), m_threadControl(BSW.m_threadControl),
			m_writeThread(BSW.m_writeThread), m_path (BSW.m_path), m_fileStream(BSW.m_fileStream),
			m_sizeWriteInBytes (BSW.m_sizeWriteInBytes), m_numBuffers (BSW.m_numBuffers),threadShouldEnd (BSW.m_numBuffers)
		{}
		BufferStreamWriterMT (const std::string& path, size_t sizeWriteInBytes, uint32_t numBuffers = 3, std::ofstream::openmode mode = std::ofstream::binary)
			:m_path (path), m_fileStream(std::ofstream()), m_mode(mode), m_sizeWriteInBytes (sizeWriteInBytes), m_numBuffers (numBuffers), threadShouldEnd (false)
		{}
		BufferStreamWriterMT (const char* path, size_t m_sizeWriteInBytes, uint32_t numBuffers = 3, std::ofstream::openmode mode = std::ofstream::binary)
			:m_path (path), m_fileStream (std::ofstream ()), m_mode(mode), m_sizeWriteInBytes (sizeWriteInBytes), m_numBuffers (numBuffers), threadShouldEnd (false)
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
		BufferStreamWriterMT<T>& operator=(BufferStreamWriterMT<T>&& writer2)
		{
			BufferStreamWriterMT<T>& result (writer2);
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
			if(!m_streamBuffers.empty()){
				m_fileStream.write ((char*)m_streamBuffers.front ().data (), m_streamBuffers.front ().size () * sizeof(T));
				m_fileStream.flush();
				m_streamBuffers.pop ();
			}
		}
		std::function<void()> runWrite = [=]()
		{
			m_threadControl.lock ();
			bool end = threadShouldEnd;
			m_threadControl.unlock ();
			m_fileStream.open(m_path, m_mode);
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