#pragma once
#include "Corepch.h"
#include "Math/MVec.h"
#include "IO/BufferedStreamIOMT.h"
namespace IO
{
	class StarFileMT
	{
	public:
		enum fileVersion
		{
			LEGACY = 0,
			VER_1_0
		};

	private:
		typedef Application::Vec3f Vec3f;
		enum OpenMode
		{
			READ, WRITE, NONE
		};
		struct Header
		{
			uint64_t versionNum;
			uint64_t offsetToFirst;
			uint64_t numStars;
			uint64_t numTimeSteps;
			uint64_t stride;
		};

		std::unique_ptr<BufferStreamReaderMT<Vec3f>> m_reader;
		std::unique_ptr<BufferStreamWriterMT<Vec3f>> m_writer;
		std::string m_path;
		Header m_header;
		OpenMode m_mode;
	public:
		~StarFileMT();
		static StarFileMT* readFile(const std::string& path, fileVersion version = VER_1_0);
		static StarFileMT* createFile( const std::string& path, uint32_t numStars, uint32_t numTimeSteps);
		void writeTimeStep (const Vec3f* data);
		void writeTimeStep (const std::vector<Vec3f>& data);
		std::vector<Vec3f> getTimeStep();
		inline uint64_t getNumStars() {return m_header.numStars;};
	private:
		StarFileMT ();
	public:
		//StarFileMT(const std::string& path);
	};
}

