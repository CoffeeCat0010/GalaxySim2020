#pragma once
#include "Corepch.h"
#include "Math/MVec.h"
#include "IO/BufferedStreamIOMT.h"
namespace IO
{
	class StarFileMT
	{
	private:
		struct Header
		{
			uint64_t versionNum;
			uint64_t offsetToFirst;
			uint64_t numStars;
			uint64_t numTimeSteps;
			uint64_t stride;
		};

		typedef Application::Vec3f Vec3f;
		BufferStreamReaderMT<Vec3f> reader;
		BufferStreamWriterMT<Vec3f> writer;
		std::string path;
		Header header;

	public:
		StarFileMT ();
		~StarFileMT();
		static std::shared_ptr<StarFileMT> openFile(const std::string& path);
		static std::shared_ptr<StarFileMT> createFile( const std::string& path, uint32_t numStars);
		void writeTimeStep (const Vec3f* data);
		std::vector<Vec3f> getTimeStep();
		inline uint64_t getNumStars() {return header.numStars;};
	private:
		StarFileMT(const std::string& path);
	};
}

