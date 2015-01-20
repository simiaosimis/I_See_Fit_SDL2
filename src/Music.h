#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>

class Music {

	public:
		explicit Music(const std::string& path_);
		~Music();

		Mix_Music* getMixMusic();
		std::string getPath();

	private:
		Mix_Music* mixMusic;
		const std::string path;

};
