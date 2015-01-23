#include "engine/GStatePlaceholder.h"
#include "engine/Game.h"
#include "util/Logger.h"

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
	this->image = Game::Instance().Resource().sprite("assets/images/spritesheet.png");

	Game::Instance().GetAudioHandler().ChangeMusic("assets/audio/music/test_music.flac");
}

void GStatePlaceholder::unload() {
	log_debug() << "\tUnloading STATE placeholder...";

	StateGame::unload();
}

void GStatePlaceholder::update(const double dt_) {
	const InputArray keyStates = Game::Instance().Input();

	if(keyStates[GameKeys::SPACE] == true) {
		Game::Instance().GetAudioHandler().PlaySoundEffect("assets/audio/sfx/test_sfx.wav");
	}

	this->animation->Update(this->animationClip, dt_);
}

void GStatePlaceholder::render() {
	this->image->render(0, 0, &this->animationClip, true);
}
