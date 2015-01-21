#pragma once

#include <string>
#include "core/ResourceManager.h"
#include "audio/Music.h"

/**
*/
class MusicManager : public ResourceManager<Music> {

	private:
		/**
		* Constructs the desired music.
		* @param path_ : Path to the desired music.
		*/
		std::shared_ptr<Music> load(const std::string& path_);

};
