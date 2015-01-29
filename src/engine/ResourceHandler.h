#pragma once

#include "graphics/SpriteManager.h"
#include "audio/MusicManager.h"
#include "audio/SFXManager.h"

namespace sdl2engine {

class ResourceHandler {

	public:
		ResourceHandler();
		~ResourceHandler();

		/**
		* @return The desired Sprite.
		*/
		Sprite* sprite(const std::string& path_);

		/**
		* @return The desired Music.
		*/
		Music* music(const std::string& path_);

		/**
		* @return The desired SoundEffect.
		*/
		SoundEffect* soundEffect(const std::string& path_);

	private:
		SpriteManager* spriteManager;
		MusicManager* musicManager;
		SFXManager* sfxManager;
};

} // namespace sdl2engine
