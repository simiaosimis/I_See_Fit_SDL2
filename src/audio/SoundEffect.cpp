#include "audio/SoundEffect.h"
#include "core/Logger.h"

SoundEffect::SoundEffect(const std::string& path_) :
	channel(-1),
	mixChunk(nullptr),
	path(path_)
{
	this->mixChunk = Mix_LoadWAV(this->path.c_str());

	if(this->mixChunk == nullptr) {
		logger::error() << "Couldn't load sound effect (" << this->path << "). " << Mix_GetError();
	}
}

SoundEffect::~SoundEffect() {
	if(this->mixChunk != nullptr) {
		Mix_FreeChunk(this->mixChunk);
	}
}

Mix_Chunk* SoundEffect::getMixChunk() {
	return this->mixChunk;
}

std::string SoundEffect::getPath() {
	return this->path;
}