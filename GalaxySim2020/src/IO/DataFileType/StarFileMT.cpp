#include "StarFileMT.h"
namespace IO
{
	typedef Application::Vec3f Vec3f;
	StarFileMT::StarFileMT ()
	{}
	StarFileMT::~StarFileMT ()
	{}
	std::shared_ptr<StarFileMT> StarFileMT::openFile (const std::string & path)
	{
		return std::shared_ptr<StarFileMT> ();
	}
	std::shared_ptr<StarFileMT> StarFileMT::createFile (const std::string& path, uint32_t numStars)
	{
		return std::shared_ptr<StarFileMT> ();
	}
	void StarFileMT::writeTimeStep (const Vec3f* data)
	{}
	std::vector<Vec3f> StarFileMT::getTimeStep ()
	{
		return std::vector<Vec3f> ();
	}
	StarFileMT::StarFileMT (const std::string& path)
	{
		
	}
}