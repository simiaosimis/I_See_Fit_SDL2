#include "engine/GStatePlaceholder.h"
#include "audio/AudioHandler.h"
#include "engine/Game.h"
#include "core/ResourceManager.h"
#include "util/Logger.h"
#include "util/Assert.h"

namespace sdl2engine {

GStatePlaceholder::GStatePlaceholder() :
	image(nullptr),
	animation(nullptr),
	animationClip{0, 0, 0, 0}
{

}

GStatePlaceholder::~GStatePlaceholder() {
	delete this->animation;
}

void GStatePlaceholder::load() {
	log_debug() << "Loading STATE placeholder...";

	log_info() << "Press SPACEBAR for the SFX.";

	this->animation = new Animation(0, 4, 32, 32, 5, 5.0);
	this->animationClip = {0, 0, 0, 0};
	this->image = ResourceManager<Sprite>::Instance().Get("assets/images/spritesheet.png");

	AudioMusic::Play("assets/audio/music/test_music.flac", k_infinite_loop);
}

void GStatePlaceholder::unload() {
	log_debug() << "\tUnloading STATE placeholder...";

	StateGame::unload();
}

void GStatePlaceholder::update(const double dt_) {
	const InputArray keyStates = Game::Instance().Input();

	if(keyStates[GameKeys::SPACE] == true) {
		AudioMusic::FadeOut(5.0);
		AudioSfx::Play("assets/audio/sfx/test_sfx.wav", 1);
	}

	if(keyStates[GameKeys::A] == true) {
		if(AudioMusic::FadedOut()) {
			AudioSfx::Play("assets/audio/sfx/tururu.wav", 1);
		}
	}

	this->animation->Update(this->animationClip, dt_);
}

void GStatePlaceholder::render() {
	this->image->Render(0, 0, &this->animationClip, true);
}

} // namespace sdl2engine
