#pragma once

#include <string>
#include "core/ResourceManager.h"
#include "audio/SoundEffect.h"

namespace sdl2engine {

/**
*/
class SFXManager : public ResourceManager<SoundEffect> {

	private:
		/**
		* Constructs the desired sound effect.
		* @param path_ : Path to the desired sound effect.
		*/
		std::shared_ptr<SoundEffect> load(const std::string& path_);
};

} // namespace sdl2engine
