#pragma once

#include <string>
#include <sstream>

enum LogLevel : uint8_t {
	INFO,
	WARN,
	ERROR,
	DEBUG
};

#define Log(logLevel) Logger().log(logLevel)

/**
*/
class Logger {

	public:
		Logger();
		~Logger();

		std::ostringstream& log(const LogLevel level_);

	private:
		std::string logLevelToString(const LogLevel level_);

		std::ostringstream os;

};
