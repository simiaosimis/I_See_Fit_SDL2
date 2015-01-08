#include "GStatePlaceholder.h"
#include "Game.h"
#include "Logger.h"

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
	Log(DEBUG) << "Loading STATE placeholder...";

	Log(INFO) << "Press SPACEBAR for the SFX.";

	this->animation = new Animation(0, 4, 32, 32, 5, 5.0);
	this->animationClip = {0, 0, 0, 0};
	this->image = Game::instance().getResource().sprite("assets/images/spritesheet.png");

	Game::instance().getAudioHandler().changeMusic("assets/audio/music/test_music.flac");
}

void GStatePlaceholder::unload() {
	Log(DEBUG) << "\tUnloading STATE placeholder...";

	StateGame::unload();
}

void GStatePlaceholder::update(const double dt_) {
	const std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	if(keyStates[GameKeys::SPACE] == true) {
		Game::instance().getAudioHandler().pushSoundEffect("assets/audio/sfx/test_sfx.wav");
	}

	this->animation->Update(this->animationClip, dt_);
}

void GStatePlaceholder::render() {
	this->image->render(0, 0, &this->animationClip, true);
}
