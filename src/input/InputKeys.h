#pragma once

#include <array>

namespace sdl2engine {

enum GameKeys {
	A,
	SPACE,
	ESCAPE,
	MAX
};

using InputArray = std::array<bool, GameKeys::MAX>;

} // namespace sdl2engine
