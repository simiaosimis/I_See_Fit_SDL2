#include "SoundEffect.h"
#include "Logger.h"
#include "UsefulDefines.h"

SoundEffect::SoundEffect(const std::string& path_) :
	channel(-1),
	mixChunk(nullptr),
	path(path_)
{
	this->mixChunk = Mix_LoadWAV(this->path.c_str());

	if(this->mixChunk == nullptr){
		Log(ERROR) << "Couldn't load sound effect (" << this->path << "). " << Mix_GetError();
	}
}

SoundEffect::~SoundEffect() {
	SAFE_DELETE_WITH_FUNCTION(Mix_FreeChunk, this->mixChunk);
}

Mix_Chunk* SoundEffect::getMixChunk() {
	return this->mixChunk;
}

std::string SoundEffect::getPath(){
	return this->path;
}
