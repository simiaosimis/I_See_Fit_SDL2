#pragma once

#include "SpriteManager.h"
#include "MusicManager.h"
#include "SFXManager.h"

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
