#pragma once

#include <string>
#include "core/ResourceManager.h"
#include "graphics/Sprite.h"

namespace sdl2engine {

/**
*/
class SpriteManager : public ResourceManager<Sprite> {

	private:
		/**
		* Constructs the desired sprite.
		* @param path_ : Path to the desired sprite.
		*/
		std::shared_ptr<Sprite> load(const std::string& path_);
};

} // namespace sdl2engine
