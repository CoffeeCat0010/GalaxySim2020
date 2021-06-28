
#include "Corepch.h"
#include "StarFile.h"

namespace IO
{
	StarFile::StarFile (const std::string& path, std::ios_base::openmode mode)
		:m_path (path), m_stream (new std::fstream (path, mode)), m_header ({ 0, 0 })
	{}

	StarFile* StarFile::createFile (const std::string& path, uint32_t numStars)
	{
		StarFile* result = new StarFile(path, std::ios::out | std::ios::binary | std::ios::trunc);
		result->m_header = { sizeof (Header), numStars, (uint64_t)numStars * 3 * sizeof (float) };
		result->m_stream->write ((char*)&(result->m_header), sizeof(Header));
		return result;
	}

	StarFile* StarFile::readFile (const std::string& path)
	{
		StarFile* result = new StarFile (path, std::ios::in | std::ios::binary);
		uint64_t inHeader[3];
		result->m_stream->read ((char*) inHeader, sizeof(uint64_t) * 3);
		result->m_header.m_offsetToFirst = inHeader[0];
		result->m_header.m_numStars = inHeader[1];
		result->m_header.m_stride = inHeader[2];
		return result;
	}

	void StarFile::writeTimeStep (const cl_float3* data)
	{
		// TODO: buffered write, query for buffer alignment
		for ( int i = 0; i < m_header.m_numStars; ++i ) {
			m_stream->write ((char*)&(data[i].x), sizeof (float));
			m_stream->write ((char*)&(data[i].y), sizeof (float));
			m_stream->write ((char*)&(data[i].z), sizeof (float));
		}
	}
	//TODO: implement 
	void StarFile::writeSubTimeStep (const cl_float3 * data, size_t sizeOfArray)
	{}

	void StarFile::readTimeStep (glm::vec3 * data, size_t numElementsInBuf)
	{
		for ( int i = 0; i < m_header.m_numStars; ++i ) {
			m_stream->read ((char*)&(data[i].x), sizeof (float));
			m_stream->read ((char*)&(data[i].y), sizeof (float));
			m_stream->read ((char*)&(data[i].z), sizeof (float));
		}
	}


}
