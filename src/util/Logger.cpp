#include "Logger.h"
#include <iostream>

namespace logger {

// constexpr implies const, but const is here to stop the compiler from yelling about
// -Wwrite-strings
constexpr const char* k_level_color_map[] {
	"[ ERROR ]",
	"[WARNING]",
	"[ INFO  ]",
	"[ DEBUG ]"
};

LogBuffer::LogBuffer(const int level) :
	m_log_level{level},
	m_log_stream{}
{
}

LogBuffer::LogBuffer(const LogBuffer& log_buffer) :
	m_log_level{log_buffer.m_log_level},
	m_log_stream{}
{
}

LogBuffer::~LogBuffer() {
	std::clog << k_level_color_map[m_log_level] << " - " << m_log_stream.str() << "\n";
}

template <int level>
LogBuffer log() {
	LogBuffer log_buffer{level};
	return log_buffer;
}

template LogBuffer log<0>();
template LogBuffer log<1>();
template LogBuffer log<2>();
template LogBuffer log<3>();

} // namespace logger
