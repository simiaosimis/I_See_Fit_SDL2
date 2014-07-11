#pragma once

#include "SDLWrapper.h"
#include <string>

class SoundEffect {

	public:
		SoundEffect(const std::string& path_);
		~SoundEffect();

		Mix_Chunk* getMixChunk();
		std::string getPath();

		int channel;

	private:
		Mix_Chunk* mixChunk;
		const std::string path;

};
