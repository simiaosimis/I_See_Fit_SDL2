#include "audio/MusicManager.h"

namespace sdl2engine {

std::shared_ptr<Music> MusicManager::load(const std::string& path_) {
	std::shared_ptr<Music> music = std::make_shared<Music>(path_);
	registerResource(path_, music);
	return music;
}

} // namespace sdl2engine
