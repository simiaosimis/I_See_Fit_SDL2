#include "Music.h"
#include "Logger.h"
#include "UsefulDefines.h"

Music::Music(const std::string& path_) :
	mixMusic(nullptr),
	path(path_)
{
	this->mixMusic = Mix_LoadMUS(this->path.c_str());

	if(this->mixMusic == nullptr){
		Log(ERROR) << "Couldn't load music (" << this->path << "). " << Mix_GetError();
	}
}

Music::~Music() {
	SAFE_DELETE_WITH_FUNCTION(Mix_FreeMusic, this->mixMusic);
}

Mix_Music* Music::getMixMusic() {
	return this->mixMusic;
}

std::string Music::getPath(){
	return this->path;
}
