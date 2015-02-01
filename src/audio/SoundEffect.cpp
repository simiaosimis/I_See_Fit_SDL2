#include "audio/SoundEffect.h"
#include "util/Logger.h"

namespace sdl2engine {

SoundEffect::SoundEffect(const std::string& path) :
	m_channel{-1},
	m_mix_chunk{Mix_LoadWAV(path.c_str())},
	m_path{path}
{
	if(m_mix_chunk == nullptr) {
		log_error() << "Couldn't load sound effect (" << m_path << "). " << Mix_GetError();
	}
}

SoundEffect::~SoundEffect() {
	if(m_mix_chunk != nullptr) {
		Mix_FreeChunk(m_mix_chunk);
	}
}

Mix_Chunk* SoundEffect::MixChunk() const {
	return m_mix_chunk;
}

std::string SoundEffect::Path() const {
	return m_path;
}

int SoundEffect::Channel() const {
	return m_channel;
}

void SoundEffect::SetChannel(const int channel) {
	m_channel = channel;
}

} // namespace sdl2engine
