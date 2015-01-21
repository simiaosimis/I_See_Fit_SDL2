#include "audio/SFXManager.h"

std::shared_ptr<SoundEffect> SFXManager::load(const std::string& path_) {
	std::shared_ptr<SoundEffect> soundEffect = std::make_shared<SoundEffect>(path_);
	registerResource(path_, soundEffect);
	return soundEffect;
}
