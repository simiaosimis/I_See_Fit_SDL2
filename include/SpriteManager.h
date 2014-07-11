#pragma once

#include "ResourceManager.h"
#include "Sprite.h"

/**
*/
class SpriteManager : public ResourceManager<Sprite> {

	private:
		/**
		* Constructs the desired sprite.
		* @param path_ : Path to the desired sprite.
		*/
		std::shared_ptr<Sprite> load(const std::string& path_);

};
