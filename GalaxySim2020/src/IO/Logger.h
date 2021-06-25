#pragma once
#include <fstream>
#include <string>

#define LOG_PATH "log/"

#if defined(LOG_VERBOSE)
	#define LOG_INFO(message) \
		IO::logger* l = l->getInstance(); \
		l->printMessage(message, IO::LOG); \
		l = nullptr;
	#define LOG_INFO_IF(message, cond)\
		if(cond) {LOG_INFO(message)};
#else
#define LOG_INFO(message)
#define LOG_INFO_IF(message, cond)
#endif
#if defined(LOG_VERBOSE) || defined(LOG_P3)
	#define LOG_WARN(message) \
		IO::logger* l = l->getInstance(); \
		l->printMessage(message, IO::WARNING); \
		l = nullptr;
	#define LOG_WARN_IF(message, cond)\
		if(cond) {LOG_WARN(message)};
#else
#define LOG_WARN(message)
#define LOG_WARN_IF(message, cond)
#endif
#if defined(LOG_VERBOSE) || defined(LOG_P3) || defined (LOG_P2)
	#define LOG_ERROR(message) \
		IO::logger* l = l->getInstance(); \
		l->printMessage(message, IO::ERROR); \
		l = nullptr;
	#define LOG_ERROR_IF(message, cond)\
		if(cond) {LOG_ERROR(message)};
#else
#define LOG_ERROR(message)
#define LOG_ERROR_IF(message, cond)
#endif
#if defined(LOG_VERBOSE) || defined(LOG_P3) || defined (LOG_P2) ||  defined (LOG_P1)
	#define LOG_FATAL(message) \
		IO::logger* l = l->getInstance(); \
		l->printMessage(message, IO::FATAL); \
		l = nullptr;
	#define LOG_FATAL_IF(message, cond)\
		if(cond) {LOG_FATAL(message)};
#else 
#define LOG_FATAL(message)
#define LOG_FATAL_IF(message, cond)
#endif

namespace IO
{
	enum PRIORITY
	{
		LOG = 0, WARNING = 1, ERROR = 2, FATAL = 3
	};
	class logger
	{
	private:
		std::string path;
		std::fstream log;
		static logger* INSTANCE;
	public:
		void printMessage(const std::string message, enum PRIORITY priority);
		static logger* getInstance()
		{
			if (INSTANCE == nullptr) INSTANCE = new logger();
			return INSTANCE;
		}
	private:
		logger();
	};
}

