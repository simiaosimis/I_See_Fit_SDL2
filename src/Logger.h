#pragma once

#include <sstream>

namespace logger {
namespace detail {

class LogBuffer {
	public:
		LogBuffer(const int level);
		LogBuffer(const LogBuffer& log_buffer);
		~LogBuffer();

		template <typename T>
		LogBuffer& operator<<(const T& t) {
			m_log_stream << t;
			return *this;
		}

		const int m_log_level;

	private:
		std::ostringstream m_log_stream;
};

} // namespace detail

template <int level>
detail::LogBuffer log();

using logger_function_ptr = detail::LogBuffer (*) ();

constexpr logger_function_ptr error = log<0>;
constexpr logger_function_ptr warn = log<1>;
constexpr logger_function_ptr info = log<2>;
constexpr logger_function_ptr debug = log<3>;

} // namespace logger
