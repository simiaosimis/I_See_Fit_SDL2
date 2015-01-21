#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {

	public:
		explicit SoundEffect(const std::string& path_);
		~SoundEffect();

		Mix_Chunk* getMixChunk();
		std::string getPath();

		int channel;

	private:
		Mix_Chunk* mixChunk;
		const std::string path;

};