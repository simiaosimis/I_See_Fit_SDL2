#include "engine/states/game/Placeholder.h"
#include "audio/AudioHandler.h"
#include "core/ResourceManager.h"
#include "graphics/Sprite.h"
#include "engine/Game.h"
#include "engine/Animation.h"
#include "input/InputHandler.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

Placeholder::Placeholder() :
	m_explosion{nullptr},
	m_explosion_animation{nullptr},
	m_animation_clip{0, 0, 0, 0}
{
}

Placeholder::~Placeholder() {
	delete m_explosion_animation;
}

void Placeholder::Load() {
	log_info() << "Loading STATE placeholder...";

	m_explosion_animation = new Animation(0, 4, 32, 32, 5, 5.0);
	m_explosion = ResourceManager<Sprite>::Instance().Get("assets/images/spritesheet.png");
	m_animation_clip = {0, 0, 0, 0};

	AudioMusic::Play("assets/audio/music/test_music.flac", k_infinite_loop);
	AudioSfx::Play("assets/audio/sfx/test_sfx.wav", 1);
}

void Placeholder::Unload() {
	log_info() << "Unloading STATE placeholder...";
}

void Placeholder::Update(const double dt_) {
	const InputArray keyStates = InputHandler::KeyStates();

	if(keyStates[Key::FadeOut] == true) {
		AudioMusic::FadeOut(5.0);
	}

	if(keyStates[Key::LogSomething] == true) {
		log_warn() << "Testing input!";
	}

	if(keyStates[Key::TestSfx] == true) {
		AudioSfx::Play("assets/audio/sfx/test_sfx.wav", 1);
	}

	if(keyStates[Key::TestSfxAfterFadeOut] == true) {
		if(AudioMusic::FadedOut()) {
			AudioSfx::Play("assets/audio/sfx/tururu.wav", 1);
		}
	}

	m_explosion_animation->Update(m_animation_clip, dt_);
}

void Placeholder::Render() {
	m_explosion->Render(0, 0, &m_animation_clip, true);
}

} // namespace sdl2engine
