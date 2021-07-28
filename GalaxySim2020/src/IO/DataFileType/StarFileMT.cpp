#include "StarFileMT.h"
namespace IO
{
	#define CURRENT_VER VER_1_0
	typedef Application::Vec3f Vec3f;

	StarFileMT::StarFileMT ()
	: m_mode(NONE)
	{}
	StarFileMT::~StarFileMT ()
	{}
	StarFileMT* StarFileMT::readFile (const std::string& path, fileVersion version)
	{
		StarFileMT* result = new StarFileMT ();
		std::ifstream file = std::ifstream (path, std::ios_base::in | std::ios_base::binary);
		result->m_path = path;
		if ( version == LEGACY )
		{
			uint64_t inHeader[3];
			file.read((char*)inHeader, sizeof (uint64_t) * 3);
			result->m_header.offsetToFirst = inHeader[0];
			result->m_header.numStars = inHeader[1];
			result->m_header.stride = inHeader[2];
		}
		else
		{
			uint64_t inHeader[5];
			file.read ((char*)inHeader, sizeof (uint64_t) * 5);
			result->m_header.versionNum = inHeader[0];
			result->m_header.offsetToFirst = inHeader[1];
			result->m_header.numStars = inHeader[2];
			result->m_header.numTimeSteps = inHeader[3];
			result->m_header.stride = inHeader[4];
		}
		result->m_reader = std::make_unique<BufferStreamReaderMT<Vec3f>>(path, result->m_header.numStars * sizeof(Vec3f), 3, std::ios_base::binary);
		result->m_reader->startRead();
		result->m_mode = READ;
		return result;
	}
	StarFileMT* StarFileMT::createFile (const std::string& path, uint32_t numStars, uint32_t numTimeSteps)
	{
		StarFileMT* result = new StarFileMT();
		std::ofstream file = std::ofstream (path, std::ios_base::out | std::ios_base::binary);
		result->m_path = path;
		result->m_header.versionNum = CURRENT_VER;
		result->m_header.offsetToFirst = sizeof(uint64_t) * 5;
		result->m_header.numStars = numStars;
		result->m_header.numTimeSteps = numTimeSteps;
		result->m_header.stride = numStars * 3 * sizeof(float);
		file.write ((char*)&(result->m_header), sizeof (Header));
		result->m_writer = std::make_unique < BufferStreamWriterMT<Vec3f>>(path, result->m_header.stride, std::ios_base::binary | std::ios_base::app);
		result->m_writer->startWrite();
		result->m_mode = WRITE;
		return result;
	}
	void StarFileMT::writeTimeStep (const Vec3f* data)
	{
		// Potential for errors. Take look at in the future;
		std::vector<Vec3f> vec(data, data + m_header.numStars);
		writeTimeStep(vec);
	}
	void StarFileMT::writeTimeStep (const std::vector<Vec3f>& data)
	{
		if ( m_mode == WRITE && data.size () == m_header.numStars )
		{
			m_writer->writeBuffer(data);
		}
	}
	std::vector<Vec3f> StarFileMT::getTimeStep ()
	{
		if(m_mode == READ)
			return m_reader->readBuffer();
		else
			return std::vector<Vec3f>();
	}
	/*StarFileMT::StarFileMT (const std::string& path)
		: m_path(path), m_header(), m_mode(NONE)
	{}*/
}