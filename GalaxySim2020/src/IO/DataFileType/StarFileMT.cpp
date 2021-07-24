#include "StarFileMT.h"
namespace IO
{
	#define CURRENT_VER VER_1_0
	typedef Application::Vec3f Vec3f;
	StarFileMT::StarFileMT ()
	{}
	StarFileMT::~StarFileMT ()
	{}
	std::shared_ptr<StarFileMT> StarFileMT::openFile (const std::string& path, fileVersion version)
	{
		std::shared_ptr<StarFileMT> result = std::make_shared<StarFileMT> (path, version);
		std::ifstream file = std::ifstream (path, std::ios_base::in | std::ios_base::binary);
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
		return result;
	}
	std::shared_ptr<StarFileMT> StarFileMT::createFile (const std::string& path, uint32_t numStars, uint32_t numTimeSteps)
	{
		std::shared_ptr<StarFileMT> result = std::make_shared<StarFileMT> (path);
		std::ofstream file = std::ofstream (path, std::ios_base::out | std::ios_base::binary);
		result->m_header.versionNum = CURRENT_VER;
		result->m_header.offsetToFirst = sizeof(uint64_t) * 5;
		result->m_header.numStars = numStars;
		result->m_header.numTimeSteps = numTimeSteps;
		result->m_header.stride = numStars * 3 * sizeof(float);
		file.write ((char*)&(result->m_header), sizeof (Header));
		result->m_writer = BufferStreamWriterMT<Vec3f>(path, result->m_header.stride, std::ios_base::binary | std::ios_base::app);
		return result;
	}
	void StarFileMT::writeTimeStep (const Vec3f* data)
	{}
	std::vector<Vec3f> StarFileMT::getTimeStep ()
	{
		return std::vector<Vec3f> ();
	}
	StarFileMT::StarFileMT (const std::string& path)
		: m_path(path)
	{}
}