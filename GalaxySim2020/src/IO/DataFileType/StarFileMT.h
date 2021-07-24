#pragma once
#include "Corepch.h"
#include "Math/MVec.h"
#include "IO/BufferedStreamIOMT.h"
namespace IO
{
	class StarFileMT
	{
	private:
		enum fileVersion
		{
			LEGACY = 0,
			VER_1_0
		};
		struct Header
		{
			uint64_t versionNum;
			uint64_t offsetToFirst;
			uint64_t numStars;
			uint64_t numTimeSteps;
			uint64_t stride;
		};

		typedef Application::Vec3f Vec3f;
		BufferStreamReaderMT<Vec3f> m_reader;
		BufferStreamWriterMT<Vec3f> m_writer;
		std::string m_path;
		Header m_header;

	public:
		StarFileMT ();
		~StarFileMT();
		static std::shared_ptr<StarFileMT> openFile(const std::string& path, fileVersion version = VER_1_0);
		static std::shared_ptr<StarFileMT> createFile( const std::string& path, uint32_t numStars, uint32_t numTimeSteps);
		void writeTimeStep (const Vec3f* data);
		std::vector<Vec3f> getTimeStep();
		inline uint64_t getNumStars() {return m_header.numStars;};
	private:
		StarFileMT(const std::string& path);
	};
}

