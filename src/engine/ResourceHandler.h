#pragma once

#include <string>
#include <memory>

namespace sdl2engine {

class Sprite;
class Music;
class SoundEffect;

class ResourceHandler {

	public:
		/**
		* @brief The constructor.
		*/
		ResourceHandler();

		// Special member functions declared only for Pimpl idiom with std::unique_ptr.
		~ResourceHandler();
		ResourceHandler(const ResourceHandler&);
		ResourceHandler& operator=(const ResourceHandler&);
		ResourceHandler(ResourceHandler&&);
		ResourceHandler& operator=(ResourceHandler&&);

		/**
		* @return The desired Sprite.
		*
		* @param path : The path to the resource.
		*
		* @note The 'Get' was added to the name to avoid conflict with class Sprite.
		*/
		Sprite* GetSprite(const std::string& path) const;

		/**
		* @return The desired Music.
		*
		* @param path : The path to the resource.
		*
		* @note The 'Get' was added to the name to avoid conflict with class Music.
		*/
		Music* GetMusic(const std::string& path) const;

		/**
		* @return The desired SoundEffect.
		*
		* @param path : The path to the resource.
		*
		* @note The 'Get' was added to the name to avoid conflict with class SoundEffect.
		*/
		SoundEffect* GetSoundEffect(const std::string& path) const;

	private:
		class ResourceHandlerImpl;
		std::unique_ptr<ResourceHandlerImpl> m_pimpl;
};

} // namespace sdl2engine
