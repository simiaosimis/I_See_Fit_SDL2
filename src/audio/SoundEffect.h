#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>

namespace sdl2engine {

class SoundEffect {

	public:
		explicit SoundEffect(const std::string& path);
		~SoundEffect();

		Mix_Chunk* MixChunk();
		std::string Path();

		int m_channel;

	private:
		Mix_Chunk* const m_mix_chunk;
		const std::string m_path;
};

} // namespace sdl2engine
