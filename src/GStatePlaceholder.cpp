#include "GStatePlaceholder.h"
#include "Game.h"
#include "Logger.h"
#include "UsefulDefines.h"

GStatePlaceholder::GStatePlaceholder() :
	image(nullptr),
	animation(nullptr),
	animationClip{0, 0, 0, 0}
{
	
}

GStatePlaceholder::~GStatePlaceholder() {
	SAFE_DELETE(this->animation);
}

void GStatePlaceholder::load() {
	Log(DEBUG) << "Loading STATE placeholder...";

	this->animation = new Animation(0, 4, 32, 32, 5, false, 2);
	this->animationClip = {0, 0, 0, 0};
	this->image = Game::instance().getResources().get("res/images/spritesheet.png");
}

void GStatePlaceholder::unload() {
	Log(DEBUG) << "\tUnloading STATE placeholder...";

	StateGame::unload();
}

void GStatePlaceholder::update(const double dt_) {
	this->animation->update(this->animationClip, dt_);
}

void GStatePlaceholder::render() {
	this->image->render(0, 0, &this->animationClip, true);
}
