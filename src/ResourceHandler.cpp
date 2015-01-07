#include "ResourceHandler.h"

ResourceHandler::ResourceHandler() :
	spriteManager(new SpriteManager()),
	musicManager(new MusicManager()),
	sfxManager(new SFXManager())
{

}

ResourceHandler::~ResourceHandler() {
	delete spriteManager;
	delete musicManager;
	delete sfxManager;
}

Sprite* ResourceHandler::sprite(const std::string& path_) {
	return this->spriteManager->get(path_);
}

Music* ResourceHandler::music(const std::string& path_) {
	return this->musicManager->get(path_);
}

SoundEffect* ResourceHandler::soundEffect(const std::string& path_) {
	return this->sfxManager->get(path_);
}
