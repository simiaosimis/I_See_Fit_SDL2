#include "audio/Music.h"
#include "util/Logger.h"

namespace sdl2engine {

Music::Music(const std::string& path) :
	m_mix_music{Mix_LoadMUS(path.c_str())},
	m_path{path}
{
	if(m_mix_music == nullptr) {
		log_error() << "Couldn't load music (" << m_path << "). " << Mix_GetError();
	}
}

Music::~Music() {
	if(m_mix_music != nullptr) {
		Mix_FreeMusic(m_mix_music);
	}
}

Mix_Music* Music::MixMusic() {
	return m_mix_music;
}

std::string Music::Path() {
	return m_path;
}

} // namespace sdl2engine
