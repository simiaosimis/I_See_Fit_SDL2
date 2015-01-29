#pragma once

#include <array>

namespace sdl2engine {

enum GameKeys {
	UP = 0,
	LEFT,
	RIGHT,
	DOWN,
	SPACE,
	ESCAPE,
	MAX
};

using InputArray = std::array<bool, GameKeys::MAX>;

} // namespace sdl2engine
