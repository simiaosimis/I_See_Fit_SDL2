#pragma once

#include "ResourceManager.h"
#include "Music.h"

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
