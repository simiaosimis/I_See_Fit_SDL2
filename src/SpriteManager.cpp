#include "SpriteManager.h"

std::shared_ptr<Sprite> SpriteManager::load(const std::string& path_) {
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(path_);
	registerResource(path_, sprite);
	return sprite;
}
