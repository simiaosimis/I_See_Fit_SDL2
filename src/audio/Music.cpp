#include "audio/Music.h"
#include "core/Logger.h"

Music::Music(const std::string& path_) :
	mixMusic(nullptr),
	path(path_)
{
	this->mixMusic = Mix_LoadMUS(this->path.c_str());

	if(this->mixMusic == nullptr) {
		logger::error() << "Couldn't load music (" << this->path << "). " << Mix_GetError();
	}
}

Music::~Music() {
	if(this->mixMusic != nullptr) {
		Mix_FreeMusic(this->mixMusic);
	}
}

Mix_Music* Music::getMixMusic() {
	return this->mixMusic;
}

std::string Music::getPath() {
	return this->path;
}
