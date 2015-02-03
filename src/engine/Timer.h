#pragma once

#include <chrono>

namespace sdl2engine {

class Timer {

	private:
		using clock = std::chrono::steady_clock;

	public:
		Timer();
		double GetFrameTime();
		void Reset();

	private:
		clock::time_point m_last_time;
		clock::time_point m_now;
};

} // namespace sdl2engine
