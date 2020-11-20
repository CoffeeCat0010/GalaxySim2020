#include "Logger.h"
#include <chrono>
#include <ctime>
#include <time.h>


namespace IO
{

	logger* logger::INSTANCE = nullptr;
	logger::logger()
	{
		char buff[70];
		auto now = std::chrono::system_clock::now();
		std::time_t tt = std::chrono::system_clock::to_time_t(now);
		struct tm time;
		localtime_s(&time, &tt);
		strftime(buff, sizeof(buff), "%y%m%e%H%M%S", &time);
		path = LOG_PATH + (std::string)buff + ".txt";
		log = std::fstream(path, std::fstream::out);
	}
	void logger::printMessage(const std::string message, enum PRIORITY priority)
	{
		char buff[70];
		auto now = std::chrono::system_clock::now();
		std::time_t tt = std::chrono::system_clock::to_time_t(now);
		struct tm time;
		localtime_s(&time, &tt);
		strftime(buff, sizeof(buff), "%T", &time);
		std::string str = (std::string)buff + " ";

		switch (priority)
		{
		case WARNING:
			str += "[WARNING] ";
			break;
		case ERROR:
			str += "[ERROR] ";
			break;
		case FATAL:
			str += "[FATAL] ";
			break;
		default:
			str += "[MESSAGE] ";
			break;
		}
		str += message;
		this->log << str << "\n";
	}
}
