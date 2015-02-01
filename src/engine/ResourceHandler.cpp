#include "engine/ResourceHandler.h"
#include "graphics/SpriteManager.h"
#include "audio/MusicManager.h"
#include "audio/SFXManager.h"

namespace sdl2engine {

class ResourceHandler::ResourceHandlerImpl {
	public:
		ResourceHandlerImpl() :
			m_sprite_manager{std::make_unique<SpriteManager>()},
			m_music_manager{std::make_unique<MusicManager>()},
			m_sfx_manager{std::make_unique<SFXManager>()}
		{
		}

		std::unique_ptr<SpriteManager> m_sprite_manager;
		std::unique_ptr<MusicManager> m_music_manager;
		std::unique_ptr<SFXManager> m_sfx_manager;
};

ResourceHandler::ResourceHandler() :
	m_pimpl{std::make_unique<ResourceHandlerImpl>()}
{
}

ResourceHandler::~ResourceHandler() = default;
ResourceHandler::ResourceHandler(const ResourceHandler&) = delete;
ResourceHandler& ResourceHandler::operator=(const ResourceHandler&) = delete;
ResourceHandler::ResourceHandler(ResourceHandler&&) = delete;
ResourceHandler& ResourceHandler::operator=(ResourceHandler&&) = delete;

Sprite* ResourceHandler::GetSprite(const std::string& path) const {
	return m_pimpl->m_sprite_manager->get(path);
}

Music* ResourceHandler::GetMusic(const std::string& path) const {
	return m_pimpl->m_music_manager->get(path);
}

SoundEffect* ResourceHandler::GetSoundEffect(const std::string& path) const {
	return m_pimpl->m_sfx_manager->get(path);
}

} // namespace sdl2engine
