#pragma once

#include "ResourceManager.h"
#include "SoundEffect.h"
#include <string>

/**
*/
class SFXManager : public ResourceManager<SoundEffect> {

	private:
		/**
		* Constructs the desired sound effect.
		* @param path_ : Path to the desired sound effect.
		*/
		std::shared_ptr<SoundEffect> load(const std::string& path_);

};
