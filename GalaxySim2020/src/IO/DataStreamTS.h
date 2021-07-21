#pragma once
#include "Corepch.h"
namespace IO
{
	template <typename T, size_t numElementsInBuffer>
	class DataStreamTS
	{
	private:
		std::mutex m_mutex;
		std::queue<std::vector<T>> m_stream;
	public:
		void in (T* data, size_t size)
		{
			std::lock_guard<std::mutex> guard (m_mutex);
			m_stream.push (std::vector<T> (data, data + size));
		}
		void in (std::array<> data)
		{
			std::lock_guard<std::mutex> guard (m_mutex);
			m_stream.push (std::vector<T> (data.begin(), data.end()));

		}
		std::array<T> out ()
		{
			std::array<T> result;
			{
				std::lock_guard<std::mutex> guard (m_mutex);
				result = std::array<T> (m_data);
			}
			return result;
		}
	};
}
