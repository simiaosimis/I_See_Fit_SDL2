#pragma once

#include <array>

namespace sdl2engine {

enum Key {
	FadeOut,
	LogSomething,
	TestSfx,
	TestSfxAfterFadeOut,
	Quit,
	Count // Always last.
};

using InputArray = std::array<bool, Key::Count>;

} // namespace sdl2engine
