#include "audio/SFXManager.h"

namespace sdl2engine {

std::shared_ptr<SoundEffect> SFXManager::load(const std::string& path_) {
	std::shared_ptr<SoundEffect> soundEffect = std::make_shared<SoundEffect>(path_);
	registerResource(path_, soundEffect);
	return soundEffect;
}

} // namespace sdl2engine
