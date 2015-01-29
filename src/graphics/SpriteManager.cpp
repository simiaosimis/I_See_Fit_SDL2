#include "graphics/SpriteManager.h"

namespace sdl2engine {

std::shared_ptr<Sprite> SpriteManager::load(const std::string& path_) {
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(path_);
	registerResource(path_, sprite);
	return sprite;
}

} // namespace sdl2engine
