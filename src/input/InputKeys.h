#pragma once

#include <array>

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
